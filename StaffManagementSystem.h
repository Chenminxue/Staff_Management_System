#pragma once
#include <iostream>
#include "Staff.h"
using namespace std;


class StaffManagementSystem {
public:
	StaffManagementSystem();

	// Menu of the system
	void ShowMenu();
	
	// Exit the system
	void ExitSystem();

	// Total number of staffs
	int m_StaffNum;

	// Staff point array
	Staff** m_StaffArr;

	// Add Staff
	void AddStaff();

	~StaffManagementSystem();
};


