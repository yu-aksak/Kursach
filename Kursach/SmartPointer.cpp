#include "SmartPointer.hpp"
#include <iostream>
#include <string>
#include "Book.hpp"
#include "Reader.hpp"
#include "Employee.hpp"
using namespace std;

template SmartPointer<Available>;
template SmartPointer<Issued>;
template SmartPointer<Recieved>;
template SmartPointer<Reserved>;
template SmartPointer<Written_off>;
template SmartPointer<Reader>;
template SmartPointer<Employee>;

// �����������
template<class T>
SmartPointer<T>::SmartPointer(T* ptr) {
	if (!ptr) smartPtr = NULL;
	else {
		smartPtr = new Status<T>;
		smartPtr->ptr = ptr;
		smartPtr->counter = 1;
	}
}

// ����������� �����������
template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj) {
	smartPtr = obj.smartPtr;
	if (smartPtr)
		smartPtr->counter++;
}

// ����������
template<class T>
SmartPointer<T>::~SmartPointer() {
	if (smartPtr) {
		smartPtr->counter--;
		if (smartPtr->counter <= 0) {
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
}

// ���������� ��������� ->
template <class T>
T* SmartPointer<T>::operator->() const {
	if (smartPtr) return smartPtr->ptr;
	else return NULL;
}

// ���������� ��������� =
template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& obj) {
	if (smartPtr) {
		smartPtr->counter--;
		if (smartPtr->counter <= 0) {
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
	smartPtr = obj.smartPtr;
	if (smartPtr) smartPtr->counter++;
	return *this;
}