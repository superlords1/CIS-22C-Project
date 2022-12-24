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
#include "../StackATD.h"

using std::cin;
using std::cout;

void deleteManager(HashTable<Student>& hash, BinarySearchTree<string>& bst, Stack<Student>&s)
{
    cout << "\nDelete\n";
    cout <<   "=======\n";

    cout << "\nEnter student ID to delete: ";
    string target; cin >> target;
    

    if (bst.remove(target)){
        Student itemOut, targetStd; 
        targetStd.setId(target);

        hash.remove(itemOut, targetStd, keyToIndex);
        
        s.push(itemOut);
        cout << "Student successfully found and deleted from database!" << endl;
        cout << endl << "Student information:" << endl;
        itemOut.vDisplay();
        cout << endl;
        cout << "To undo action, type \'u\' to undo delete!" << endl << endl;
    }
    else
        cout << "Student not found!\n\n";
}