/* Unit 5: File I/O:  
• Determine Hash Size (count the lines in the input file, multiply it by 2, and choose the next prime number).  
• Read data from the input file and insert them into the hash table and BST 
• Save to file (in hash table sequence) 
• Re-hashing: – only for teams of 4 or 5 students:  
    o When load factor is 75%, allocate another hash table (2 * actual size, and 
      choose the next prime number), then  
    o Traverse the hash table and hash each item into the new table using the same 
      hash function and collision resolution method, and delete the old hash table) 
 
Created by Trevor Mathisen */
 
#ifndef _FILE_READ_WRITE
#define _FILE_READ_WRITE
 
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "HashUtils.h"
 
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::getline;
 
void readFromFile(HashTable<Student>*hash, BinarySearchTree<string> &bst) {
    cout << "\nEnter file name to read from: ";
    string filename; cin >> filename;
    ifstream fin(filename);
    int hashSize = hash->getSize();
    
    if(!fin)
    {
        cout << "\nError opening the input file: \""<< filename << "\"" << endl << endl;
        return;
    }
 
    string line;
 
    vector<Student> allStudents; // Vector to store student data while reading number of lines
    while (getline(fin, line))
    {
        string id, name, phone;
        float gpa;
        int year;
 
        stringstream temp(line);   // create temp with data
        temp >> id;                // read from temp
        temp.ignore();             // to ignore space in front of name
        getline(temp, name, ';');  // stop reading name at ';'
        temp >> phone;
        temp >> gpa;
        temp >> year;
        // create a Student object and initialize it with data from file
        Student aStudent(id, name, phone, gpa, year);
        allStudents.push_back(aStudent); // Insert it into the vector in any order
    }
    //cout << "Number of lines read: " << numLines << endl; // For debug
    
    fin.close(); // All done with the file
    size_t numLines = allStudents.size();
 
    // Rehasing: If needed, allocate a new hash table and replace the given pointer
    if ((numLines / double(hashSize)) >= 0.75) {
        cout << "Recomputing hashSize" << endl;
        hashSize = getNextPrimeNumber(numLines * 2);
        HashTable<Student> *newHash;
        newHash = new HashTable<Student>(hashSize);
        delete hash;
        hash = newHash;
        // cout << "New Hash Size: " << hash->getSize() << endl;
    } else { 
        // cout << "Hash Size: " << hash->getSize() << endl; 
    }
 
    // Insert into hash and BST
    for (int i = 0; i < numLines; i++) {
        hash->insert(allStudents.at(i), keyToIndex);
        bst.insert(allStudents.at(i).getId());
        // cout << allStudents.at(i) << endl;
    }
    allStudents.clear(); // Release the memory
    // cout << "Size: " << hash->getSize() << endl;
    // cout << "Count: " << hash->getCount() << endl;
    cout << "File data read and added to database successfully!\n\n";
}
 
#endif
