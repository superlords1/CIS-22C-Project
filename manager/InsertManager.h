#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "../hash/HashTable.h"
#include "../bst/BinarySearchTree.h"
#include "../student/Student.h"

#include "../utils/HashUtils.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::getline;

void insertManager(HashTable<Student>&hash, BinarySearchTree<string>&bst){
    string id, name, phone, _;
    float gpa;
    int year;

    cout << "\nInsert\n";
    cout << "=======\n";

    cout << endl << "Creating new student profile..."  << endl;
    cout << "Enter id: ";    cin >> id;

    if (bst.search(id, _)){
        cout << "\nId already used in database!\n\n";
        return;
    }
        
    cout << "Enter name: ";  cin.ignore(); getline(cin, name);
    cout << "Enter phone: "; cin >> phone;
    cout << "Enter GPA: ";   cin >> gpa;
    cout << "Enter year: ";  cin >> year;

    // sample entry
    // id = "86989401";
    // name = "Stephen Curry";
    // phone = "408-555-0128";
    // gpa = 4.0;
    // year = 2;


    Student newObj(id, name, phone, gpa, year);
    bst.insert(newObj.getId());
    hash.insert(newObj, keyToIndex);
    cout << "\nStudent added successfully!\n\n";

    // if the data added causes the load factor of hash table to be >= 0.75, re-hashing
    if (hash.getCount() / double(hash.getSize()) >= 0.75){
        int newHashSize = getNextPrimeNumber(hash.getCount() * 2);
        hash.rehashing(newHashSize , keyToIndex);
    }
        
}
