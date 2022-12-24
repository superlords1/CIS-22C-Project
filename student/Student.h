// Specification file for the Student class
// Written By: Trevor Mathisen
// Changed By: 

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <fstream>

using std::string;
using std::ostream;
using std::ofstream;

class Student; // Forward Declaration

// Function Prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Student &);

class Student
{
	private:
		string stuId; // unique key
		string stuName;
		string stuPhone;
		float stuGpa;
		int stuYear;

	public:
		//constructors
		Student();
		Student(string, string, string, float , int);
		
		//setters
		void setId(string id){ stuId = id;}
		void setName(string nm){ stuName = nm;}
		void setPhone(string pn){ stuPhone = pn;}
		void setGpa(float gpa){ stuGpa = gpa;}
		void setYear(int yr){ stuYear = yr;}
		
		//getters
		string getId() const { return stuId; }
		string getName() const { return stuName; }
		string getPhone() const { return stuPhone; }
		float getGpa() const { return stuGpa; }
		int getYear() const { return stuYear; }
		
		//other functions
		void hDdisplay()const;
		void vDisplay()const;
		
		// overloaded operators
		friend ostream& operator<< (ostream&, const Student&);
		friend ofstream& operator<< (ofstream&, const Student&);
		bool operator==(const Student& rhs) {return stuId == rhs.getId();}
		bool operator<(const Student& rhs) {return stuId < rhs.getId();}
		bool operator>(const Student& rhs) {return stuId > rhs.getId();}
};

#endif
