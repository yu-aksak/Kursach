#pragma once
#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <string>
using namespace std;

class Reader {
	int Num_Library_card = 0;
	string firstName, name, secondName, adress, phone;
public:
	Reader() { }
	Reader(int, string, string, string, string, string);
	void setter(int, string, string, string, string, string);
	void set(int&);
	void print();
	void setFirstName(const string&);
	void setName(const string&);
	void setSecondName(const string&);
	void setAdress(const string&);
	void setPhone(const string&);
	void editInfo(int, string);
	void viewBooks();
	template<class T> void viewBooksR();
	void search(int, string);
	void filtration(int, string);
	void reserve(string, string);
	void remove(string, string);
	void check();
	friend ostream& operator<<(ostream& out, const Reader& A);
	~Reader() {}
};

#endif // !READER_HPP