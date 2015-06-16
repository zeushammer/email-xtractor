#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct Student
{
	string name;
	char gender;
	int id;
	float gpa;
}; // Student

void printStudents(Student& student)
{
  cout << "Name = " << left << setw(30) << student.name;
  cout.fill('0');
  cout << " ID = " << right << setw(7) << student.id
  	<< ", gpa = " << student.gpa << endl;
  cout.fill(' ');
} // printStudents

int main()
{
  int nStudents = 0;

  cout << "Programmer: Andrew Gerhold" << endl;
  cout << "Description: This program will record student information" << endl;
 
  cout << "How many records? ";
  cin >> nStudents;
  cin.ignore(1000, 10);

  // create an empty list
  deque<Student> student;

  // read and save the records
  for (int i = 0; i < nStudents; i++)
  {
	Student aStudent;

	cout << "Student Name: ";
	getline(cin, aStudent.name);

	cout << "Student Gender [M/F]: ";
	cin >> aStudent.gender;
	cin.ignore(1000, 10);

	cout << "Student ID: ";
	cin >> aStudent.id;
	cin.ignore(1000, 10);

	cout << "Student GPA: ";
	cin >> aStudent.gpa;
	cin.ignore(1000, 10);

	cout << endl;

	student.push_back(aStudent);
  } // while

  for (int i = 0; i < nStudents; i++)
  {
	printStudents(student[i]);
  }

	return 0;
} //main
