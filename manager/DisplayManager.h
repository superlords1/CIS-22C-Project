#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "../bst/BinarySearchTree.h"
#include "../student/Student.h"

using std::cin;
using std::cout;
using std::setw;
using std::endl;


void hDdisplay(Student &);
void iDisplay(string &item , int level);
void displayHash(HashTable<Student>&hash, string id, int keyToIndex(const Student &key, int size));

void displayManager(HashTable<Student>&hash, BinarySearchTree<string>&bst){
    cout << "\nDisplay\n";
    cout <<   "=======\n";

    bst.inOrderDisplayHash(hash, displayHash, keyToIndex);
    cout << endl;
}

void displayHash(HashTable<Student>&hash, string id, int keyToIndex(const Student &key, int size)){
    Student ItemOut, targetStd;
    targetStd.setId(id);

    if (hash.search(ItemOut, targetStd, keyToIndex) != -1){
        cout << endl;
        ItemOut.vDisplay();
        cout << endl;
    }
}

void displayIndentedList(BinarySearchTree<string>&bst){
    cout << "\nIdented Tree\n";
    cout <<   "=======\n";
    bst.printTree(iDisplay);
    cout << endl;
}

void hDdisplay(Student &std){
    cout << std::left;
    cout << " " << setw(4) << std.getId() << "  ";
    cout << " " << setw(18) << std.getName() << "  ";
    cout << " " << setw(15)<< std.getPhone() << "  ";
    cout << std::right;
    cout << " " << setw(3) << std.getGpa() << " ";
    cout << " " << setw(3) << std.getYear() << " ";
    cout << std::left << endl;
}

void iDisplay(string &item , int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item << endl;
}