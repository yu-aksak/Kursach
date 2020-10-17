#pragma once
#ifndef AUTORISATION_HPP
#define AUTORISATION_HPP

#include<iostream>
#include<string>
using namespace std;

class Autorisation {
	string login, password;		//level - уровень доступа (читатель(2), работник(1) и др.)
	int level = 0;
	bool checkPass(string, string, int);
	string encrypt(string);
	string decrypt(const string&);
	void print(int)const;
	bool checkLog(string, int);
public:
	Autorisation() { }
	bool Enter(string, string, int);
	bool Registration(string, string, int);
	~Autorisation() { }
};

#endif // !AUTORISATION_HPP