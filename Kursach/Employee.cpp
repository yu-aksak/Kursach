#include "Employee.hpp"
#include "Book.hpp"
// ����������� ���������� C++
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
// ���� header �����
#include "SmartPointer.hpp"
// ����������� ������������ ���� (��� �����������, ��� � ����)
using namespace std;

Employee::Employee(int Num_card, string FirstName, string Name, string SecondName, string Position) {
	num_report_card = Num_card;
	firstName = FirstName;
	name = Name;
	secondName = SecondName;
	position = Position;
}

// ����� ������ ����, ������� ������������ ���������
void Employee::viewBooks(int login)const {
	SmartPointer<Issued> book(new Issued());
	book->viewBooks(login);
}

// �������� ���������� � ���������, ������� ������������ �����
void Employee::viewBookReaders(string Autor, string Title) {
	ifstream File_Data;
	File_Data.open("issued.txt");
	vector<int> num_cards;
	int yearMade, Num_card_reader, num_report_card, count = 0;
	string ISBN, autor, title, genre, edition, date, firstName, name, secondName, adress, phone;

	// ��������� �� ����� � ��������� � ������ ������ ������������ ������� ��� ���������, ������� ����� ������������ �����
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> Num_card_reader >> date >> num_report_card) {
		if (autor == Autor && title == Title) {
			num_cards.push_back(Num_card_reader);
			count++;
		}
	}
	if (count == 0) {
		cout << "��� ����� ����� � ������ ������" << endl;
		return;
	}
	File_Data.close();
	ifstream File_Data1;
	File_Data1.open("readersInfo.txt");
	// ���������� �� ����� ���������� ��� ���������, ������ ������������ ������� ������� ��������� � ������� � ������� �� �����
	for (size_t i = 0; i < num_cards.size(); i++) {
		
		while (File_Data1 >> Num_card_reader >> firstName >> name >> secondName >> adress >> phone) {
			if (num_cards[i] == Num_card_reader)
				cout << setw(10) << left << Num_card_reader << setw(15) << left << firstName << setw(10)
					<< left << name << setw(15) << left << secondName << setw(40) << left << adress << setw(10) << left << phone << endl;
		}
		File_Data1.seekg(0);
	}
	File_Data1.close();
}

// �������� ���������� � ���� ���������
void Employee::viewReaders() {
	ifstream File_Data;
	File_Data.open("readersInfo.txt");
	int Num_card_reader;
	string firstName, name, secondName, adress, phone;
	while (File_Data >> Num_card_reader >> firstName >> name >> secondName >> adress >> phone) {
		cout << setw(10) << left << Num_card_reader << setw(15) << left << firstName << setw(10)
			<< left << name << setw(15) << left << secondName << setw(40) << left << adress << setw(10) << left << phone << endl;
	}

	File_Data.close();
}

// ������ � ���� ������ ������
void Employee::print() {
	ofstream File_Data;
	File_Data.open("employeesInfo.txt", ios::app);

	File_Data << endl;
	File_Data << num_report_card << "\t" << firstName << "\t" << name << "\t" << secondName << "\t" << position;
	File_Data.close();
}

void Employee::setter(int Num_card, string FirstName, string Name, string SecondName, string Position) {
	num_report_card = Num_card;
	firstName = FirstName;
	name = Name;
	secondName = SecondName;
	position = Position;
}

void Employee::set(int& login) {
	ifstream File_Data;
	File_Data.open("employeesInfo.txt");
	while (File_Data >> num_report_card >> firstName >> name >> secondName >> position)
	{
		if (num_report_card == login)
			break;
	}
}

ostream& operator<<(ostream& out, const Employee& A)
{
	out << setw(10) << left << A.num_report_card << setw(15) << left << A.firstName << setw(10)
		<< left << A.name << setw(15) << left << A.secondName << setw(25) << left << A.position << endl;
	return out;
}

void Employee::setFirstName(const string& firstName) {
	this->firstName = firstName;
}

void Employee::setName(const string& name) {
	this->name = name;
}

void Employee::setSecondName(const string& secondName) {
	this->secondName = secondName;
}

void Employee::setPosition(const string& position) {
	this->position = position;
}

// �������������� ������ ������ ���������
void Employee::editInfo(int s, string change) {
	ifstream File_Data;
	File_Data.open("employeesInfo.txt", ios::app);
	vector<SmartPointer<Employee>> employees;
	int Num_report_card;	string FirstName, Name, SecondName, Position;
	// ���������� �� ����� � ���������� � ������ ������ ������ ���� ����������
	while (File_Data >> Num_report_card >> FirstName >> Name >> SecondName >> Position)
	{
		employees.push_back(new Employee(Num_report_card, FirstName, Name, SecondName, Position));
	}
	File_Data.close();
	// ������� �� ������� ��������� ���������, ������� �������� ���� ������ ������
	for (size_t i = 0; i < employees.size(); ++i)
	{
		if (employees[i]->num_report_card == num_report_card) {
			employees.erase(employees.begin() + i);
		}

	}
	// ������� ���� � ������� ������� � ���������
	ofstream File_Data1;
	File_Data1.open("employeesInfo.txt");
	File_Data1.close();
	// �������� ����, ������� �����
	switch (s)
	{
	case 1:
		setFirstName(change);
		break;
	case 2:
		setName(change);
		break;
	case 3:
		setSecondName(change);
		break;
	case 4:
		setPosition(change);
		break;
	default:
		break;
	}
	// ���������� � ���� ������ ����������
	for (size_t i = 0; i < employees.size(); i++)
	{
		employees[i]->print();
	}
	print();
	cout << "������ ������� ��������!" << endl;
}

// �������� ����
template<class T>
void Employee::viewBooks()const {
	SmartPointer<T> book(new T());
	book->viewBooks();
}
template void Employee::viewBooks<Available>()const;
template void Employee::viewBooks<Reserved>()const;
template void Employee::viewBooks<Issued>()const;
template void Employee::viewBooks<Recieved>()const;
template void Employee::viewBooks<Written_off>()const;

// �������� �� �������� �����
void Employee::checkIssued(int num_card, string Autor, string Title) {
	ifstream File_Data;
	File_Data.open("issued.txt");
	string ISBN, autor, title, genre, edition, date; int Num_card, yearMake, Num_repord_card;
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMake >> edition >> Num_card >> date >> Num_repord_card) {
		if (autor == Autor && title == Title && Num_card == num_card)
			throw "� ����� �������� ��� ���� ����� �����.";
	}
	File_Data.close();
}

// ������ ����� �������� �� ������ ���������������
void Employee::giveBook(int Login, string date) {
	try {
		checkReader(Login);
	}
	catch (const char* s) {
		cout << "��� �������� � ����� ������������ �������. ��������� ������������ �������� ������" << endl;
		return;
	}

	ifstream File_Data;
	File_Data.open("reserved.txt");
	vector<SmartPointer<Reserved>> books;
	string ISBN, autor, title, genre, edition; int Num_card, yearMake, countI = 0;
	SmartPointer<Issued> book1(new Issued());
	int count = 0;
	try {
		countI += book1->checkIssued(Login);
		if (countI == 5)
			throw "���������� ����� 5";
	}
	catch (const char* s) {
		cout << "� ��� �� ����� 5 ����. \n�� ������ �� ������ ����� �����.\n������ �����." << endl;
		return;
	}

	//��������� ��������������� ����� ��������� �� ����� � ��������� � ������ ����� ���, ������� �������� � ���������� � ���� issued
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMake >> edition >> Num_card)
	{
		try {
			checkIssued(Login, autor, title);
		}
		catch (const char* s) {
			cout << "� ����� �������� ��� ���� �����"  << autor << "\t" << title << endl;
			continue;
		}
		if (Num_card != Login) {
			books.push_back(new Reserved(ISBN, autor, title, genre, yearMake, edition, Num_card));
		}
		else {
			book1->setter(ISBN, autor, title, genre, yearMake, edition, Num_card, date,num_report_card);
			book1->print();
			count++;
		}
	}
	if (count == 0) {
		cout << "� ����� �������� ��� ��������������� ����." << endl;
		return;
	}
	File_Data.close();
	//������� ����
	ofstream File_Data1;
	File_Data1.open("reserved.txt");
	File_Data1.close();
	//���������� ����� ������ � ����
	for (size_t i = 0; i < books.size(); i++) {
		books[i]->print();
	}
	cout << "����� ������� ������!" << endl;
}

// ������ �������� ����� �� ������ � �������
void Employee::giveBook(int Login, string date, string Autor, string Title) {
	try {
		checkReader(Login);
	}
	catch (const char* s) {
		cout << "��� �������� � ����� ������������ �������. ��������� ������������ �������� ������" << endl;
		return;
	}
	ifstream File_Data;
	File_Data.open("available.txt");
	vector<SmartPointer<Available>> books;
	string ISBN, autor, title, genre, edition;
	int count = 0, yearMade = 0, count1 = 0, countI = 0;
	SmartPointer<Issued> book1(new Issued());
	//�������� �� ���������� ������ ����
	try {
		countI += book1->checkIssued(Login);
		if (countI == 5)
			throw "���������� ����� 5";
	}
	catch (const char* s) {
		cout << "� ��� �� ����� 5 ����. \n�� ������ �� ������ ����� �����.\n������ �����." << endl;
		return;
	}
	try {
		checkIssued(Login, autor, title);
	}
	catch (const char* s) {
		cout << "� ����� �������� ��� ���� �����" << autor << "\t" << title << endl;
	}
	//��������� ���������� �� ����� � ��������� � ������, ����� ��� �����, ������� ����� �������������, ��� ��� ��������� ���������� ����������� ���� � �������
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
	{
		if ((title == Title) && (autor == Autor)) {
			if ((--count) != 0) {
				books.push_back(new Available(ISBN, autor, title, genre, yearMade, edition, count));
			}
			book1->setter(ISBN, autor, title, genre, yearMade, edition, Login, date, num_report_card);
			book1->print();
			count1++;
		}
		else {
			books.push_back(new Available(ISBN, autor, title, genre, yearMade, edition, count));
		}
	}
	File_Data.close();

	try {
		if (count1 == 0)
			throw "���������� ����� 0.";
	}
	catch (const char* s) {
		cout << "� ������ ���� ��� ����� ������ ������ � ����� ���������. ��������� ������������ ��������� ������" << endl;
		return;
	}
	//������� ���� � ���������� � ���� ����� ������
	ofstream File_Data1;
	File_Data1.open("available.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i]->print();
	}
	cout << "�� ������� ������ �����!" << endl;
}

// ������� ����� � ��������
void Employee::acceptBook(int Login, string Autor, string Title) {
	try {
		checkReader(Login);
	}
	catch (const char* s) {
		cout << "��� �������� � ����� ������������ �������. ��������� ������������ �������� ������" << endl;
		return;
	}
	vector<SmartPointer<Issued>> books;
	string ISBN, autor, title, genre, edition, date; int Num_card, yearMake, count, count1 = 0, Num_report_card;
	vector<SmartPointer<Available>> books1;
	ifstream File_Data1;
	File_Data1.open("available.txt");
	//��������� ������ �� ����� available � ���������� � ������
	while (File_Data1 >> ISBN >> autor >> title >> genre >> yearMake >> edition >> count) {
		books1.push_back(new Available(ISBN, autor, title, genre, yearMake, edition, count));
	}
	File_Data1.close();
	//��������� ������ �� ����� � ��������� � ������ ����� ���, ��� ������� �� ������ �������, ����������� ���������� ����, ������� ������� � ����������, �� 1
	ifstream File_Data;
	File_Data.open("issued.txt");
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMake >> edition >> Num_card >> date >> Num_report_card)
	{
		if (autor == Autor && title == Title && Num_card == Login) {
			for (size_t i = 0; i < books1.size(); i++) {
				if (books1[i]->returnAutor() == Autor && books1[i]->returnTitle() == Title) {
					count = books1[i]->returnCount();
					books1[i]->setter(ISBN, autor, title, genre, yearMake, edition, ++count);
					break;
				}
			}
			count1++;
		}
		else
			books.push_back(new  Issued(ISBN, autor, title, genre, yearMake, edition, Num_card, date, Num_report_card));
	}
	File_Data.close();
	
	try {
		if (count1 == 0)
			throw "���������� ����� 0";
	}
	catch (const char* s) {
		cout << "� ��� ��� ����� ����� �� �����. ��������� ������������ ��������� ������." << endl;
		return;
	}
	//������� ���� t � ���������� ����� ������
	ofstream File_Data2;
	File_Data2.open("issued.txt");
	File_Data2.close();
	for (size_t i = 0; i < books.size(); i++) {
		books[i]->print();
	}
	//������� ���� available � ���������� ����� ������
	ofstream File_Data3;
	File_Data3.open("available.txt");
	File_Data3.close();
	for (size_t i = 0; i < books1.size(); i++) {
		books1[i]->print();
	}
	cout << "����� ������� ������� � ����������!" << endl;
}

// �������� �� ������������� ��������
void Employee::checkReader(int Login) {
	ifstream File_Data;
	File_Data.open("readersInfo.txt");
	int Num_Library_card;
	string FirstName, Name, SecondName, Adress, Phone;
	while (File_Data >> Num_Library_card >> FirstName >> Name >> SecondName >> Adress >> Phone)
	{
		if (Num_Library_card == Login)
			return;
	}
	throw "��� �������� � ����� �������";
}

template<class T>
void Employee::search(int s) {
	string ISBN, autor, title;
	switch (s)
	{
	case 1:
		cout << "������� �������� �����" << endl;
		cin >> title;
		searchBook<T>(1, title);
		break;
	case 2:
		cout << "������� ������ �����" << endl;
		cin >> autor;
		searchBook<T>(2, autor);
		break;
	case 3:
		cout << "������� ISBN �����" << endl;
		cin >> ISBN;
		searchBook<T>(3, ISBN);
		break;
	default:
		break;
	}
}
template void Employee::search<Available>(int);
template void Employee::search<Written_off>(int);
template void Employee::search<Issued>(int);
template void Employee::search<Recieved>(int);
template void Employee::search<Reserved>(int);

template<class T>
void Employee::searchBook(int k, string key) {
	SmartPointer<T> book(new T());
	book->search(k, key);
}
template void Employee::searchBook<Available>(int, string);
template void Employee::searchBook<Written_off>(int, string);
template void Employee::searchBook<Issued>(int, string);
template void Employee::searchBook<Recieved>(int, string);
template void Employee::searchBook<Reserved>(int, string);

template<class T>
void Employee::sortBook(int k) {
	SmartPointer<T> book(new T());
	book->sortBook(k);
}
template void Employee::sortBook<Available>(int);
template void Employee::sortBook<Reserved>(int);
template void Employee::sortBook<Issued>(int);
template void Employee::sortBook<Recieved>(int);
template void Employee::sortBook<Written_off>(int);

template<class T>
void Employee::filtration(int f) {
	string ISBN, autor, title;
	switch (f)
	{
	case 1:
		cout << "������� ������ �����" << endl;
		cin >> autor;
		filtrationBook<T>(1, autor);
		break;
	case 2:
		cout << "������� ���� �����" << endl;
		cin >> ISBN;
		filtrationBook<T>(2, ISBN);
		break;
	default:
		break;
	}
}
template void Employee::filtration<Available>(int);
template void Employee::filtration<Reserved>(int);
template void Employee::filtration<Issued>(int);
template void Employee::filtration<Recieved>(int);
template void Employee::filtration<Written_off>(int);

template<class T>
void Employee::filtrationBook(int k, string key) {
	SmartPointer<T> book(new T());
	book->filtration(k, key);
}
template void Employee::filtrationBook<Available>(int, string);
template void Employee::filtrationBook<Reserved>(int, string);
template void Employee::filtrationBook<Issued>(int, string);
template void Employee::filtrationBook<Recieved>(int, string);
template void Employee::filtrationBook<Written_off>(int, string);

void Employee::addBook(string ISBN, string autor, string title, string genre,
	int yearMade, string edition, int count, string date) {
	SmartPointer<Recieved> book(new Recieved());
	book->setter(ISBN, autor, title, genre, yearMade, edition, count, date, num_report_card);
	book->print();
	book->addAvailable();
}

void Employee::deleteBook(string isbn, int Count, string date) {
	ifstream File_Data;
	File_Data.open("available.txt");
	vector<SmartPointer<Available>> books;
	string ISBN, autor, title, genre, edition;
	int count = 0, yearMade = 0, count1 = 0, countIR = 0;
	SmartPointer<Written_off> book1(new Written_off());
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
	{
		if (ISBN == isbn) {
			if ((count-Count) > 0) {
				books.push_back(new Available(ISBN, autor, title, genre, yearMade, edition, count - Count));
			}
			book1->setter(ISBN, autor, title, genre, yearMade, edition, Count, date, num_report_card);
			book1->print();
			count1++;
		}
		else {
			books.push_back(new Available(ISBN, autor, title, genre, yearMade, edition, count));
		}
	}
	File_Data.close();
	try {
		if (count1 == 0)
			throw "���������� ����� 0.";
	}
	catch (const char* s) {
		cout << "� ������ ���� ��� ����� ������ ������ � ����� ���������. ��������� ������������ ��������� ������" << endl;
		return;
	}
	ofstream File_Data1;
	File_Data1.open("available.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i]->print();
	}
	cout << "�������� ��������� �������!" << endl;

}