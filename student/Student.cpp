// Implementation file for Student Class
// Written By: Nyun Ei Hlaing 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Student.h"

using namespace std;

// Constructor

Student::Student()
{
    stuId = "";
    stuName = "";
    stuPhone = "";
    stuGpa = 0;
    stuYear = 0;
}

// Overloaded Constructor

Student::Student(string id, string nm, string ph, float gpa, int year)
{
    stuId = id;
    stuName = nm;
    stuPhone = ph;
    stuGpa = gpa;
    stuYear = year;
}

// Displays the values of the Student object member variables
// on one line (horizontal display)

void Student::hDdisplay() const
{
    cout << left;
    cout << " " << setw(4) << stuId << "  ";
    cout << " " << setw(2) << stuName << "  ";
    cout << " " << setw(10)<< stuPhone << "  ";
    cout << right;
    cout << " " << setw(7) << stuGpa << " ";
    cout << " " << setw(7) << stuYear << " ";
    cout << left << endl;
}

// Displays the values of the Student object member variables
// one per line (vertical display)

void Student::vDisplay() const
{
    cout << "  Student ID: " << stuId << endl;
    cout << "        Name: " << stuName << endl;
    cout << "Phone Number: " << stuPhone << endl;
    cout << "         GPA: " << stuGpa << endl;
    cout << "        Year: " << stuYear << endl; 
}

ostream &operator << (ostream &output, const Student& stu)
{
    output << stu.getId() << " " << stu.getName() << "; " << stu.getPhone() << " ";
    output << stu.getGpa() << " " << stu.getYear();
    return output;
}

ofstream &operator << (ofstream &outfile, const Student& stu){
    outfile << stu.getId() << " " << stu.getName() << "; " << stu.getPhone() << " ";
    outfile << stu.getGpa() << " " << stu.getYear(); 
    return outfile;
}