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
#include "../StackATD.h"
#include "../student/Student.h"

void UndoDeleteManager(HashTable<Student>&hash, BinarySearchTree<string>&bst, Stack<Student> &st){
    if (st.isEmpty()){
        cout << "\nNo deletion recorded!\n\n";
        return;
    }

    Student top = st.pop();
    cout << "\nRecently deleted item:\n";
    top.vDisplay();

    cout << "\nInserting student back into database...\n";
    hash.insert(top, keyToIndex);
    bst.insert(top.getId());

    cout << "Undo delete successfully!\n\n";
    return;
}