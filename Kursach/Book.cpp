#include "Book.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// собственная функция для сортировки vector
template<class T>
bool sortAutor(const T& a, const T& b) { return a.returnAutor() < b.returnAutor(); }
template<class T>
bool sortTitle(const T& a, const T& b) { return a.returnTitle() < b.returnTitle(); }
template<class T>
bool sortGenre(const T& a, const T& b) { return a.returnGenre() < b.returnGenre(); }

// списанные книги
#pragma region Written_off
Written_off::Written_off(string ISBN, string autor, string title, string genre,
	int yearMade, string edition, int count, string date, int num_report_card) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->count = count;
	this->date = date;
	this->num_report_card = num_report_card;
}


void Written_off::setter(string ISBN, string autor, string title, string genre,
				int yearMade, string edition, int count, string date, int num_report_card) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->count = count;
	this->date = date;
	this->num_report_card = num_report_card;
}

// просмотр всех списанных книг
void Written_off::viewBooks(){
	ifstream File_Data;
	int count1 = 0;
	File_Data.open("written_off.txt");
	cout << "\t" << setw(20) << left << "ISBN" << setw(17) << left << "Автор" << setw(28) << left <<
		"Название" << setw(18) << left << "Жанр" << setw(6) << left << "Год" << setw(10) << left <<
		"Издат-во" << setw(7) << left << "Кол-во" << setw(18) << left << "Дата списания" << setw(18) <<
		left << "№табеля работника" << endl;

	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
	{
		view();
		count1++;
	}
	try {
		if (count1 == 0)
			throw "Количество равно 0";
	}
	catch (const char* c) {
		cout << "В данном файле нет записей" << endl;
	}
	File_Data.close();
}

// запись в файл
void Written_off::print() {
	ofstream File_Data;
	File_Data.open("written_off.txt", ios::app);

	File_Data << endl;
	File_Data << ISBN << "\t" << autor << "\t" << title << "\t" << genre << "\t" 
			  << yearMade << "\t" << edition << "\t" << count << "\t" << date << "\t"
			  << num_report_card;
	File_Data.close();

}

// вывод информации на  экран
void Written_off::view() const {
	cout << "\t" << setw(20) << left << ISBN << setw(17) << left << autor << setw(28) << left << title 
		 << setw(18) << left << genre << setw(6) << left << yearMade << setw(10) << left <<	edition 
		 << setw(7) << left << count << setw(18) << left << date << setw(18) << left << num_report_card << endl;
}

// поиск книг в файле
void Written_off::search(int k, string key) {
	ifstream File_Data;
	File_Data.open("written_off.txt");
	int count1 = 0;
	
	//чтение из файла и вывод на экран книг, заданных критерием
	switch (k)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (title == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким названием" << endl;
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (autor == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг такого автора" << endl;
		break;
	case 3:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (ISBN == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким ISBN" << endl;
		break;
	default:
		break;
	}
	File_Data.close();
}

// сортировка книг в файле
void Written_off::sortBook(int k) {
	Written_off book;
	vector<Written_off> books;
	int count1 = 0;

	ifstream File_Data;
	File_Data.open("written_off.txt");
	// считывание книг из файла и запись в вектор
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
	{
		book.setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
		books.push_back(book);
		count1++;
	}
	File_Data.close();

	try {
		if (count1 == 0)
			throw "Количество равно 0";
	}
	catch (const char* s) {
		cout << "Нет книг в данной категории" << endl;
		return;
	}

	//сортировка вектора книг по определенному полю
	switch (k)
	{
	case 1:
		sort(books.begin(), books.end(), sortTitle<Written_off>);
		break;
	case 2:
		sort(books.begin(), books.end(), sortAutor<Written_off>);
		break;
	case 3:
		sort(books.begin(), books.end(), sortGenre<Written_off>);
		break;
	default:
		break;
	}
	File_Data.close();

	// очистка файла и запись в файл отсортированных книг
	ofstream File_Data1;
	File_Data1.open("written_off.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i].print();
	}
	cout << "Сортировка завершена успешно!" << endl;
}

// фильтрация книг в файле
void Written_off::filtration(int s, string key) {
	ifstream File_Data;
	File_Data.open("written_off.txt");
	int count1 = 0;
	Written_off book;
	//чтение из файла и вывод на экран книг, заданных кнритерием
	switch (s)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (autor == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого  автора" << endl;
		}
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (genre == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого жанра" << endl;
		}
		break;
	default:
		break;
	}
}

string Written_off::returnISBN() const {
	return ISBN;
}

string Written_off::returnAutor() const {
	return autor;
}

string Written_off::returnTitle() const {
	return title;
}

string Written_off::returnGenre() const {
	return genre;
}

int Written_off::returnYearMade() const {
	return yearMade;
}

string Written_off::returnEdition() const {
	return edition;
}

int Written_off::returnCount() const {
	return count;
}

string Written_off::returnDate()const {
	return date;
}

int Written_off::returnNumEmpCard()const {
	return num_report_card;
}

#pragma endregion

// поступившие книги
#pragma region Recieved
Recieved::Recieved(string ISBN, string autor, string title, string genre,
	int yearMade, string edition, int count, string date, int num_report_card) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->count = count;
	this->date = date;
	this->num_report_card = num_report_card;
}

void Recieved::setter(string ISBN, string autor, string title, string genre,
				int yearMade, string edition, int count, string date, int num_report_card) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->count = count;
	this->date = date;
	this->num_report_card = num_report_card;
}

// вывод информации на  экран
void Recieved::view() const {
	cout << "\t" << setw(20) << left << ISBN << setw(17) << left << autor << setw(28) << left << title
		 << setw(18) << left << genre << setw(6) << left << yearMade << setw(10) << left << edition 
		<< setw(7) << left << count << setw(18) << left << date << setw(18) << left << num_report_card << endl;
}

// запись в файл
void Recieved::print() {
	ofstream File_Data;
	File_Data.open("recieved.txt", ios::app);

	File_Data << endl;
	File_Data << ISBN << "\t" << autor << "\t" << title << "\t" << genre << "\t" << yearMade << "\t" << edition << "\t" << count << "\t" << date << "\t" << num_report_card;
	File_Data.close();
}

// добавить в "в наличии"
void Recieved::addAvailable() {
	Available book;
	book.setter(ISBN, autor, title, genre, yearMade, edition, count);
	book.print();
}

// поиск книг в файле
void Recieved::search(int k, string key) {
	ifstream File_Data;
	File_Data.open("recieved.txt");
	int count1 = 0;

	//чтение из файла и вывод на экран книг, заданных критерием
	switch (k)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (title == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким названием" << endl;
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (autor == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг такого автора" << endl;
		break;
	case 3:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (ISBN == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким ISBN" << endl;
		break;
	default:
		break;
	}
	File_Data.close();
}

// просмотр всех поступивших книг
void Recieved::viewBooks() {
	ifstream File_Data;
	File_Data.open("recieved.txt");
	cout << "\t" << setw(20) << left << "ISBN" << setw(17) << left << "Автор" << setw(28) << left <<
		"Название" << setw(18) << left << "Жанр" << setw(6) << left << "Год" << setw(10) << left <<
		"Издат-во" << setw(7) << left << "Кол-во" << setw(18) << left << "Дата поступления" << setw(18) <<
		left << "№табеля работника" << endl;

	// считывание из файла и вывод на экран
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
	{
		view();
	}
	File_Data.close();
}

// сортировка книг в файле
void Recieved::sortBook(int k) {
	Recieved book;
	vector<Recieved> books;
	int count1 = 0;

	ifstream File_Data;
	File_Data.open("recieved.txt");
	
	// считывание из файла и добавление в вектор
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
	{
		book.setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
		books.push_back(book);
		count1++;
	}
	File_Data.close();

	// сортировка вектора по определенному полю
	try {
		if (count1 == 0)
			throw "Количество равно 0";
	}
	catch (const char* s) {
		cout << "Нет книг в данной категории" << endl;
		return;
	}
	switch (k)
	{
	case 1:
		sort(books.begin(), books.end(), sortTitle<Recieved>);
		break;
	case 2:
		sort(books.begin(), books.end(), sortAutor<Recieved>);
		break;
	case 3:
		sort(books.begin(), books.end(), sortGenre<Recieved>);
		break;
	default:
		break;
	}
	File_Data.close();

	// очистка файла и запись в файл отсортированных книг
	ofstream File_Data1;
	File_Data1.open("recieved.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i].print();
	}
	cout << "Сортировка завершена успешно!" << endl;
}

// фильтрация книг в файле
void Recieved::filtration(int s, string key) {
	ifstream File_Data;
	File_Data.open("recieved.txt");
	int count1 = 0;
	Recieved book;
	//чтение из файла и вывод на экран книг, заданных кнритерием
	switch (s)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (autor == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого  автора" << endl;
		}
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count >> date >> num_report_card)
		{
			if (genre == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого жанра" << endl;
		}
		break;
	default:
		break;
	}
}

string Recieved::returnISBN()const {
	return ISBN;
}

string Recieved::returnAutor()const {
	return autor;
}

string Recieved::returnTitle()const {
	return title;
}

string Recieved::returnGenre()const {
	return genre;
}

int Recieved::returnYearMade()const {
	return yearMade;
}

string Recieved::returnEdition()const {
	return edition;
}

int Recieved::returnCount() const {
	return count;
}

string Recieved::returnDate()const {
	return date;
}

int Recieved::returnNumEmpCard()const {
	return num_report_card;
}

#pragma endregion

// книги в наличии
#pragma region Available
Available::Available(string ISBN, string autor, string title, string genre, int yearMade, string edition, int count) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->count = count;
}

void Available::setter(string ISBN, string autor, string title, string genre, int yearMade, string edition, int count) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->count = count;
}

// вывод информации на  экран
void Available::view() const {
	cout << setw(20) << left << ISBN << setw(17) << left << autor << setw(28) << left <<
		title << setw(18) << left << genre << setw(6) << left << yearMade << setw(10) << left << edition << setw(6) << left << count << endl;
}

// запись в файл
void Available::print() {
	ofstream File_Data;
	File_Data.open("available.txt", ios::app);

	File_Data << endl;
	File_Data << ISBN << "\t" << autor << "\t" << title << "\t" << genre << "\t" << yearMade << "\t" << edition << "\t" << count;
	File_Data.close();
}

// просмотр всех книг в наличии
void Available::viewBooks() {
	ifstream File_Data;
	File_Data.open("available.txt");
	cout << setw(20) << left << "ISBN" << setw(17) << left << "Автор" << setw(28) << left << "Название" << setw(18) << left
		<< "Жанр" << setw(6) << left << "Год" << setw(10) << left << "Издат-во" << setw(6) << left << "Кол-во" << endl;
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
	{
		view();
	}
	File_Data.close();
}

// поиск книг в файле
void Available::search(int k, string key) {
	ifstream File_Data;
	File_Data.open("available.txt");
	int count1 = 0;

	//чтение из файла и вывод на экран книг, заданных критерием
	switch (k)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
		{
			if (title == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким названием" << endl;
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
		{
			if (autor == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг такого автора" << endl;
		break;
	case 3:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
		{
			if (ISBN == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, count);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким ISBN" << endl;
		break;
	default:
		break;
	}
	File_Data.close();
}

// сортировка книг в файле
void Available::sortBook(int k) {
	Available book;
	vector<Available> books;
	int count1 = 0;

	ifstream File_Data;
	File_Data.open("available.txt");

	// считывание книг из файла и запись в вектор
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
	{
		book.setter(ISBN, autor, title, genre, yearMade, edition, count);
		books.push_back(book);
		count1++;
	}
	File_Data.close();

	try {
		if (count1 == 0)
			throw "Количество равно 0";
	}
	catch (const char* s) {
		cout << "Нет книг в данной категории" << endl;
		return;
	}

	// сортировка вектора по определенному полю
	switch (k)
	{
	case 1:
		sort(books.begin(), books.end(), sortTitle<Available>);
		break;
	case 2:
		sort(books.begin(), books.end(), sortAutor<Available>);
		break;
	case 3:
		sort(books.begin(), books.end(), sortGenre<Available>);
		break;
	default:
		break;
	}
	File_Data.close();

	// очистка файла и запись в файл отсортированных книг
	ofstream File_Data1;
	File_Data1.open("available.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i].print();
	}
	cout << "Сортировка завершена успешно!" << endl;
}

// фильтрация книг в файле
void Available::filtration(int s, string key) {
	ifstream File_Data;
	File_Data.open("available.txt");
	int count1 = 0;
	Available book;
	//чтение из файла и вывод на экран книг, заданных кнритерием
	switch (s)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
		{
			if (autor == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, count);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого  автора" << endl;
		}
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
		{
			if (genre == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, count);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого жанра" << endl;
		}
		break;
	default:
		break;
	}
}

void Available::setCount(int count) {
	this->count = count;
}

string Available::returnISBN() const {
	return ISBN;
}

string Available::returnAutor() const{
	return autor;
}

string Available::returnTitle() const{
	return title;
}

string Available::returnGenre() const {
	return genre;
}

int Available::returnYearMade() const{
	return yearMade;
}

string Available::returnEdition() const{
	return edition;
}

int Available::returnCount() const {
	return this->count;
}

#pragma endregion

// выданные книги
#pragma region Issued
Issued::Issued(string ISBN, string autor, string title, string genre, int yearMade,
	string edition, int Num_card_reader, string date, int num_report_card) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->Num_card_reader = Num_card_reader;
	this->date = date;
	this->num_report_card = num_report_card;
}

void Issued::setter(string ISBN, string autor, string title, string genre, int yearMade,
			string edition, int Num_card_reader, string date, int num_report_card) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->Num_card_reader = Num_card_reader;
	this->date = date;
	this->num_report_card = num_report_card;
}

// запись в файл
void Issued::print() {
	ofstream File_Data;
	File_Data.open("issued.txt", ios::app);

	File_Data << endl;
	File_Data << ISBN << "\t" << autor << "\t" << title << "\t" << genre << "\t" << yearMade << "\t" << edition << "\t" << Num_card_reader << "\t" << date << "\t" << num_report_card;
	File_Data.close();
}

// вывод информации на  экран
void Issued::view() const {
	cout << setw(20) << left << ISBN << setw(17) << left << autor << setw(28) << left << title
		 << setw(18) << left << genre << setw(6) << left << yearMade << setw(10) << left << edition
		 << setw(15) << left << Num_card_reader << setw(18) << left << date << setw(18) << left << num_report_card << endl;
}

// просмотр всех выданных книг
void Issued::viewBooks() {
	ifstream File_Data;
	File_Data.open("issued.txt");
	cout << setw(20) << left << "ISBN" << setw(17) << left << "Автор" << setw(28) << left << "Название" << setw(18) << left
		<< "Жанр" << setw(6) << left << "Год" << setw(10) << left << "Изд-во" << setw(15) << left << "Чит.билет" <<
		setw(18) << left << "Дата выдачи" << setw(18) << left << "№табеля работника" << endl;
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
	{
			view();
	}
	File_Data.close();
}

// просмотр выданных книг читателю
void Issued::viewBooks(int& Num_Library_card) {
	ifstream File_Data;
	File_Data.open("issued.txt");
	int count = 0;
	cout << setw(20) << left << "ISBN" << setw(17) << left << "Автор" << setw(28) << left << "Название" << setw(18) << left
		<< "Жанр" << setw(6) << left << "Год" << setw(10) << left << "Изд-во" << setw(15) << left << "Чит.билет" <<
		setw(18) << left << "Дата выдачи" << setw(18) << left << "№табеля работника" << endl;
	
	// считываем из файла книги, записанные на читателя и выводим на экран
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
	{
		if (Num_card_reader == Num_Library_card) {
			view();
			count++;
		}
	}
	if (count == 0)
		cout << "У вас нет книг на руках." << endl;
	File_Data.close();
}

// проверка на выданные книги определенному читателю
int Issued::checkIssued(int& Num_Library_card) {
	ifstream File_Data;
	File_Data.open("issued.txt");
	int count = 0;

	// считывание из файла и подсчет книг, выданных определенному читателю
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
	{
		if (Num_card_reader == Num_Library_card)
			count++;
	}
	File_Data.close();
	return count;
}

// поиск книг в файле
void Issued::search(int k, string key) {
	ifstream File_Data;
	File_Data.open("issued.txt");
	int count1 = 0;

	//чтение из файла и вывод на экран книг, заданных критерием
	switch (k)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
		{
			if (title == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким названием" << endl;
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
		{
			if (autor == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг такого автора" << endl;
		break;
	case 3:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
		{
			if (ISBN == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader, date, num_report_card);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким ISBN" << endl;
		break;
	default:
		break;
	}
	File_Data.close();
}

// сортировка книг в файле
void Issued::sortBook(int k) {
	Issued book;
	vector<Issued> books;
	int count1 = 0;

	ifstream File_Data;
	File_Data.open("issued.txt");

	// считывание книг из файла и запись в вектор
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
	{
		book.setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader, date, num_report_card);
		books.push_back(book);
		count1++;
	}
	File_Data.close();

	try {
		if (count1 == 0)
			throw "Количество равно 0";
	}
	catch (const char* s) {
		cout << "Нет книг в данной категории" << endl;
		return;
	}
	
	// сортировка вектора по определенному полю
	switch (k)
	{
	case 1:
		sort(books.begin(), books.end(), sortTitle<Issued>);
		break;
	case 2:
		sort(books.begin(), books.end(), sortAutor<Issued>);
		break;
	case 3:
		sort(books.begin(), books.end(), sortGenre<Issued>);
		break;
	default:
		break;
	}
	File_Data.close();

	// очистка файла и запись в файл отсортированных книг
	ofstream File_Data1;
	File_Data1.open("issued.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i].print();
	}
	cout << "Сортировка завершена успешно!" << endl;
}

// фильтрация книг в файле
void Issued::filtration(int s, string key) {
	ifstream File_Data;
	File_Data.open("issued.txt");
	int count1 = 0;
	Issued book;
	//чтение из файла и вывод на экран книг, заданных кнритерием
	switch (s)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
		{
			if (autor == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader, date, num_report_card);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого  автора" << endl;
		}
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card)
		{
			if (genre == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader, date, num_report_card);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого жанра" << endl;
		}
		break;
	default:
		break;
	}
}

string Issued::returnISBN()const {
	return ISBN;
}

string Issued::returnAutor()const {
	return autor;
}

string Issued::returnTitle()const {
	return title;
}

string Issued::returnGenre()const {
	return genre;
}

int Issued::returnYearMade()const {
	return yearMade;
}

string Issued::returnEdition()const {
	return edition;
}

int Issued::returnNumCard()const {
	return Num_card_reader;
}

string Issued::returnDate()const {
	return date;
}

int Issued::returnNumEmpCard()const {
	return num_report_card;
}

#pragma endregion

// забронированные книги
#pragma region Reserved
Reserved::Reserved(string ISBN, string autor, string title, string genre, int yearMade, string edition, int Num_card_reader) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->Num_card_reader = Num_card_reader;
}


void Reserved::setter(string ISBN, string autor, string title, string genre, int yearMade, string edition, int Num_card_reader) {
	this->ISBN = ISBN;
	this->autor = autor;
	this->title = title;
	this->genre = genre;
	this->yearMade = yearMade;
	this->edition = edition;
	this->Num_card_reader = Num_card_reader;
}

// запись в файл
void Reserved::print() {
	ofstream File_Data;
	File_Data.open("reserved.txt", ios::app);

	File_Data << endl;
	File_Data << ISBN << "\t" << autor << "\t" << title << "\t" << genre << "\t" << yearMade << "\t" << edition << "\t" << Num_card_reader;
	File_Data.close();
}

// вывод информации на  экран
void Reserved::view() const {
	cout << setw(20) << left << ISBN << setw(17) << left << autor << setw(28) << left <<
		title << setw(18) << left << genre << setw(6) << left << yearMade << setw(10) << left <<
		edition << setw(15) << left << Num_card_reader << endl;
}

// просмотр всех забронированных книг
void Reserved::viewBooks() {
	ifstream File_Data;
	File_Data.open("reserved.txt");
	cout << setw(20) << left << "ISBN" << setw(17) << left << "Автор" << setw(28) << left << "Название" << setw(18) << left
		<< "Жанр" << setw(6) << left << "Год" << setw(10) << left << "Изд-во" << setw(15) << left << "Чит.билет" << endl;
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
		view();
	
	File_Data.close();
}

// просмотр заюронированных книг определенным читателем
void Reserved::viewBooks(int& Num_library_card) {
	ifstream File_Data;
	File_Data.open("reserved.txt");
	int count = 0;
	cout << setw(20) << left << "ISBN" << setw(17) << left << "Автор" << setw(28) << left << "Название" << setw(18) << left
		<< "Жанр" << setw(6) << left << "Год" << setw(10) << left << "Изд-во" << setw(15) << left << "Чит.билет" << endl;
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
	{
		if (Num_card_reader == Num_library_card) {
			view();
			count++;
		}
	}
	if (count == 0)
		cout << "У вас нет забронированных книг. Забронируйте!" << endl;
	File_Data.close();
}

// поиск книг в файле
void Reserved::search(int k, string key) {
	ifstream File_Data;
	File_Data.open("written_off.txt");
	int count1 = 0;

	//чтение из файла и вывод на экран книг, заданных критерием
	switch (k)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
		{
			if (title == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким названием" << endl;
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
		{
			if (autor == key) {
				setter(ISBN, autor, title, genre, yearMade, edition,Num_card_reader);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг такого автора" << endl;
		break;
	case 3:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
		{
			if (ISBN == key) {
				setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader);
				view();
				count1++;
			}
		}
		if (count1 == 0)
			cout << "Нет книг с таким ISBN" << endl;
		break;
	default:
		break;
	}
	File_Data.close();
}

// сортировка книг в файле
void Reserved::sortBook(int k) {
	Reserved book;
	vector<Reserved> books;
	int count1 = 0;

	ifstream File_Data;
	File_Data.open("reserved.txt");

	// считывание книг из файла и запись в вектор
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
	{
		book.setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader);
		books.push_back(book);
		count1++;
	}
	File_Data.close();

	try {
		if (count1 == 0)
			throw "Количество равно 0";
	}
	catch (const char* s) {
		cout << "Нет книг в данной категории" << endl;
		return;
	}
	
	// сортировка вектора по определенному полю
	switch (k)
	{
	case 1:
		sort(books.begin(), books.end(), sortTitle<Reserved>);
		break;
	case 2:
		sort(books.begin(), books.end(), sortAutor<Reserved>);
		break;
	case 3:
		sort(books.begin(), books.end(), sortGenre<Reserved>);
		break;
	default:
		break;
	}
	File_Data.close();

	// очистка файла и запись в файл отсортированных книг
	ofstream File_Data1;
	File_Data1.open("reserved.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i].print();
	}
	cout << "Сортировка завершена успешно!" << endl;
}

// фильтрация книг в файле
void Reserved::filtration(int s, string key) {
	ifstream File_Data;
	File_Data.open("reserved.txt");
	int count1 = 0;
	Reserved book;
	//чтение из файла и вывод на экран книг, заданных кнритерием
	switch (s)
	{
	case 1:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
		{
			if (autor == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого  автора" << endl;
		}
		break;
	case 2:
		while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
		{
			if (genre == key) {
				book.setter(ISBN, autor, title, genre, yearMade, edition, Num_card_reader);
				book.view();
				count1++;
			}
		}
		try {
			if (count1 == 0)
				throw "Количество равно 0";
		}
		catch (const char* s) {
			cout << "Нет книг такого жанра" << endl;
		}
		break;
	default:
		break;
	}
}

int Reserved::checkReserved(int& Num_library_card) {
	ifstream File_Data;
	File_Data.open("reserved.txt");
	int count = 0;
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader)
	{
		if (Num_card_reader == Num_library_card)
			count++;
	}
	File_Data.close();
	return count;
}

string Reserved::returnISBN()const {
	return ISBN;
}

string Reserved::returnAutor()const {
	return autor;
}

string Reserved::returnTitle()const {
	return title;
}

string Reserved::returnGenre()const {
	return genre;
}

int Reserved::returnYearMade()const {
	return yearMade;
}

string Reserved::returnEdition()const {
	return edition;
}

int Reserved::returnNumCard()const {
	return Num_card_reader;
}
#pragma endregion