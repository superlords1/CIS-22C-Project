// Binary Search Tree ADT
// Created by A. Student
// Modified by: Bach (Peter) Tran
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <iostream>

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
public:
    // insert a node at the correct location
    bool insert(const ItemType &item);
    // remove a node if found
    bool remove(const ItemType &item);
    // find a target node
    bool search(const ItemType &target, ItemType &returnedItem) const;
    // find the smallest node
    bool findSmallest(ItemType &returnedItem) const;
    // find the largest node
    bool findLargest(ItemType &returnedItem) const;
    
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

    // search for target node
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType &target) const;
        
    // find the smallest node
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr, ItemType &smallest) const;
        
    // find the largest node
    BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr, ItemType &smallest) const;
   
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool &success);
    
    // delete target node from tree, called by internal remove node
    //BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    //BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &successor);
    
};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  

//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller 
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;

    temp = _search(this->rootPtr, anEntry);
    if (temp){
        returnedItem = temp->getItem();
        return true;
    }
        
    return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &item){
    bool success = true;
    BinaryNode<ItemType>*temp = _remove(this->rootPtr, item, success);
    
    // if (success){
    //     std::cout << "Item found and removed" << std::endl;
    // }
    // else
    //     std::cout << "Item not found!" << std::endl;

    return success;
}


//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
// Using recursion
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{

    if( !nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }

    if (newNodePtr->getItem() < nodePtr->getItem())
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
    else
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));

    return nodePtr;
}

//Implementation for the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType &target) const
{
    if (!nodePtr)
        return nullptr;

    if (nodePtr->getItem() > target)
        return _search(nodePtr->getLeftPtr(), target);
    else if (nodePtr->getItem() < target)
        return _search(nodePtr->getRightPtr(), target);
    else  // target == nodePtr->getItem()
        return nodePtr;    
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool &success) {
    // base case
    if (nodePtr == NULL){
        success = false;
        return nodePtr;
    }
        
 
    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (target < nodePtr->getItem()){
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
        return nodePtr;
    }
        
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    if (target > nodePtr->getItem()){
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
        return nodePtr;
    }
       
    // if key is same as root's key, then This is the node
    // to be deleted

    if (nodePtr->getLeftPtr()==NULL && nodePtr->getRightPtr()==NULL)
        return NULL;
    
    // node with only one child or no child
    else if (nodePtr->getLeftPtr() == NULL) {
        BinaryNode<ItemType>* temp = nodePtr->getRightPtr();
        delete nodePtr;
        return temp;
    }
    else if (nodePtr->getRightPtr() == NULL) {
        BinaryNode<ItemType>* temp = nodePtr->getLeftPtr();
        delete nodePtr;
        return temp;
    }

    BinaryNode<ItemType>* succParent = nodePtr;
 
    // Find successor
    BinaryNode<ItemType>* succ = nodePtr->getRightPtr();
    while (succ->getLeftPtr() != NULL) {
        succParent = succ;
        succ = succ->getLeftPtr();
    }

    // Delete successor.  Since successor
    // is always left child of its parent
    // we can safely make successor's right
    // right child as left of its parent.
    // If there is no succ, then assign
    // succ->right to succParent->right
    if (succParent != nodePtr)
        succParent->setLeftPtr(succ->getRightPtr());
    else
        succParent->setRightPtr(succ->getRightPtr());

    // Copy Successor Data to root
    nodePtr->setItem(succ->getItem());

    // Delete Successor and return root
    delete succ;
    return nodePtr;
}


#endif
