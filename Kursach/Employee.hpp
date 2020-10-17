#pragma once
#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <string>
using namespace std;

class Employee {
	int num_report_card = 0; 
	string firstName, name, secondName, position;
public:
	Employee() { }
	Employee(int, string, string, string, string);
	void setter(int, string, string, string, string);
	void print();
	void viewBookReaders(string, string);
	void viewReaders();
	void set(int&);
	void setFirstName(const string&);
	void setName(const string&);
	void setSecondName(const string&);
	void setPosition(const string&);
	void editInfo(int, string);
	template<class T> void viewBooks()const;
	void viewBooks(int)const;
	void checkIssued(int, string, string);
	void giveBook(int, string);
	void giveBook(int, string, string, string);
	void acceptBook(int, string, string);
	void checkReader(int);
	template<class T> void sortBook(int);
	template<class T> void searchBook(int, string);
	template<class T> void search(int);
	template<class T> void filtration(int);
	template<class T> void filtrationBook(int, string);

	void addBook(string, string, string, string, int, string, int, string);
	void deleteBook(string, int, string);

	friend ostream& operator<<(ostream& out, const Employee& A);
	~Employee() {}
};

#endif // !EMPLOYEE_HPP