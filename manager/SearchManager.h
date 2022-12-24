#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "../utils/HashUtils.h"
#include "../hash/HashTable.h"
#include "../bst/BinarySearchTree.h"
#include "../student/Student.h"

using std::cin;
using std::cout;

void searchManager(HashTable<Student>&hash) {
    cout << "\nSearch\n";
    cout <<   "=======\n";
    
    Student std;
    string target;
    cout << "\nEnter student ID to search: ";
    cin >> target;
    Student targetStd;
    targetStd.setId(target);

    if (hash.search(std, targetStd, keyToIndex) != -1){
        cout << "Student found!" << endl << endl;
        std.vDisplay();
    }
    else {
        cout << "Student not found!" << endl;
    }
    cout << endl;
}
