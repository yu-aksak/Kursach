#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
using namespace std;

namespace menu {

	template<typename T>
	void Check(T* inf)
	{
		while (!(cin >> *inf) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "������! ���������� �����!";
		}
	}

	int menuAutorisation() {
		int i;
		cout << "��������:" << endl;
		cout << "1. �����" << endl;
		cout << "2. ������������������" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuUser() {
		int i;
		cout << "��������:" << endl;
		cout << "1. ��� ��������" << endl;
		cout << "2. ��� ���������" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuBookEmployee() {
		int i;
		cout << "��������:" << endl;
		cout << "1. ���� � �������" << endl;
		cout << "2. ��������� ����" << endl;
		cout << "3. �������� ����" << endl;
		cout << "4. �������� ����" << endl;
		cout << "5. ��������������� ����" << endl;
		cout << "6. �������� ���� ������������� ��������" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuBookEmployeeS() {
		int i;
		cout << "��������:" << endl;
		cout << "1. ���� � �������" << endl;
		cout << "2. ��������� ����" << endl;
		cout << "3. �������� ����" << endl;
		cout << "4. �������� ����" << endl;
		cout << "5. ��������������� ����" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuBookReader() {
		int i;
		cout << "��������:" << endl;
		cout << "1. ���� � �������" << endl;
		cout << "2. �������� ����" << endl;
		cout << "3. ��������������� ����" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuFiltration() {
		int i;
		cout << "��������:" << endl;
		cout << "1. �� ������" << endl;
		cout << "2. �� �����" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuSearch() {
		int i;
		cout << "��������: " << endl;
		cout << "1. �� ��������" << endl;
		cout << "2. �� ������" << endl;
		cout << "3. �� ISBN �����" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuSort() {
		int i;
		cout << "��������: " << endl;
		cout << "1. �� ���������" << endl;
		cout << "2. �� �������" << endl;
		cout << "3. �� ������" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int mainMenuReader() {
		system("pause");
		system("cls");
		int i;
		cout << "��������" << endl;
		cout << "1. �������� ������ ������" << endl;
		cout << "2. ��������� ������ ������" << endl;
		cout << "3. �������� ����" << endl;
		cout << "4. ����� ����� ������ ����" << endl;
		cout << "5. ���������� ���� (�� ����� � ��.)" << endl;
		cout << "6. ������������� �����" << endl;
		cout << "7. ������ ����� �� ������ �������" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuEditReader() {
		int i;
		cout << "�������� ������, ������� ������ �������������:" << endl;
		cout << "1. �������" << endl;
		cout << "2. ���" << endl;
		cout << "3. ��������" << endl;
		cout << "4. �����" << endl;
		cout << "5. �������" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int mainMenuEmployee() {
		system("pause");
		system("cls");
		int i;
		cout << "��������:" << endl;
		cout << "1. �������� ������ ������" << endl;
		cout << "2. ��������� ������ ������" << endl;
		cout << "3. �������� ����" << endl;
		cout << "4. ����� ������ � ���������, ������� ������������ �����" << endl;
		cout << "5. ����� ������ � ���� ���������" << endl;
		cout << "6. ������ �������� ����� �� ������ ���������������" << endl;
		cout << "7. ������ ����� �� ���� � �������" << endl;
		cout << "8. ������� ����� �� �������� (�� �����)" << endl;
		cout << "9. ����� �����" << endl;
		cout << "10. ���������� � ������� �����������" << endl;
		cout << "11. ����������" << endl;
		cout << "12. ���������� �����" << endl;
		cout << "13. �������� �����" << endl;
		cout << "0. �����" << endl;
		Check(&i);
		return i;
	}

	int menuEditEmployee() {
		int i;
		cout << "�������� ������, ������� ������ �������������:" << endl;
		cout << "1. �������" << endl;
		cout << "2. ���" << endl;
		cout << "3. ��������" << endl;
		cout << "4. ���������" << endl;
		Check(&i);
		return i;
	}
}
#endif // !MENU_HPP