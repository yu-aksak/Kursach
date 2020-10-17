#include "Reader.hpp"
#include "Book.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include "SmartPointer.hpp"
using namespace std;

Reader::Reader(int Num_card, string FirstName, string Name, string SecondName, string Adress, string Phone) {
	Num_Library_card = Num_card;
	firstName = FirstName;
	name = Name;
	secondName = SecondName;
	adress = Adress;
	phone = Phone;
}

void Reader::setter(int Num_card, string FirstName, string Name, string SecondName, string Adress, string Phone) {
	Num_Library_card = Num_card;
	firstName = FirstName;
	name = Name;
	secondName = SecondName;
	adress = Adress;
	phone = Phone;
}

void Reader::set(int& login) {
	ifstream File_Data;
	File_Data.open("readersInfo.txt");
	while (File_Data >> Num_Library_card >> firstName >> name >> secondName >> adress >> phone)
	{
		if (Num_Library_card == login)
			break;
	}
}

void Reader::setFirstName(const string& FirstName) {
	firstName = FirstName;
}

void Reader::setName(const string& Name) {
	name = Name;
}

void Reader::setSecondName(const string& SecondName) {
	secondName = SecondName;
}

void Reader::setAdress(const string& Adress) {
	adress = Adress;
}

void Reader::setPhone(const string& Phone) {
	phone = Phone;
}

//����� ������ ������ �������� �� �����
ostream& operator<<(ostream& out, const Reader& A)
{
	out << setw(10) << left << A.Num_Library_card << setw(15) << left << A.firstName << setw(10)
		<< left << A.name << setw(15) << left << A.secondName << setw(40) << left << A.adress << setw(10) << left << A.phone << endl;
	return out;
}

//������ ������ ������ � ����
void Reader::print() {
	ofstream File_Data;
	File_Data.open("readersInfo.txt", ios::app);

	File_Data << endl;
	File_Data << Num_Library_card << "\t" << firstName << "\t" << name << "\t" << secondName << "\t" << adress << "\t" << phone;
	File_Data.close();
}

//�������������� ������ ������
void Reader::editInfo(int s, string change) {
	ifstream File_Data;
	vector<SmartPointer<Reader>> readers;
	string FirstName, Name, SecondName, Adress, Phone;
	int num_Library_card;
	File_Data.open("readersInfo.txt", ios::app);
	//��������� ��������� �� ����� � ��������� � ������, ����� ����, ������ ������ �������� ����� ����������
	while (File_Data >> num_Library_card >> FirstName >> Name >> SecondName >> Adress >> Phone)
	{
		if (num_Library_card != Num_Library_card)
			readers.push_back(new Reader(num_Library_card, FirstName, Name, SecondName, Adress, Phone));
	}
	File_Data.close();
	//������ ������ ������ ������������ � ������������ � ����������� ������
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
		setAdress(change);
		break;
	case 5:
		setPhone(change);
		break;
	default:
		break;
	}
	//������� ����
	ofstream File_Data1;
	File_Data1.open("readersInfo.txt");
	File_Data1.close();
	//���������� ������ ������ ���������, ����� ������ ������������
	for (size_t i = 0; i < readers.size(); i++)
		readers[i]->print();
	//���������� ������ ������ ������������
	print();
	cout << "��������� ������� �������" << endl;
}

//�������� ���� � �������
void Reader::viewBooks() {
	SmartPointer<Available> book(new Available());
	book->viewBooks();
}

//�������� ����, ������/��������������� �������������
template<class T>
void Reader::viewBooksR() {
	SmartPointer<T> book(new T());
	book->viewBooks(Num_Library_card);
}
template void Reader::viewBooksR<Reserved>();
template void Reader::viewBooksR<Issued>();

//����� ����� ���� � �������
void Reader::search(int k, string key) {
	SmartPointer<Available> book(new Available());
	book->search(k, key);
}

//���������� ���� ����� ���� � �������
void Reader::filtration(int k, string key) {
	SmartPointer<Available> book(new Available());
	book->filtration(k, key);
}

//������������ ����� �������������
void Reader::reserve(string Title, string Autor) {
	ifstream File_Data;
	File_Data.open("available.txt");
	vector<SmartPointer<Available>> books;
	string ISBN, autor, title, genre, edition;
	int count = 0, yearMade = 0, count1 = 0, countIR = 0;
	SmartPointer<Reserved> book1(new Reserved());
	SmartPointer<Issued> book2(new Issued());
	//�������� �� ���������� ���������������/������ ����
	try {
		countIR += book2->checkIssued(Num_Library_card) + book1->checkReserved(Num_Library_card);
		if (countIR == 5)
			throw "���������� ����� 5";
	}
	catch (const char* s) {
		cout << "� ��� � ����� �� ����� � ������������� 5 ����. \n�� ������ �� ������ ������������� �����.\n������ �����, ��� ������� �� ������ �������." << endl;
		return;
	}
	//��������� ���������� �� ����� � ��������� � ������, ����� ��� �����, ������� ����� �������������, ��� ��� ��������� ���������� ����������� ���� � �������
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMade >> edition >> count)
	{
		if ((title == Title) && (autor == Autor)) {
			if ((count--) != 0) {
				books.push_back(new Available(ISBN, autor, title, genre, yearMade, edition, count));
			}
			book1->setter(ISBN, autor, title, genre, yearMade, edition, Num_Library_card);
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
	cout << "������������ ��������� �������!" << endl;
}

//������ �� ������ �������
void Reader::remove(string Autor, string Title) {
	vector<SmartPointer<Reserved>> books;
	string ISBN, autor, title, genre, edition; int Num_card, yearMake, count, count1 = 0;
	vector<SmartPointer<Available>> books1;
	ifstream File_Data1;
	File_Data1.open("available.txt");
	//��������� ������ �� ����� available � ���������� � ������
	while (File_Data1 >> ISBN >> autor >> title >> genre >> yearMake >> edition >> count)
		books1.push_back(new Available(ISBN, autor, title, genre, yearMake, edition, count));
	
	File_Data1.close();
	//��������� ������ �� ����� � ��������� � ������ ����� ���, ��� ������� �� ������ �������, ����������� ���������� ����, ������� ������� � ����������, �� 1
	ifstream File_Data;
	File_Data.open("reserved.txt");
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMake >> edition >> Num_card)
	{
		if (autor == Autor && title == Title && Num_card == Num_Library_card) {
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
			books.push_back(new Reserved(ISBN, autor, title, genre, yearMake, edition, Num_Library_card));
	}
	File_Data.close();
	try {
		if (count1 == 0)
			throw "���������� ����� 0";
	}
	catch (const char* s) {
		cout << "� ��� ��� ����� ��������������� �����. ��������� ������������ ��������� ������." << endl;
		return;
	}
	//������� ���� t � ���������� ����� ������
	ofstream File_Data2;
	File_Data2.open("reserved.txt");
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
	cout << "�������� �� ������ ������� ��������� �������!" << endl;
}

//�������� �� ������� ���� �� �����
void Reader::check() {
	ifstream File_Data;
	File_Data.open("reserved.txt");
	SmartPointer<Reserved> book(new Reserved());
	string ISBN, autor, title, genre, edition; int Num_card, yearMake, count1 = 0;
	//��������� ������ �� ����� � ������� ���������� ���, ��� ������������� ������������
	while (File_Data >> ISBN >> autor >> title >> genre >> yearMake >> edition >> Num_card)
	{
		book->setter(ISBN, autor, title, genre, yearMake, edition, Num_card);
		if (book->returnNumCard() == Num_Library_card)
			count1++;
	}
	File_Data.close();
	if (count1 == 0)
		throw false;
}