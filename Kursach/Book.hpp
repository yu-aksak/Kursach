#pragma once
#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
protected:
	int yearMade;
	string ISBN, autor, title, genre, edition;
public:
	Book() {}
	virtual void print() = 0;
	virtual void view()const = 0;
	virtual void viewBooks() = 0;
	virtual string returnISBN()const = 0;
	virtual string returnAutor()const = 0;
	virtual string returnTitle()const = 0;
	virtual string returnGenre()const = 0;
	virtual int returnYearMade()const = 0;
	virtual string returnEdition()const = 0;
	virtual ~Book() {}
};

class Written_off : public Book {
	int count, num_report_card;
	string date;
public:
	Written_off() { }
	Written_off(string, string, string, string, int, string, int, string, int);
	void setter(string, string, string, string, int, string, int, string, int);
	void print();
	void view()const;
	void search(int, string);
	void sortBook(int);
	void filtration(int, string);
	void viewBooks();
	string returnISBN()const;
	string returnAutor()const;
	string returnTitle()const;
	string returnGenre()const;
	int returnYearMade()const;
	string returnEdition()const;
	int returnCount()const;
	string returnDate()const;
	int returnNumEmpCard()const;
	~Written_off() { }
};

class Recieved : public Book {
	int count, num_report_card;
	string date;
public:
	Recieved() { }
	Recieved(string, string, string, string, int, string, int, string, int);
	void setter(string, string, string, string, int, string, int, string, int);
	void print();
	void addAvailable();
	void view()const;
	void viewBooks();
	void search(int, string);
	void sortBook(int);
	void filtration(int, string);
	string returnISBN()const;
	string returnAutor()const;
	string returnTitle()const;
	string returnGenre()const;
	int returnYearMade()const;
	string returnEdition()const;
	int returnCount() const;
	string returnDate()const;
	int returnNumEmpCard()const;
	~Recieved() { }

};

class Available : public Book {
	int count;
public:
	Available() {}
	Available(string, string, string, string, int, string, int);
	void setter(string, string, string, string, int, string, int);
	void view()const;
	void viewBooks();
	void setCount(int);
	void search(int, string);
	void sortBook(int);
	void filtration(int, string);
	string returnISBN()const;
	string returnAutor()const;
	string returnTitle()const;
	string returnGenre() const;
	int returnYearMade()const;
	string returnEdition()const;
	int returnCount()const;
	void print();
	~Available() {}
};

class Issued : public Book {
	int Num_card_reader, num_report_card;
	string date;
public:
	Issued() {}
	Issued(string, string, string, string, int, string, int, string, int);
	void setter(string, string, string, string, int, string, int, string, int);
	void print();
	void view()const;
	void viewBooks();
	void viewBooks(int&);
	int checkIssued(int&);
	void search(int, string);
	void sortBook(int);
	void filtration(int, string);
	string returnISBN()const;
	string returnAutor()const;
	string returnTitle()const;
	string returnGenre()const;
	int returnYearMade()const;
	string returnEdition()const;
	int returnNumCard()const;
	string returnDate()const;
	int returnNumEmpCard()const;
	~Issued() {}
};

class Reserved : public Book {
	int Num_card_reader;
public:
	Reserved() {}
	Reserved(string, string, string, string, int, string, int);
	void setter(string, string, string, string, int, string, int);
	void print();
	void view() const;
	void viewBooks();
	void viewBooks(int&);
	void search(int, string);
	void sortBook(int);
	void filtration(int, string);
	int checkReserved(int&);
	string returnISBN()const;
	string returnAutor()const;
	string returnTitle()const;
	string returnGenre()const;
	int returnYearMade()const;
	string returnEdition()const;
	int returnNumCard()const;
	~Reserved() {}
};

#endif // !BOOK_HPP