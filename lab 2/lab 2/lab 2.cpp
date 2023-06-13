#include "Student.h"
#include <iostream>
#include <string>


using namespace std;

Student MakeStudent()
{
	string n;
	string g;
	float m;
	cout << "Student name: ";
	getline(cin, n);
	cout << "Student group: ";
	getline(cin, g);
	cout << "Marks: ";
	cin >> m;

	return Student(n, g, m);
}

void PrintStudent(Student s)
{
	s.Show();
}

void main()
{

	Student s1;
	s1.Show();


	Student s2("rostic", "RIS-22-2B", 15000);
	s2.Show();


	Student s3 = s2;

	s3.SetName("shaharyar");
	s3.SetGroup("RIS-22-2B");
	s3.SetMarks(0);


	PrintStudent(s3);


	s1 = MakeStudent();
	s1.Show();
}