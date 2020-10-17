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

//вывод личных данных читателя на экран
ostream& operator<<(ostream& out, const Reader& A)
{
	out << setw(10) << left << A.Num_Library_card << setw(15) << left << A.firstName << setw(10)
		<< left << A.name << setw(15) << left << A.secondName << setw(40) << left << A.adress << setw(10) << left << A.phone << endl;
	return out;
}

//запись личных данных в файл
void Reader::print() {
	ofstream File_Data;
	File_Data.open("readersInfo.txt", ios::app);

	File_Data << endl;
	File_Data << Num_Library_card << "\t" << firstName << "\t" << name << "\t" << secondName << "\t" << adress << "\t" << phone;
	File_Data.close();
}

//редактирование личных данных
void Reader::editInfo(int s, string change) {
	ifstream File_Data;
	vector<SmartPointer<Reader>> readers;
	string FirstName, Name, SecondName, Adress, Phone;
	int num_Library_card;
	File_Data.open("readersInfo.txt", ios::app);
	//считываем читателей из файла и добавляем в вектор, кроме того, личные данные которого будут изменяться
	while (File_Data >> num_Library_card >> FirstName >> Name >> SecondName >> Adress >> Phone)
	{
		if (num_Library_card != Num_Library_card)
			readers.push_back(new Reader(num_Library_card, FirstName, Name, SecondName, Adress, Phone));
	}
	File_Data.close();
	//меняем личные данные пользователя в соответствии с изменяемыми полями
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
	//очищаем файл
	ofstream File_Data1;
	File_Data1.open("readersInfo.txt");
	File_Data1.close();
	//записываем личные данные читателей, кроме данных пользователя
	for (size_t i = 0; i < readers.size(); i++)
		readers[i]->print();
	//записываем личные данные пользователя
	print();
	cout << "Изменения внесены успешно" << endl;
}

//просмотр книг в наличии
void Reader::viewBooks() {
	SmartPointer<Available> book(new Available());
	book->viewBooks();
}

//просмотр книг, взятых/забронированных пользователем
template<class T>
void Reader::viewBooksR() {
	SmartPointer<T> book(new T());
	book->viewBooks(Num_Library_card);
}
template void Reader::viewBooksR<Reserved>();
template void Reader::viewBooksR<Issued>();

//поиск среди книг в наличии
void Reader::search(int k, string key) {
	SmartPointer<Available> book(new Available());
	book->search(k, key);
}

//фильтрация книг среди книг в наличии
void Reader::filtration(int k, string key) {
	SmartPointer<Available> book(new Available());
	book->filtration(k, key);
}

//бронирование книги пользователем
void Reader::reserve(string Title, string Autor) {
	ifstream File_Data;
	File_Data.open("available.txt");
	vector<SmartPointer<Available>> books;
	string ISBN, autor, title, genre, edition;
	int count = 0, yearMade = 0, count1 = 0, countIR = 0;
	SmartPointer<Reserved> book1(new Reserved());
	SmartPointer<Issued> book2(new Issued());
	//проверка на количество забронированных/взятых книг
	try {
		countIR += book2->checkIssued(Num_Library_card) + book1->checkReserved(Num_Library_card);
		if (countIR == 5)
			throw "Количество равно 5";
	}
	catch (const char* s) {
		cout << "У вас в сумме на руках и забронировано 5 книг. \nВы больше не можете забронировать книгу.\nСдайте книгу, или удалите из списка заказов." << endl;
		return;
	}
	//считываем информацию из файла и добавляем в вектор, кроме той книги, которую нужно забронировать, при чем уменьшаем количество экземпляров книг в наличии
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
			throw "Количество равно 0.";
	}
	catch (const char* s) {
		cout << "В списке книг нет книги такого автора с таким названием. Проверьте правильность введенных данных" << endl;
		return;
	}
	//очищаем файл и записываем в него новые данные
	ofstream File_Data1;
	File_Data1.open("available.txt");
	File_Data1.close();
	for (size_t i = 0; i < books.size(); i++)
	{
		books[i]->print();
	}
	cout << "Бронирование завершено успешно!" << endl;
}

//убрать из списка заказов
void Reader::remove(string Autor, string Title) {
	vector<SmartPointer<Reserved>> books;
	string ISBN, autor, title, genre, edition; int Num_card, yearMake, count, count1 = 0;
	vector<SmartPointer<Available>> books1;
	ifstream File_Data1;
	File_Data1.open("available.txt");
	//считываем данные из файла available и дообавляем в вектор
	while (File_Data1 >> ISBN >> autor >> title >> genre >> yearMake >> edition >> count)
		books1.push_back(new Available(ISBN, autor, title, genre, yearMake, edition, count));
	
	File_Data1.close();
	//считываем данные из файла и добавляем в вектор кроме тех, что удаляем из списка заказов, увелияиваем количество книг, которые вернули в библиотеку, на 1
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
			throw "Количество равно 0";
	}
	catch (const char* s) {
		cout << "У вас нет такой забронированной книги. Проверьте правильность введенных данных." << endl;
		return;
	}
	//очищаем файл t и записываем новые данные
	ofstream File_Data2;
	File_Data2.open("reserved.txt");
	File_Data2.close();
	for (size_t i = 0; i < books.size(); i++) {
		books[i]->print();
	}
	//очищаем файл available и записываем новые данные
	ofstream File_Data3;
	File_Data3.open("available.txt");
	File_Data3.close();
	for (size_t i = 0; i < books1.size(); i++) {
		books1[i]->print();
	}
	cout << "Удаление из списка заказов завершено успешно!" << endl;
}

//проверка на наличие книг на руках
void Reader::check() {
	ifstream File_Data;
	File_Data.open("reserved.txt");
	SmartPointer<Reserved> book(new Reserved());
	string ISBN, autor, title, genre, edition; int Num_card, yearMake, count1 = 0;
	//считываем данные из файла и считаем количество тех, что соответствуют пользователю
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