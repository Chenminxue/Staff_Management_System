#pragma once
#include <iostream>
#include <string>
using namespace std;

class Staff {
public:
	string m_name;

	int m_ID;

	int m_DepartmentID;

	virtual void ShowInfo() = 0;

	virtual string GetDepartmentInfo() = 0;
};

class Worker : public Staff {
public:

	Worker(int id, string name, int departmentID);

	virtual void ShowInfo();

	virtual string GetDepartmentInfo();

};

class Manager : public Staff {
public:

	Manager(int id, string name, int departmentID);

	virtual void ShowInfo();

	virtual string GetDepartmentInfo();

};

class Boss : public Staff {
public:

	Boss(int id, string name, int departmentID);

	virtual void ShowInfo();

	virtual string GetDepartmentInfo();

};

