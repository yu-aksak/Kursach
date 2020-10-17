#include "Autorisation.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// ���� � ������� ������
bool Autorisation::Enter(string login, string password, int level) {
	if (checkPass(login, password, level)) {		// �������� �� ������������ ������
		this->login = login;
		this->level = level;
		cout << "���� �������� �������." << endl;
		return true;
	}
	else {
		cout << "������������ ����� ��� ������. ��������� ������������ ������." << endl;
		return false;
	}
}

// ����������� ������������
bool Autorisation::Registration(string login, string password, int level) {
	if (checkLog(login, level)) {		// �������� �� �������������� ������
		this->login = login;
		this->password = encrypt(password);
		this->level = level;
		print(level);					// ������ � ����
		cout << "����������� ����������� �������." << endl;
		return true;
	}
	else {
		cout << "����� ����� ��� ����������. ���������� ������." << endl;
		return false;
	}
}

// �������� ������ �� ������������
bool Autorisation::checkPass(string Login, string Password, int Level) {
	ifstream File_Data;
	string File_Name;
	string EnPass, log, pass;
	if (Level == 1)
		File_Name = "readers.txt";
	else
		File_Name = "employees.txt";
	File_Data.open(File_Name);

	// �������� �� ������������� ������
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

	// ����������� ������ � �������� �� ������������ ���������� ������
	pass = decrypt(EnPass);
	if (Password == pass)
	{
		password = Password;
		return true;
	}
	return false;
}

// �������� �� ������������� ������
bool Autorisation::checkLog(string Login, int Level) {
	string log, pass; int lvl = 0; bool temp = true;
	ifstream File_Data;
	string File_Name;
	if (Level == 1)
		File_Name = "readers.txt";
	else
		File_Name = "employees.txt";
	File_Data.open(File_Name, ios::app);
	
	// �������� �� ���������� � ��������� �������
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

// ���������� ������
string Autorisation::encrypt(const string password) {
	string EnPassword = "";
	char pass;
	// ����������� ���� ��� ����������
	int key = password.length();
	if (key <= 12)
		key *= 2;
	else 
		key /= 2;

	// ����������
	for (size_t i = 0; i < password.length(); i++)
	{
		pass = password[i] + key;
		EnPassword.push_back(pass);
	}
	return EnPassword;
}

// ����������� ������
string Autorisation::decrypt(const string& EnPassword) {
	string Password;
	char pass;
	// ����������� ���� ��� �����������
	int key = EnPassword.length();
	if (key <= 12)
		key *= 2;
	else
		key /= 2;

	// ����������� ������
	for (size_t i = 0; i < EnPassword.length(); i++) {
		pass = EnPassword[i] - key;
		Password.push_back(pass);
	}
	return Password;
}

// ������ ������ � �������������� ������ � ����
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