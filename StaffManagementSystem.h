#pragma once
#include <iostream>
#include "Staff.h"
#include <fstream>
#define FILENAME "StaffFile.txt"
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

	// Save info 
	void save();

	// Is file empty?
	bool m_FileIsEmpty;

	// Get Staff in file
	int GetStaffNum();

	// Initial Staff
	void InitialStaff();

	~StaffManagementSystem();
};


