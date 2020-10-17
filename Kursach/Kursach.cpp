#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <ctime>
#include "Autorisation.hpp"
#include "Book.hpp"
#include "Employee.hpp"
#include "Reader.hpp"
#include "SmartPointer.hpp"
#include "menu.hpp"
using namespace std;
using namespace menu;

// функция получения текущей даты
string gettime(void) {
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	const char* format = "%d/%m/%Y";
	char buffer[80];
	strftime(buffer, 80, format, &timeinfo);
	string str_buffer(buffer);
	return str_buffer;
}

// функция ввода пароля и отображение на экране звездочками
string EnterPassword() {
	string pass;
	int i = 0;
	char a;
	while (true)
	{
		a = _getch();
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
		{
			pass.push_back(a);
			++i;
			cout << "*";
		}
		if (a == '\b' && i >= 1)
		{
			cout << "\b \b";
			pass.pop_back();
			--i;
		}
		if (a == '\r')
		{
			cout << endl;
			if (pass.length() <= 8) {
				cout << "Пароль слишком короткий! Попробуйте снова!" << endl;
				pass = "";
			}
			else
				break;
		}
	}
	return pass;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color E0");

	Reader reader;
	Employee employee;
	Autorisation person;
	int login = 0, s = 0, count = 0, yearMade = 0;
	string password, password1, firstName, Name, ISBN, autor, title, secondName, adress, phone, position, genre, date, edition;
	bool enter = false, registration = false;

	while (enter == false) {
		switch (menuAutorisation())
		{
		case 1:
			switch (menuUser())
			{
			case 1:
				cout << "Введите номер читательского билета: "; Check(&login);
				cout << "Введите пароль: ";
				password = EnterPassword();
				enter = person.Enter(to_string(login), password, 1);
				if (enter == false)
					break;
				reader.set(login);
				s = 1;
				password = "";
				break;
			case 2:
				cout << "Введите номер табеля: "; Check(&login);
				cout << "Введите пароль: ";
				password = EnterPassword();
				enter = person.Enter(to_string(login), password, 2);
				if (enter == false)
					break;
				employee.set(login);
				s = 2;
				password = "";
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (menuUser())
			{
			case 1:
				cout << "Введите номер читательского билета: "; Check(&login);
				cout << "Введите пароль: ";
				password = EnterPassword();
				cout << "Повторите пароль: ";
				password1 = EnterPassword();
				if (password1 == password);
				else {
					cout << "Вы неправильно повторили ввод пароля" << endl;
					break;
				}
				registration = person.Registration(to_string(login), password, 1);
				if (registration == false)
					break;
				cout << "Введите Фамилию: " << endl;
				cin >> firstName;
				cout << "Введите Имя: " << endl;
				cin >> Name;
				cout << "Введите Отчество: " << endl;
				cin >> secondName;
				cout << "Введите Адрес: " << endl;
				cin >> adress;
				cout << "Введите Телефон: " << endl;
				cin >> phone;
				reader.setter(login, firstName, Name, secondName, adress, phone);
				reader.print();
				password = "";
				break;
			case 2:
				cout << "Введите номер табеля: "; Check(&login);
				cout << "Введите пароль: ";
				password = EnterPassword();
				cout << "Повторите пароль: ";
				password1 = EnterPassword();
				if (password1 == password);
				else {
					cout << "Вы неправильно повторили ввод пароля" << endl;
					break;
				}
				cout << endl;
				registration = person.Registration(to_string(login), password, 2);
				if (registration == false)
					break;
				cout << "Введите Фамилию: " << endl;
				cin >> firstName;
				cout << "Введите Имя: " << endl;
				cin >> Name;
				cout << "Введите Отчество: " << endl;
				cin >> secondName;
				cout << "Введите должность: " << endl;
				cin >> position;
				employee.setter(login, firstName, Name, secondName, position);
				employee.print();
				password = "";
				break;
			default:
				break;
			}
			break;
		case 0:
			system("pause");
			return 0;
		default:
			break;
		}
	}

	while (true) {
		switch (s)
		{
		case 1:
			switch (mainMenuReader())
			{
			case 1:
				cout << reader;
				break;
			case 2:
				switch (menuEditReader())
				{
				case 1:
					cout << "Введите новую фамилию" << endl;
					cin >> firstName;
					reader.editInfo(1, firstName);
					break;
				case 2:
					cout << "Введите новое имя" << endl;
					cin >> Name;
					reader.editInfo(2, Name);
					break;
				case 3:
					cout << "Введите новое отчество" << endl;
					cin >> secondName;
					reader.editInfo(3, secondName);
					break;
				case 4:
					cout << "Введите новый адрес" << endl;
					cin >> adress;
					reader.editInfo(4, adress);
					break;
				case 5:
					cout << "Введите новый телефон" << endl;
					cin >> phone;
					reader.editInfo(5, phone);
					break;
				default:
					break;
				}
				break;
			case 3:
				switch (menuBookReader())
				{
				case 1:
					reader.viewBooks();
					break;
				case 2:
					reader.viewBooksR<Issued>();
					break;
				case 3:
					reader.viewBooksR<Reserved>();
					break;
				default:
					break;
				}
				break;
			case 4:
				switch (menuSearch())
				{
				case 1:
					cout << "Введите название книги" << endl;
					cin >> title;
					reader.search(1, title);
					break;
				case 2:
					cout << "Введите автора книги" << endl;
					cin >> autor;
					reader.search(2, autor);
					break;
				case 3:
					cout << "Введите ISBN книги" << endl;
					cin >> ISBN;
					reader.search(3, ISBN);
					break;
				default:
					break;
				}
				break;
			case 5:
				switch (menuFiltration())
				{
				case 1:
					cout << "Введите автора" << endl;
					cin >> autor;
					reader.filtration(1, autor);
					break;
				case 2:
					cout << "Введите жанр" << endl;
					cin >> genre;
					reader.filtration(2, genre);
					break;
				default:
					break;
				}
				break;

			case 6:
				reader.viewBooks();
				cout << endl;
				cout << "Введите автора книги, которую хотите забронировать" << endl;
				cin >> autor;
				cout << "Введите название книги, которую хотите забронировать" << endl;
				cin >> title;
				reader.reserve(title, autor);
				break;
			case 7:
				try {
					reader.check();
				}
				catch (bool b) {
					cout << "У вас нет книг в списке заказов." << endl;
					break;
				}
				reader.viewBooksR<Reserved>();
				cout << endl;
				cout << "Введите автора книги, которую хотите удалить из списка заказов: " << endl; cin >> autor;
				cout << "Введите название книги, которую хотите удалить из списка заказов: " << endl; cin >> title;
				reader.remove(autor, title);
				break;
			case 0:
				system("pause");
				return 0;
			default:
				break;
			}
			break;
		case 2:
			switch (mainMenuEmployee())
			{
			case 1:
				cout << employee;
				break;
			case 2:
				switch (menuEditEmployee()) {
				case 1:
					cout << "Введите новую фамилию" << endl;
					cin >> firstName;
					employee.editInfo(1, firstName);
					break;
				case 2:
					cout << "Введите новое имя" << endl;
					cin >> Name;
					employee.editInfo(1, Name);
					break;
				case 3:
					cin >> secondName;
					employee.editInfo(1, secondName);
					cout << "Введите новое отчество" << endl;
					break;
				case 4:
					cin >> position;
					employee.editInfo(1, position);
					cout << "Введите новую должность" << endl;
					break;
				default:
					break;
				}
				break;
			case 3:
				switch (menuBookEmployee())
				{
				case 1:
					employee.viewBooks<Available>();
					break;
				case 2:
					employee.viewBooks<Written_off>();
					break;
				case 3:
					employee.viewBooks<Issued>();
					break;
				case 4:
					employee.viewBooks<Recieved>();
					break;
				case 5:
					employee.viewBooks<Reserved>();
					break;
				case 6:
					cout << "Введите номер читательского билета" << endl;
					Check(&login);
					employee.viewBooks(login);
					break;
				default:
					break;
				}
				break;
			case 4:
				cout << endl;
				cout << "Введите автора книги" << endl;
				cin >> autor;
				cout << "Введите название книги" << endl;
				cin >> title;
				employee.viewBookReaders(autor, title);
				break;
			case 5:
				employee.viewReaders();
				break;
			case 6:
				cout << "Введите номер читательского билета" << endl;
				cin >> login;
				date = gettime();
				employee.giveBook(login, date);
				break;
			case 7:
				cout << "Введите номер читательского билета" << endl;
				cin >> login;
				date = gettime();
				cout << "Введите автора книги" << endl;
				cin >> autor;
				cout << "Введите название книги" << endl;
				cin >> title;
				employee.giveBook(login, date, autor, title);
				break;
			case 8:
				cout << "Введите номер читательского билета" << endl;
				cin >> login;
				cout << "Введите автора книги" << endl;
				cin >> autor;
				cout << "Введите название книги" << endl;
				cin >> title;
				employee.acceptBook(login, autor, title);
				break;
			case 9:
				switch (menuBookEmployeeS())
				{
				case 1:
					employee.search<Available>(menuSearch());
					break;
				case 2:
					employee.search<Written_off>(menuSearch());
					break;
				case 3:
					employee.search<Issued>(menuSearch());
					break;
				case 4:
					employee.search<Recieved>(menuSearch());
					break;
				case 5:
					employee.search<Reserved>(menuSearch());
					break;
				default:
					break;
				}
				break;
			case 10:
				switch (menuBookEmployeeS())
				{
				case 1:
					employee.sortBook<Available>(menuSort());
					break;
				case 2:
					employee.sortBook<Written_off>(menuSort());
					break;
				case 3:
					employee.sortBook<Issued>(menuSort());
					break;
				case 4:
					employee.sortBook<Recieved>(menuSort());
					break;
				case 5:
					employee.sortBook<Reserved>(menuSort());
					break;
				default:
					break;
				}
				break;
			case 11:
				switch (menuBookEmployeeS())
				{
				case 1:
					employee.filtration<Available>(menuFiltration());
					break;
				case 2:
					employee.filtration<Written_off>(menuFiltration());
					break;
				case 3:
					employee.filtration<Issued>(menuFiltration());
					break;
				case 4:
					employee.filtration<Recieved>(menuFiltration());
					break;
				case 5:
					employee.filtration<Reserved>(menuFiltration());
					break;
				default:
					break;
				}
				break;
			case 12:
				cout << "Введите ISBN книги: ";
				cin >> ISBN;
				cout << "Введите автора книги: ";
				cin >> autor;
				cout << "Введите название книги: ";
				cin >> title;
				cout << "Введите жанр книги: ";
				cin >> genre;
				cout << "Введите год написания книги: ";
				Check(&yearMade);
				cout << "Ввелите издательство: ";
				cin >> edition;
				cout << "Введите количество поступивших книг: ";
				Check(&count);
				date = gettime();
				employee.addBook(ISBN, autor, title, genre, yearMade, edition, count, date);
				break;
			case 13:
				cout << "Введите ISBN книги: ";
				cin >> ISBN;
				cout << "Введите количество книг, которые нужно списать: ";
				try {
					Check(&count);
					if (count == 0)
						throw "Количество равно 0";
				}
				catch (const char* c) {
					cout << "Количество книг для списания равно 0." << endl;
					break;
				}
				date = gettime();
				employee.deleteBook(ISBN, count, date);
				break;

			case 0:
				system("pause");
				return 0;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}