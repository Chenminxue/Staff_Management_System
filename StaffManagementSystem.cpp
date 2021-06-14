#include "StaffManagementSystem.h"
#include "Staff.h"

int main() {

	StaffManagementSystem sms;

	int choice = 0;

	while (true) {
		sms.ShowMenu();

		cout << "Please enter your choice.\n";
		
		cin >> choice;

		switch (choice) {

		case 0: // Exit
			sms.ExitSystem();
			break;
		case 1: // Add Staff info
			sms.AddStaff();
			break;
		case 2: // Show Staff info
			sms.ShowStaff();
			break;
		case 3: // Delete Staff info
			sms.DeleteStaff();
			break;
		case 4: // Modify Staff info
			sms.ModifyStaffInfo();
			break;
		case 5: // Search Staff info
			sms.SearchStaff();
			break;
		case 6: // Sort by ID
			break;
		case 7: // Clear the System
			break;
		default:
			cout << "Error, please enter again!\n";
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");

	return 0;
}

StaffManagementSystem::StaffManagementSystem() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	// File doesn't exist
	if (!ifs.is_open()) {
		cout << "File doesn't exist!" << endl;

		this->m_StaffNum = 0;
		
		this->m_StaffArr = NULL;

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	// File is empty
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "File is empty!" << endl;
		this->m_StaffNum = 0;

		this->m_StaffArr = NULL;

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	this->m_StaffNum = 0;
	this->m_StaffArr = NULL;

	// File is not empty
	int num = this->GetStaffNum();
	cout << "The number of Staff is " << num << endl;
	this->m_StaffNum = num;

	this->m_StaffArr = new Staff * [this->m_StaffNum];
	this->InitialStaff();

	// // test code
	//for (int i = 0; i < m_StaffNum; i++) {
	//	cout << " StaffID: " << this->m_StaffArr[i]->m_ID
	//		<< " StaffName: " << this->m_StaffArr[i]->m_name
	//		<< " DepartmentID: " << this->m_StaffArr[i]->m_DepartmentID << endl;
	//}
}

StaffManagementSystem::~StaffManagementSystem() {

}

void StaffManagementSystem::ShowMenu() {
	cout << "********************************************" << endl;
	cout << "********** Welcome to the System! **********" << endl;
	cout << "********************************************" << endl;
	cout << "*********   0. Exit               **********" << endl;
	cout << "*********   1. Add Staff info     **********" << endl;
	cout << "*********   2. Show Staff info    **********" << endl;
	cout << "*********   3. Delete Staff info  **********" << endl;
	cout << "*********   4. Modify Staff info  **********" << endl;
	cout << "*********   5. Search Staff info  **********" << endl;
	cout << "*********   6. Sort by ID         **********" << endl;
	cout << "*********   7. Clear the System   **********" << endl;
	cout << "********************************************" << endl;
}

void StaffManagementSystem::ExitSystem() {
	cout << "Goodbye!\n";
	system("pause");
	exit(0);
}

void StaffManagementSystem::AddStaff() {
	cout << "Number of staff you want to add: " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		int newSize = this->m_StaffNum + addNum;
		Staff** newSpace = new Staff* [newSize];

		if (this->m_StaffArr != NULL) {
			for (int i = 0; i < m_StaffNum; i++) {
				newSpace[i] = this->m_StaffArr[i];
			}
		}
		for (int j = 0; j < addNum; j++) {
			int id;
			string name;
			int department;

			cout << "Please enter ID of staff " << j + 1 << endl;
			cin >> id;

			cout << "Please enter name of staff " << j + 1 << endl;
			cin >> name;

			cout << "Please choose department ID " << endl;
			cout << "1. worker" << endl;
			cout << "2. manager" << endl;
			cout << "3. boss" << endl;
			cin >> department;

			Staff* staff = NULL;
			switch (department) {
			case 1:
				staff = new Worker(id, name, 1);
				break;
			case 2:
				staff = new Manager(id, name, 2);
				break;
			case 3:
				staff = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_StaffNum + j] = staff;

		}
		delete[] this->m_StaffArr;

		this->m_StaffArr = newSpace;

		this->m_StaffNum = newSize;

		this->m_FileIsEmpty = false;

		cout << "Successfully added " << addNum << " staff!" << endl;
	
		this->save();
	}
	else {
		cout << "Error, please enter again!" << endl;
	}
	system("pause");
	system("cls");
}

void StaffManagementSystem::ShowStaff() {
	if (this->m_FileIsEmpty) {
		cout << "File doesn't exist or empty!" << endl;
	}
	else {
		for (int i = 0; i < m_StaffNum; i++) {
			this->m_StaffArr[i]->ShowInfo();
		}
	}
	system("pause");
	system("cls");
}

int StaffManagementSystem::IsStaffExist(int id) {
	int index = -1;

	for (int i = 0; i < this->m_StaffNum; i++) {
		if (this->m_StaffArr[i]->m_ID == id) {
			index = i;

			break;
		}
	}
	return index;
}

void StaffManagementSystem::DeleteStaff() {
	if (this->m_FileIsEmpty) {
		cout << "File doesn't exist or empty!" << endl;
	}
	else {
		cout << "Which one(ID) you want to delete: " << endl;
		int id = 0;
		cin >> id;

		int index = this->IsStaffExist(id);

		if (index != -1) {
			for (int i = index; i < this->m_StaffNum - 1; i++) {
				this->m_StaffArr[i] = this->m_StaffArr[i + 1];
			}
			this->m_StaffNum--;

			this->save();

			cout << "Successfully deleted!" << endl;
		}
		else {
			cout << "Error, Staff doesn't exist!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void StaffManagementSystem::ModifyStaffInfo() {
	if (this->m_FileIsEmpty) {
		cout << "File doesn't exist or empty!" << endl;
	}
	else {
		cout << "Which one(ID) you want to modify: " << endl;
		
		int id;
		cin >> id;
		
		int check = this->IsStaffExist(id);
		if (check != -1) {
			delete this->m_StaffArr[check];

			int newID = 0;
			string newName = "";
			int newDepartmentID = 0;

			cout << "Found ID: " << id << endl;
			cout << "Enter new ID: " << endl;
			cin >> newID;

			cout << "Enter new name: " << endl;
			cin >> newName;

			cout << "Enter department ID: " << endl;
			cout << "1. worker" << endl;
			cout << "2. manager" << endl;
			cout << "3. boss" << endl;

			cin >> newDepartmentID;

			Staff* staff = NULL;

			switch (newDepartmentID) {
			case 1:
				staff = new Worker(newID, newName, newDepartmentID);
				break;
			case 2:
				staff = new Manager(newID, newName, newDepartmentID);
				break;
			case 3:
				staff = new Boss(newID, newName, newDepartmentID);
				break;
			default:
				break;
			}

			this->m_StaffArr[check] = staff;

			cout << "Successfully modified!" << endl;

			this->save();
		}
		else {
			cout << "Error, Staff doesn't exist!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void StaffManagementSystem::SearchStaff() {
	if (this->m_FileIsEmpty) {
		cout << "File doesn't exist or empty!" << endl;
	}
	else {
		cout << "1. Search by ID " << endl;
		cout << "2. Search by name " << endl;
	
		int select = 0;
		cin >> select;

		if (select == 1) {
			int id;
			cout << "Please enter the ID number: " << endl;
			cin >> id;

			int check = IsStaffExist(id);
			if (check != -1) {
				cout << "Successfully found!" << endl;
				this->m_StaffArr[check]->ShowInfo();
			}
			else {
				cout << "Didn't find this person." << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "Please enter the name: " << endl;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < m_StaffNum; i++) {
				if (this->m_StaffArr[i]->m_name == name) {
					cout << "Successfully found " << this->m_StaffArr[i]->m_ID << " and Info: " << endl;

					flag = true;

					this->m_StaffArr[i]->ShowInfo();
				}
			}
			if (flag == false) {
				cout << "Didn't find this person." << endl;
			}
		}
		else {
			cout << "Error! Wrong input!" << endl;
		}
	}
	system("pause");
	system("cls");
}

Worker::Worker(int id, string name, int departmentID) {
	this->m_ID = id;
	this->m_name = name;
	this->m_DepartmentID = departmentID;
}

void Worker::ShowInfo() {
	cout << "\tStaff ID " << this->m_ID <<
		"\t\nStaff name " << this->m_name <<
		"\t\nStaff department " << this->GetDepartmentInfo() <<
		"\t\nStaff responsibility : Complete the tasks assigned by the manager." << endl;
}

// return department name
string Worker::GetDepartmentInfo() {
	return "worker";
}

Manager::Manager(int id, string name, int departmentID) {
	this->m_ID = id;
	this->m_name = name;
	this->m_DepartmentID = departmentID;
}

void Manager::ShowInfo() {
	cout << "\tStaff ID " << this->m_ID <<
		"\t\nStaff name " << this->m_name <<
		"\t\nStaff department " << this->GetDepartmentInfo() <<
		"\t\nStaff responsibility : Complete the tasks assigned by the boss." << endl;
}

string Manager::GetDepartmentInfo() {
	return "Manager";
}

Boss::Boss(int id, string name, int departmentID) {
	this->m_ID = id;
	this->m_name = name;
	this->m_DepartmentID = departmentID;
}

void Boss::ShowInfo() {
	cout << "\tStaff ID " << this->m_ID <<
		"\t\nStaff name " << this->m_name <<
		"\t\nStaff department " << this->GetDepartmentInfo() <<
		"\t\nStaff responsibility : Manage all employees." << endl;
}

string Boss::GetDepartmentInfo() {
	return "Boss";
}

void StaffManagementSystem::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < m_StaffNum; i++) {
		ofs << this->m_StaffArr[i]->m_ID << " "
			<< this->m_StaffArr[i]->m_name << " "
			<< this->m_StaffArr[i]->m_DepartmentID << endl;
	}

	ofs.close();
}

int StaffManagementSystem::GetStaffNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int departmentID;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> departmentID) {
		num++;
	}
	return num;
}

void StaffManagementSystem::InitialStaff() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int departmentID;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> departmentID) {
		Staff* staff = NULL;

		if (departmentID == 1) {
			staff = new Worker(id, name, departmentID);
		}
		else if (departmentID == 2) {
			staff = new Manager(id, name, departmentID);
		}
		else {
			staff = new Boss(id, name, departmentID);
		}
		this->m_StaffArr[index] = staff;
		index++;
	}
	ifs.close();
}