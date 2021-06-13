#include "StaffManagementSystem.h"


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
			break;
		case 2: // Show Staff info
			break;
		case 3: // Delete Staff info
			break;
		case 4: // Modify Staff info
			break;
		case 5: // Search Staff info
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