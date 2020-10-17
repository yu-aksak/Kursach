#include "Autorisation.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// вход в учетную запись
bool Autorisation::Enter(string login, string password, int level) {
	if (checkPass(login, password, level)) {		// проверка на правильность пароля
		this->login = login;
		this->level = level;
		cout << "Вход выполнен успешно." << endl;
		return true;
	}
	else {
		cout << "Неправильный логин или пароль. Проверьте правильность данных." << endl;
		return false;
	}
}

// регистрация пользователя
bool Autorisation::Registration(string login, string password, int level) {
	if (checkLog(login, level)) {		// проверка на оригинальность логина
		this->login = login;
		this->password = encrypt(password);
		this->level = level;
		print(level);					// запись в файл
		cout << "Регистрация произведена успешно." << endl;
		return true;
	}
	else {
		cout << "Такой логин уже существует. Придумайте другой." << endl;
		return false;
	}
}

// проверка пароля на правильность
bool Autorisation::checkPass(string Login, string Password, int Level) {
	ifstream File_Data;
	string File_Name;
	string EnPass, log, pass;
	if (Level == 1)
		File_Name = "readers.txt";
	else
		File_Name = "employees.txt";
	File_Data.open(File_Name);

	// проверка на существование логина
	while (File_Data >> log >> pass)
	{
		if (Login == log) {
			EnPass = pass;
			login = Login;
			break;
		}
	}
	File_Data.close();
	if (login == "\0")
		return false;

	// расшифровка пароля и проверка на правильность введенного пароля
	pass = decrypt(EnPass);
	if (Password == pass)
	{
		password = Password;
		return true;
	}
	return false;
}

// проверка на существование логина
bool Autorisation::checkLog(string Login, int Level) {
	string log, pass; int lvl = 0; bool temp = true;
	ifstream File_Data;
	string File_Name;
	if (Level == 1)
		File_Name = "readers.txt";
	else
		File_Name = "employees.txt";
	File_Data.open(File_Name, ios::app);
	
	// проверка на совпаление с введенным логином
	while (File_Data >> log >> pass)
	{
		if (Login == log) {
			temp = false;
			break;
		}
	}
	File_Data.close();
	return temp;
}

// шифрование пароля
string Autorisation::encrypt(const string password) {
	string EnPassword = "";
	char pass;
	// высчитываем ключ для шифрования
	int key = password.length();
	if (key <= 12)
		key *= 2;
	else 
		key /= 2;

	// шифрование
	for (size_t i = 0; i < password.length(); i++)
	{
		pass = password[i] + key;
		EnPassword.push_back(pass);
	}
	return EnPassword;
}

// расшифровка пароля
string Autorisation::decrypt(const string& EnPassword) {
	string Password;
	char pass;
	// высчитываем ключ для расшифровки
	int key = EnPassword.length();
	if (key <= 12)
		key *= 2;
	else
		key /= 2;

	// расшифровка пароля
	for (size_t i = 0; i < EnPassword.length(); i++) {
		pass = EnPassword[i] - key;
		Password.push_back(pass);
	}
	return Password;
}

// запись логина и зашифрованного пароля в файл
void Autorisation::print(int Level) const
{
	ofstream File_Data;
	string File_Name;
	if (Level == 1)
		File_Name = "readers.txt";
	else
		File_Name = "employees.txt";
	File_Data.open(File_Name, ios::app);
	
	File_Data << endl;
	File_Data << login << "\t" << password;
	File_Data.close();
}