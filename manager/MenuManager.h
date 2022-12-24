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

#include "InsertManager.h"
#include "SearchManager.h"
#include "DisplayManager.h"
#include "DeleteManager.h"
#include "UndoDeleteManager.h"

#include "../utils/FileReadWrite.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::getline;

// function declaration
void showMenu();

// menuManager function
void menuManager(HashTable<Student>&hash, BinarySearchTree<string>&bst, Stack<Student> st)
{
    while (true)
    {
        bool invalid = true;
        showMenu(); // print menu options

        cout << "\nEnter your choice: ";
        while (invalid)
        {
            invalid = false;
            char choice; cin >> choice;
            switch (tolower(choice))
            {
                case '1':
                    insertManager(hash, bst);
                    break;
                case '2': 
                    deleteManager(hash, bst, st);
                    break;
                case '3':
                    searchManager(hash);
                    break;
                case '4': 
                    displayManager(hash, bst);
                    break;
                case 's': // save to file
                    hash.saveToFile();
                    // clear stack
                    while (!st.isEmpty())
                        st.pop();
                    break;

                case 'u': // undo delete
                    UndoDeleteManager(hash, bst, st);
                    break;
                
                case 'r':  // read from file
                    readFromFile(&hash, bst);
                    break;

                case 'v': // view statistics
                    cout << "\nStatistics\n";
                    cout <<   "=======\n";
                    cout << "Load factor: "  << hash.getLoadFactor() << endl;
                    cout << "Number of collisions: " << hash.getNumCollision() << endl;
                    cout << "Longest collision path: " << hash.getLongestCollisionPath() << endl;
                    cout << endl;
                    break;
                
                case 'q':
                    cout << endl << "Exiting..." << endl;
                    exit(0);

                // hidden options
                case 'i':
                    displayIndentedList(bst);
                    break;
                case 't':
                    cout << endl;
                    cout << "Team members:" << endl;
                    cout << "   1. Bach (Peter) Tran - Group Leader" << endl;
                    cout << "   2. Trevor Mathisen" << endl;
                    cout << "   3. Nyun Ei Hlaing" << endl;
                    cout << "   4. Vincent Quach" << endl;
                    cout << endl;
                    break;

                default: // not in valid cases
                    invalid = true;
                    cout << "Invalid input, please try again!" << endl;
                    cout << "\nEnter your choice: ";
            }
        }

        // wait for keyboard input to continue
        cout << "Press any button to continue..." << endl;
        cin.ignore();
        cin.get();
    }
}

// print menu options
void showMenu(){
    cout << endl << endl;
    cout << "-------MENU-------";
    cout << endl << endl;

    cout << "1. Insert" << endl; 
    cout << "2. Delete" << endl; 
    cout << "3. Search" << endl; 
    cout << "4. Display" << endl;  // sorted by key (print from bst)

    cout << endl;

    cout << "r. Read from file" << endl;
    cout << "u. Undo delete" << endl;
    cout << "s. Save to file" << endl;  // (from hash table)
    cout << "v. View statistics" << endl;
    
    
    cout << "h. Help" << endl;

    // hidden options
    /*
        i. Print indented tree (print from bst)
        t. Print team members 
    */

    cout << "q. Quit" << endl;
    
    cout << endl << endl;
}