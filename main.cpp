#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "hash/HashTable.h"
#include "bst/BinarySearchTree.h"
#include "student/Student.h"
#include "StackATD.h"

#include "manager/MenuManager.h"

// comment out afterwards
#include "student/Student.cpp"

using namespace std;

int main()
{
    HashTable<Student> hash;
    BinarySearchTree<string> bst;
    Stack<Student> s;

    menuManager(hash, bst, s);

    return 0;
}