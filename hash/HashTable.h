// Specification file for the Hash class
// Written By: A. Student
// Changed by: Bach (Peter) Tran


#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "HashNode.h"

using std::vector;

template<class ItemType>
class HashTable
{
private:
	HashNode<ItemType>* hashAry;
	int hashSize;
    int count;
    int numCollision = 0;
    int longestCollisionPath = 0;
	
public:
	HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
	HashTable(int n)	{ count = 0; hashSize = n;	hashAry = new HashNode<ItemType>[hashSize]; }
	~HashTable(){ delete [] hashAry; }

	int getCount() const	{ return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const {return 100.0 * count / hashSize; }
    bool isEmpty() const	{ return count == 0; }
    bool isFull()  const	{ return count == hashSize; }
    
    int getNumCollision() const { return numCollision; }
    int getLongestCollisionPath() const { return longestCollisionPath; }
    
    bool insert( const ItemType &itemIn, int h(const ItemType &key, int size) );
    bool remove( ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));
    int  search( ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));

    void saveToFile() const;
    void rehashing(int newSize, int h(const ItemType &key, int size));
};

/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert( const ItemType &itemIn, int h(const ItemType &key, int size) )
{
    if ( count == hashSize)
        return false;
    
    int bucket = h(itemIn, hashSize);
    int bucketsProbed = 0;
    bool collision = false;

    while (bucketsProbed < hashSize){
        // Insert item in next empty bucket
        if (hashAry[bucket].getOccupied() != 1){
            hashAry[bucket].setItem(itemIn);
            hashAry[bucket].setOccupied(1);
            count++;

            if (bucketsProbed > longestCollisionPath){
                longestCollisionPath = bucketsProbed;
            }

            if (collision)
                numCollision++;
            return true;
        }
        else {
            collision = true;
        }

        // Increment bucket index
        bucket = (bucket + 1) % hashSize;
        // Increment number of buckets probed
        bucketsProbed++;
    }

    return false;
}

/*~*~*~*
   Removes the item with the matching key from the hash table
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record
*~**/
template<class ItemType>
bool HashTable<ItemType>::remove( ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size))
{
    if (count == 0)
        return false;

    int bucket = h(key, hashSize);
    int bucketsProbed = 0;

    while (hashAry[bucket].getOccupied() != 0 && bucketsProbed < hashSize){
        if (hashAry[bucket].getItem() == key){
            
            itemOut = hashAry[bucket].getItem();
            hashAry[bucket].setOccupied(-1);
            hashAry[bucket].setItem(ItemType());
            count--;

            return true;
        }

        // Increment bucket index
        bucket = (bucket + 1) % hashSize;

        // Increment number of buckets probed
        bucketsProbed++;
    }
    
    return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template<class ItemType>
int HashTable<ItemType>::search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size))
{
    if (count == 0)
        return -1;

    int bucket = h(key, hashSize);
    int bucketsProbed = 0;

    while (hashAry[bucket].getOccupied() != 0 && bucketsProbed < hashSize){
        if (hashAry[bucket].getItem() == key){
            
            itemOut = hashAry[bucket].getItem();
            hashAry[bucket].setNoCollisions(bucketsProbed);

            return bucketsProbed;
        }

        // Increment bucket index
        bucket = (bucket + 1) % hashSize;

        // Increment number of buckets probed
        bucketsProbed++;
    }
     
    return -1;
}

// save hash table to file
template<class ItemType>
void HashTable<ItemType>::saveToFile() const {
    std::ofstream outfile;
    std::string filename;

    std::cout << "Enter file name (should only be 1 word, end with .txt): ";
    std::cin >> filename;

    outfile.open(filename);
    int count = 0;

    for (int i = 0; i < getSize(); i++){
        if (hashAry[i].getOccupied() == 1){
            outfile << hashAry[i].getItem();
            count++;
            
            // prevent creating newline at the end of file
            if (count != getCount())
                outfile << "\n";
            else
                break;
        }
    }

    std::cout << "\nData saved to file successfully!\n\n";
}

template<class ItemType>
void HashTable<ItemType>::rehashing(int newSize, int h(const ItemType &key, int size)) {
    HashNode<ItemType>* newHashAry = new HashNode<ItemType>[newSize];
    for (int i = 0; i < hashSize; i++){
        newHashAry[i].setOccupied(hashAry[i].getOccupied());
        newHashAry[i].setNoCollisions(hashAry[i].getNoCollisions());

        if (hashAry[i].getOccupied() == 1)
            newHashAry[i].setItem(hashAry[i].getItem());
    }

    delete [] hashAry;
    hashAry = newHashAry;
    hashSize = newSize;

    std::cout << hashSize << std::endl;

    for (int i = 0; i < hashSize; i++){
        std::cout << hashAry[i].getItem() << std::endl;
    }
}

#endif // HASHTABLE_H_
