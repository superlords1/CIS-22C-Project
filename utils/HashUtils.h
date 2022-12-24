#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "../student/Student.h"

using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::getline;

bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;
   
    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n % 2 == 0 || n % 3 == 0) return false;
   
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
           return false;
   
    return true;
}


// used to find the size of hash table
int getNextPrimeNumber(int n){
    if (n <= 1)
        return 2;
 
    bool found = false;
 
    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        n++;
        if (isPrime(n))
            found = true;
    }
 
    return n;
}


// Hash function: takes the key and returns the index in the hash table
int keyToIndex(const Student &obj, int size){
    string key = obj.getId();
    int sum = 0;
    for (int i = 0; i < key.size(); i++){
        sum += key[i] - '0';  // char - '0' to extract numeric value from char digit
    }
    return sum % size;
}
