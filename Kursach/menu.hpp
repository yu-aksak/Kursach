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
			cout << "Ошибка! Попробуйте снова!";
		}
	}

	int menuAutorisation() {
		int i;
		cout << "Выберите:" << endl;
		cout << "1. Войти" << endl;
		cout << "2. Зарегистрироваться" << endl;
		cout << "0. Выход" << endl;
		Check(&i);
		return i;
	}

	int menuUser() {
		int i;
		cout << "Выберите:" << endl;
		cout << "1. Как читатель" << endl;
		cout << "2. Как сотрудник" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int menuBookEmployee() {
		int i;
		cout << "Выберите:" << endl;
		cout << "1. Книг в наличии" << endl;
		cout << "2. Списанных книг" << endl;
		cout << "3. Выданных книг" << endl;
		cout << "4. Принятых книг" << endl;
		cout << "5. Забронированных книг" << endl;
		cout << "6. Выданных книг определенному читателю" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int menuBookEmployeeS() {
		int i;
		cout << "Выберите:" << endl;
		cout << "1. Книг в наличии" << endl;
		cout << "2. Списанных книг" << endl;
		cout << "3. Выданных книг" << endl;
		cout << "4. Принятых книг" << endl;
		cout << "5. Забронированных книг" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int menuBookReader() {
		int i;
		cout << "Выберите:" << endl;
		cout << "1. Книг в наличии" << endl;
		cout << "2. Выданных книг" << endl;
		cout << "3. Забронированных книг" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int menuFiltration() {
		int i;
		cout << "Выберите:" << endl;
		cout << "1. По автору" << endl;
		cout << "2. По жанру" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int menuSearch() {
		int i;
		cout << "Выберите: " << endl;
		cout << "1. По названию" << endl;
		cout << "2. По автору" << endl;
		cout << "3. По ISBN книги" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int menuSort() {
		int i;
		cout << "Выберите: " << endl;
		cout << "1. По названиям" << endl;
		cout << "2. По авторам" << endl;
		cout << "3. По жанрам" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int mainMenuReader() {
		system("pause");
		system("cls");
		int i;
		cout << "Выберите" << endl;
		cout << "1. Просмотр личных данных" << endl;
		cout << "2. Изменение личных данных" << endl;
		cout << "3. Просмотр книг" << endl;
		cout << "4. Поиск среди списка книг" << endl;
		cout << "5. Фильтрация книг (по жанру и др.)" << endl;
		cout << "6. Забронировать книгу" << endl;
		cout << "7. Убрать книгу из списка заказов" << endl;
		cout << "0. Выход" << endl;
		Check(&i);
		return i;
	}

	int menuEditReader() {
		int i;
		cout << "Выберите данные, которые хотите редактировать:" << endl;
		cout << "1. Фамилия" << endl;
		cout << "2. Имя" << endl;
		cout << "3. Отчество" << endl;
		cout << "4. Адрес" << endl;
		cout << "5. Телефон" << endl;
		cout << "0. Назад" << endl;
		Check(&i);
		return i;
	}

	int mainMenuEmployee() {
		system("pause");
		system("cls");
		int i;
		cout << "Выберите:" << endl;
		cout << "1. Просмотр личных данных" << endl;
		cout << "2. Изменение личных данных" << endl;
		cout << "3. Просмотр книг" << endl;
		cout << "4. Вывод данных о читателях, имеющих определенную книгу" << endl;
		cout << "5. Вывод данных о всех читателях" << endl;
		cout << "6. Выдать читателю книгу из списка забронированных" << endl;
		cout << "7. Выдать книгу из книг в наличии" << endl;
		cout << "8. Принять книгу от читателя (он сдает)" << endl;
		cout << "9. Поиск книги" << endl;
		cout << "10. Сортировка в порядке возрастания" << endl;
		cout << "11. Фильтрация" << endl;
		cout << "12. Добавление книги" << endl;
		cout << "13. Списание книги" << endl;
		cout << "0. Выход" << endl;
		Check(&i);
		return i;
	}

	int menuEditEmployee() {
		int i;
		cout << "Выберите данные, которые хотите редактировать:" << endl;
		cout << "1. Фамилия" << endl;
		cout << "2. Имя" << endl;
		cout << "3. Отчество" << endl;
		cout << "4. Должность" << endl;
		Check(&i);
		return i;
	}
}
#endif // !MENU_HPP