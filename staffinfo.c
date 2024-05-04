#include<stdlib.h>
#include<stdio.h>
#pragma warning(disable:4996)
#include<string.h>
#include<ctype.h>
#include<time.h>
#define MAXSTAFF 100
#define MAXITEM 1000
#define MAXFOUND 1000

typedef struct {
	int day, month, year;
}Date;

typedef struct {
	int hours, minutes;
}Time;

typedef struct {

	char memberID[7];
	char itemID[7];
	Date lostDate;
	Time lostTime;
	char lostPlace[20];
	char description[30];

}Lost;

typedef struct {

	char memberID[7];
	char itemID[7];
	Date foundDate;
	Time foundTime;
	char foundPlace[20];

}Found;

struct validation {

	char passwordvalid[20];
	char passphrase[15];

};

typedef struct {

	char ID[7];
	char name[50];
	char gender;
	char phoneno[12];
	char position[30];
	Date date[11];
	int salary;
	char password[20];
	struct validation valid;
	char IC[13];
}Staff;

addStaff();
displayStaffList();
forgatPassword();
foundItem();
genegrateReport();
loginManager();
loginStaff();
lostAndFoundList();
managerFirstMenu();
managerSecondMenu();
staffFirstMenu();
staffSecondMenu();
removeItem();
removeStaff();
searchStaff(Staff sta[], int i);
updateContact();
updatePassword();
updatePosition();
updateSalary();
updateSatffInfo();
updateStaInfo();

void main() {

	int select;

	do {
		printf("WELCOME BACK ~\n");
		printf("==============\n");
		printf("1.Manager\n");
		printf("2.Staff\n");
		printf("3.Exit\n");
		printf("Enter a number: ");
		scanf("%d", &select);

		switch (select) {

		case 1:
			managerSecondMenu();
			break;

		case 2:
			staffSecondMenu();
			break;

		case 3:
			printf("Exit now.........\n");
			printf("\n\n");
			break;

		default:
			printf("Invalid Number!!!\n");
			printf("Please enter again.\n");
			printf("\n\n");
			break;
		}
	} while (select != 3);

	system("pause");
}

addstaff() {

	FILE* staff;
	Staff sta[MAXSTAFF];
	Staff temp;
	time_t current_time = time(NULL);
	char answer;
	int i = 0;
	char lastStaffID[7];
	int newLastStaffID = 1;
	staff = fopen("staff.bin", "ab+");

	system("cls");
	if (staff == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}
	else {
		while (fread(&sta[i], sizeof(Staff), 1, staff)) {
			i++;
		}

		if (i > 0) {
			strcpy(lastStaffID, sta[i - 1].ID);
			newLastStaffID = atoi(lastStaffID + 1) + 1;
		}

		do {

			printf("ADD STAFF PAGE\n");
			printf("==============\n\n");

			sprintf(temp.ID, "T%05d", newLastStaffID);

			strcpy(sta[i].ID, temp.ID);
			printf("The staff ID is %s.\n", sta[i].ID);

			printf("Name: ");
			rewind(stdin);
			scanf("%[^\n]", sta[i].name);

			printf("Gender: ");
			rewind(stdin);
			scanf(" %c", &sta[i].gender);

			do {
				printf("Contact No: ");
				rewind(stdin);
				scanf("%s", sta[i].phoneno);
				if (strlen(sta[i].phoneno) != 11 && strlen(sta[i].phoneno) != 12) {
					printf("Invalid Phone Number!\n");
				}
				else {
					break;
				}
			} while (1);

			printf("Position: ");
			rewind(stdin);
			scanf("%[^\n]", sta[i].position);

			strftime(sta[i].date, 11, "%Y-%m-%d", localtime(&current_time)); // Corrected date format
			printf("Date Joined: %s\n", sta[i].date);

			printf("Salary: ");
			rewind(stdin);
			scanf("%d", &sta[i].salary);

			do {
				printf("Password: ");
				rewind(stdin);
				scanf("%s", sta[i].password);
				if (strlen(sta[i].password) < 8) {
					printf("Invalid Password!\n");
				}
				else {
					break;
				}
			} while (1);

			do {
				printf("Enter the password again: ");
				rewind(stdin);
				scanf("%s", sta[i].valid.passwordvalid);
				if (strcmp(sta[i].password, sta[i].valid.passwordvalid) != 0) {
					printf("Password doesn't match!\n");
				}
				else {
					break;
				}
			} while (1);

			printf("Please create a sentence and it will be your passphrase\n");
			printf("Your sentence: ");
			scanf("%s", sta[i].valid.passphrase);

			do {
				printf("NRIC No: ");
				rewind(stdin);
				scanf("%s", sta[i].IC);
				if (strlen(sta[i].IC) != 12) {
					printf("Invalid IC number!\n");
				}
				else {
					break;
				}
			} while (1);

			fwrite(&sta[i], sizeof(Staff), 1, staff);

			i++;


			printf("Any more records? (Y/y for Yes) > ");
			rewind(stdin);
			scanf(" %c", &answer);

			printf("\n\n");

			newLastStaffID++;
		} while (toupper(answer) != 'N');
	}

	fclose(staff);
}

foundItem() {

	FILE* foundPtr;
	FILE* lostPtr;
	Lost lost;
	Found found[MAXFOUND];
	Found temp;
	int i = 0;
	char choice;

	foundPtr = fopen("found.bin", "ab+");
	lostPtr = fopen("lost.bin", "rb");

	system("cls");
	if (foundPtr == NULL || lostPtr == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}

	do {
		printf("ITEM FOUND\n");
		printf("==========\n\n");

		printf("Enter the lost item ID: ");
		rewind(stdin);
		scanf("%s", &temp.itemID);

		while (fread(&lost, sizeof(Lost), 1, lostPtr)) {
			if (strcmp(lost.itemID, temp.itemID) == 0) {
				printf("Enter your item found date (dd/mm/yyyy): ");
				rewind(stdin);
				scanf("%d/%d/%d", &temp.foundDate.day, &temp.foundDate.month, &temp.foundDate.year);
				printf("Enter your item found time (hh:mm): ");
				rewind(stdin);
				scanf("%d:%d", &temp.foundTime.hours, &temp.foundTime.minutes);
				printf("Enter your item  place: ");
				rewind(stdin);
				scanf("%[^\n]", &temp.foundPlace);

				found[i] = temp;

				fwrite(&found[i], sizeof(Found), 1, foundPtr);

				i++;

				break;
			}
			else {
				printf("Invalid ID. Please enter again.\n");
			}

			fclose(foundPtr);
			fclose(lostPtr);
		}
		printf("Found more lost item? (Y=Yes/N=No): ");
		scanf(" %c", &choice);

		while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
			printf("Invalid choice. Please enter a valid choice (Y=Yes/N=No): ");
			scanf(" %c", &choice);
		}
	} while (toupper(choice) == 'Y');
}

lostAndFoundList() {

	FILE* lostPtr;
	Lost lost[MAXITEM];
	int i = 0;
	lostPtr = fopen("lost.bin", "ab+");

	system("cls");
	if (lostPtr == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}
	printf("LOST ITEM LIST\n");
	printf("==============\n\n");
	printf("%-14s%-30s  %-15s %-15s %-20s  %-12s\n", "LOST ITEM ID", "LOST ITEM", "LOST ITEM DATE", "LOST ITEM TIME", "LOST ITEM PLACE", "LOST STATUS");
	printf("============  ==============================  ==============  ==============  ====================  ============\n");
	while (fread(&lost[i], sizeof(Lost), 1, lostPtr) != 0) {
		printf("%-14d%-30s  %02d/%02d/%-4d      %02d:%02d           %-20s  %-10s\n\n", lost[i].itemID, lost[i].description, lost[i].lostDate.day,
			lost[i].lostDate.month, lost[i].lostDate.year, lost[i].lostTime.hours, lost[i].lostTime.minutes,
			lost[i].lostPlace, "NOT FOUND");
		i++;
	}
}

removeItem() {

	FILE* lostRemovePtr;
	FILE* tempFile;
	Lost lost;
	int found = 0;
	char itemToRemove[7];

	lostRemovePtr = fopen("lost.bin", "rb");
	tempFile = fopen("temp.bin", "wb");

	system("cls");

	if (lostRemovePtr == NULL || tempFile == NULL) {
		printf("Unable to open the file for reading!\n");
		exit(-1);
	}
	printf("REMOVE ITEM\n");
	printf("===========\n\n");

	printf("Enter the lost ID that you want to remove: ");
	scanf("%s", &itemToRemove);

	while (fread(&lost, sizeof(Lost), 1, lostRemovePtr)) {
		if (strcmp(lost.itemID, itemToRemove) != 0) {
			printf("A record with requested name found and deleted.\n\n");
			found = 1;
		}
		else {
			fwrite(&lost, sizeof(Lost), 1, tempFile);
		}
	}
	if (!found) {
		printf("No match!\n");
	}

	fclose(lostRemovePtr);
	fclose(tempFile);

	remove("lost.bin");

	rename("temp.bin", "lost.bin");

	system("pause");
}

loginManager() {

	FILE* staff;
	Staff sta;
	char logID[7];
	char logPassword[20];
	char ans;

	staff = fopen("staff.bin", "rb");

	system("cls");
	if (staff == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}
	else {
		int found = 0;

		printf("MANAGER LOGIN PAGE\n");
		printf("==================\n\n");

		printf("Enter your ID: ");
		scanf("%s", &logID);
		printf("Enter your password: ");
		scanf("%s", &logPassword);

		while (fread(&sta, sizeof(Staff), 1, staff)) {
			if (strcmp(sta.ID, logID) == 0) {
				if (strcmp(sta.password, logPassword) == 0) {
					if (strcmp(sta.position, "MANAGER") == 0) {
						printf("Login Successfully!!!!\n");
						printf("Welcome Back ~ \n");
						found++;
						managerFirstMenu();
						break;
					}
				}
				else {
					printf("Invalid ID or password.\n");
					printf("\n\n");
					break;
				}
			}
		}
	}
	fclose(staff);
}

loginStaff() {

	FILE* staff;
	Staff sta;
	char logID[7];
	char logPassword[9];
	char ans;

	staff = fopen("staff.bin", "rb");

	system("cls");
	if (staff == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}
	else {
		int found = 0;

		printf("STAFF LOGIN PAGE\n");
		printf("================\n\n");

		printf("Enter your ID: ");
		scanf("%s", logID);
		printf("Enter your password: ");
		scanf("%s", logPassword);

		while (fread(&sta, sizeof(Staff), 1, staff)) {
			if (strcmp(sta.ID, logID) == 0 && strcmp(sta.password, logPassword) == 0) {
				if (strcmp(sta.position, "MANAGER") != 0) {
					found = 1;
					printf("Login Successfully!!!!\n");
					printf("Welcome Back ~ \n");
					staffFirstMenu();
					break;
				}
			}
		}

		if (!found) {
			printf("Invalid ID or Password! Please try again.\n");
			printf("\n\n");
		}

		fclose(staff);
	}
}
	
displayStaffList() {

	FILE* staff;
	Staff sta[MAXSTAFF];
	int i = 0;
	int count = 0;

	staff = fopen("staff.bin", "rb");

	system("cls");
	if (staff == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}
	printf("STAFF LIST\n");
	printf("==========\n\n");

	printf("%-7s %-20s %-7s %-12s %-12s %-12s %-6s %-10s\n", "ID", "NAME", "GENDER", "CONTACT", "JOB TITLE", "DATE JOINED", "SALARY(RM)", "IC");
	printf("%-7s %-20s %-7s %-12s %-12s %-12s %-6s %-10s\n", "======", "====", "======", "=======", "=========", "===========", "==========", "============");

	while (fread(&sta[i], sizeof(Staff), 1, staff) != 0) {
		printf("%-7s %-20s %-7c %-12s %-12s %-12s %-10d %s\n",
			sta[i].ID, sta[i].name, sta[i].gender, sta[i].phoneno,
			sta[i].position, sta[i].date, sta[i].salary, sta[i].IC);
		i++;
		count++;
	}

	printf("\n\n");
	printf("%d %s.\n\n", count, "staff displayed");

	fclose(staff);
	system("pause");
}

	

forgetPassword() {

	FILE* staff;
	FILE* tempFile;
	Staff sta;
	char logID[7];
	char logIC[14];
	char newPassword[20];
	char logPassphrase[15];

	staff = fopen("staff.bin", "rb");
	tempFile = fopen("temp.bin", "wb");
	
	system("cls");
	if (staff == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}
	else {
		int found = 0;

		system("cls");

		printf("FORGET PASSWORD\n");
		printf("===============\n\n");

		printf("Enter your ID: ");
		scanf("%s", &logID);
		printf("Enter your IC: ");
		scanf("%s", &logIC);
		printf("Enter you passphrase: ");
		scanf("%s", &logPassphrase);

		while (fread(&sta, sizeof(Staff), 1, staff)) {
			if (strcmp(sta.ID, logID) == 0) {
				if (strcmp(sta.IC, logIC) == 0) {
					if (strcmp(sta.valid.passphrase, logPassphrase) == 0)
						printf("Enter the new password: ");
					scanf("%s", &newPassword);
					if (strlen(&newPassword) <= 8) {
						printf("Invalid Password!\n");
					}
					else {
						break;
					}
					strcpy(sta.password, newPassword);
				}
			}
			fwrite(&sta, sizeof(Staff), 1, tempFile);
		}

		fclose(staff);
		fclose(tempFile);

		remove("staff.bin");
		rename("temp.bin", "staff.bin");

		printf("Password updated successfully!\n");

	}
	fclose(staff);
}

updateSalary() {

	FILE* staff;
	FILE* tempFile;
	Staff sta;
	char searchId[7];
	int newSalary;

	staff = fopen("staff.bin", "rb+");
	tempFile = fopen("temp.bin", "wb");
	
	system("cls");
	if (staff == NULL || tempFile == NULL) {
		printf("Unable to open files!\n");
		exit(-1);
	}
	else {

		printf("UPDATE SALARY\n");
		printf("=============\n\n");

		printf("Enter the ID of the staff member whose salary you want to update: ");
		scanf("%s", searchId);

		while (fread(&sta, sizeof(Staff), 1, staff)) {
			if (strcmp(sta.ID, searchId) == 0) {
				printf("Current salary of %s: %d\n", sta.name, sta.salary);
				printf("Enter the new salary: ");
				scanf("%d", &newSalary);
				sta.salary = newSalary;
			}
			fwrite(&sta, sizeof(Staff), 1, tempFile);
		}

		fclose(staff);
		fclose(tempFile);

		remove("staff.bin");
		rename("temp.bin", "staff.bin");

		printf("Salary updated successfully!\n\n");
	}
}

updatePosition() {

	FILE* staff;
	FILE* tempFile;
	Staff sta;
	char searchId[7];
	char newPosition;

	staff = fopen("staff.bin", "rb+");
	tempFile = fopen("temp.bin", "wb");

	system("cls");
	if (staff == NULL || tempFile == NULL) {
		printf("Unable to open files!\n");
		exit(-1);
	}
	else {

		printf("UPDATE POSITION\n");
		printf("===============\n\n");

		printf("Enter the ID of the staff member whose position you want to update: ");
		scanf("%s", searchId);

		while (fread(&sta, sizeof(Staff), 1, staff)) {
			if (strcmp(sta.ID, searchId) == 0) {
				printf("Current position of %s: %s\n", sta.name, sta.position);
				printf("Enter the new position: ");
				scanf("%s", &newPosition);
				strcpy(sta.position,newPosition);
			}
			fwrite(&sta, sizeof(Staff), 1, tempFile);
		}

		fclose(staff);
		fclose(tempFile);

		remove("staff.bin");
		rename("temp.bin", "staff.bin");

		printf("Position updated successfully!\n");
	}
}

updateStaffInfo() {

	int choice;

	system("cls");
	do {
		printf("MODIFY INFORMATION\n");
		printf("==================\n");
		printf("1.Salary\n");
		printf("2.Position\n");
		printf("3.Exit to the menu\n");
		printf("Which info do you want to modify? ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			updateSalary();
			break;

		case 2:
			updatePosition();
			break;

		case 3:
			managerFirstMenu();
			break;

		default:
			printf("Invalid choice!!!\n");
		}
	} while (choice != 3);
}

updateContact() {

	FILE* staff;
	FILE* tempFile;
	Staff sta;
	char searchId[7];
	char newContact;

	staff = fopen("staff.bin", "rb+");
	tempFile = fopen("temp.bin", "wb");

	system("cls");
	if (staff == NULL || tempFile == NULL) {
		printf("Unable to open files!\n");
		exit(-1);
	}
	else {
		printf("UPDATE CONTACT\n");
		printf("==============\n\n");

		printf("Enter your ID: ");
		scanf("%s", searchId);

		while (fread(&sta, sizeof(Staff), 1, staff)) {
			if (strcmp(sta.ID, searchId) == 0) {
				printf("Current contact of %s is %s\n", sta.name, sta.phoneno);
				printf("Enter the new contact: ");
				scanf("%s", &newContact);
				strcpy(sta.phoneno, newContact);
			}
			fwrite(&sta, sizeof(Staff), 1, tempFile);
		}

		fclose(staff);
		fclose(tempFile);

		remove("staff.bin");
		rename("temp.bin", "staff.bin");

		printf("Contact updated successfully!\n");
	}
}

updateStaInfo() {

	int choice;

	system("cls");
	do {
		printf("MODIFY INFORMATION\n");
		printf("==================\n");
		printf("1.Contact\n");
		printf("2.Password\n");
		printf("3.Exit to the menu\n");
		printf("Which info do you want to modify? ");
		scanf("%d", &choice);

		switch (choice) {

		case 1:
			updateContact();
			break;

		case 2:
			updatePassword();
			break;

		case 3:
			staffFirstMenu();
			break;

		default:
			printf("Invalid choice!!!\n");
			printf("Please enter again.\n");
		}
	} while (choice != 3);
}

updatePassword() {

	FILE* staff;
	FILE* tempFile;
	Staff sta;
	char searchId[7];
	char newPassword;

	staff = fopen("staff.bin", "rb+");
	tempFile = fopen("temp.bin", "wb");

	system("cls");
	if (staff == NULL || tempFile == NULL) {
		printf("Unable to open files!\n");
		exit(-1);
	}
	else {
		printf("CHANGE THE PASSWORD\n");
		printf("===================\n\n");

		printf("Enter your ID: ");
		scanf("%s", searchId);

		while (fread(&sta, sizeof(Staff), 1, staff)) {
			if (strcmp(sta.ID, searchId) == 0) {
				printf("Current password of %s is %s\n", sta.name, sta.password);
				printf("Enter the new password: ");
				scanf("%s", &newPassword);
				strcpy(sta.password, newPassword);

				printf("Enter the password again: ");
				rewind(stdin);
				scanf("%s", sta.valid.passwordvalid);
				if (strcmp(sta.password, sta.valid.passwordvalid) != 0) {
					printf("Password doesn't match!\n");
				}
				else {
					break;
				}
			}
			fwrite(&sta, sizeof(Staff), 1, tempFile);
		}

		fclose(staff);
		fclose(tempFile);

		remove("staff.bin");
		rename("temp.bin", "staff.bin");

		printf("Password updated successfully!\n");

	}
}

searchStaff(Staff sta[], int i) {

	FILE* staff;
	staff = fopen("staff.bin", "rb");
	char searchId[7];
	char ans;

	system("cls");
	if (staff == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}
	else {
		do {
			int found = 0;
			printf("SEARCH STAFF\n");
			printf("============\n\n");

			printf("Enter ID of staff to view: ");
			scanf("%s", searchId);

			while (fread(&sta[i], sizeof(Staff), 1, staff)) {
				if (strcmp(searchId, sta[i].ID) == 0) {
					found = 1;
					printf("%-7s %-20s %-7s %-12s %-12s %-12s %-6s %-10s\n", "ID", "NAME", "GENDER", "CONTACT", "JOB TITLE", "DATE JOINED", "SALARY(RM)", "IC");
					printf("%-7s %-20s %-7s %-12s %-12s %-12s %-6s %-10s\n", "======", "====", "======", "=======", "=========", "===========", "==========", "============");
					printf("%-7s %-20s %-7c %-12s %-12s %-12s %-10d %s\n",
						sta[i].ID, sta[i].name, sta[i].gender, sta[i].phoneno,
						sta[i].position, sta[i].date, sta[i].salary, sta[i].IC);
					break;
				}
			}
			if (!found) {
				printf("Not found!!\n");
			}

			printf("\n\n");
			printf("View another (Y=yes)? ");
			scanf(" %c", &ans);
		} while (toupper(ans) == 'Y');
	}

	fclose(staff);
}

removeStaff() {
	FILE* staff;
	FILE* tempFile;
	Staff sta;
	char idToRemove[7];
	int found = 0;

	staff = fopen("staff.bin", "rb");
	tempFile = fopen("temp.bin", "wb");

	system("cls");

	if (staff == NULL || tempFile == NULL) {
		printf("Unable to open the file for reading!\n");
		exit(-1);
	}

	printf("REMOVE STAFF\n");
	printf("===========\n\n");

	printf("Enter the ID that you want to remove: ");
	rewind(stdin);
	scanf("%s", idToRemove);

	while (fread(&sta, sizeof(Staff), 1, staff)) {
		if (strcmp(sta.ID, idToRemove) != 0) {
			printf("A record with requested name found and deleted.\n\n");
			found = 1;
		}
		else {
			fwrite(&sta, sizeof(Staff), 1, tempFile);
		}
	}
	if (!found) {
		printf("No match!\n");
	}

	fclose(staff);
	fclose(tempFile);

	remove("staff.bin");

	rename("temp.bin", "staff.bin");

	system("pause");
}

generateReport() {

	FILE* staff;
	Staff sta;
	char searchPosition[10];
	char ans;
	int headerPrinted = 0;

	system("cls");
	staff = fopen("staff.bin", "rb");
	if (staff == NULL) {
		printf("File is unable to open!!\n");
		exit(-1);
	}
	else {
		do {
			int found = 0;
			printf("REPORT\n");
			printf("======\n\n");

			printf("Enter position that you want to view: ");
			scanf("%s", &searchPosition);

			while (fread(&sta, sizeof(Staff), 1, staff)) {
				if (strcmp(searchPosition, sta.position) == 0) {
					if (!headerPrinted) {
						printf("%-7s %-20s %-7s %-12s %-12s %-12s %-6s %-10s\n", "ID", "NAME", "GENDER", "CONTACT", "JOB TITLE", "DATE JOINED", "SALARY(RM)", "IC");
						printf("%-7s %-20s %-7s %-12s %-12s %-12s %-6s %-10s\n", "======", "====", "======", "=======", "=========", "===========", "==========", "============");
						headerPrinted = 1;
					}
					found = 1;
					printf("%-7s %-20s %-7c %-12s %-12s %-12s %-10d %s\n",
						sta.ID, sta.name, sta.gender, sta.phoneno,
						sta.position, sta.date, sta.salary, sta.IC);
				}
			}
			if (!found) {
				printf("No staff found with the specified position.\n");
			}

			printf("View another (Y=yes)? ");
			scanf(" %c", &ans);
		} while (toupper(ans) == 'Y');
	}
	fclose(staff);
}

managerSecondMenu() {
	
	int ans2;

	system("cls");
	printf("MANAGER LOGIN MENU\n");
	printf("==================\n");
	printf("1.Login\n");
	printf("2.Forget Password\n");
	printf("Enter the number: ");
	scanf("%d", &ans2);

	if (ans2 == 1) {
		loginManager();
	}
	else {
		forgetPassword();
	}
}

staffSecondMenu() {

	int ans2;

	system("cls");
	printf("STAFF LOGIN MENU\n");
	printf("==========\n");
	printf("1.Login\n");
	printf("2.Forget Password\n");
	printf("Enter the number: ");
	scanf("%d", &ans2);

	switch (ans2) {

	case 1:
		loginManager();
		break;

	case 2:
		loginStaff();
		break;

	default:
		printf("Invalid value\n");
		break;
	}

}

managerFirstMenu() {

	int option;
	Staff sta[MAXSTAFF];

	do {
		system("cls");
		printf("MANAGER MAIN MENU\n");
		printf("=================\n");
		printf("1.Add Staff\n");
		printf("2.Search Staff\n");
		printf("3.Update Staff Information\n");
		printf("4.View Staff List\n");
		printf("5.Remove Staff\n");
		printf("6.Position Level Report\n");
		printf("7.Exit\n");
		printf("Enter the number: ");
		scanf("%d", &option);

		switch (option) {

		case 1:
			addStaff();
			break;

		case 2:
			searchStaff(sta, MAXSTAFF);
			break;

		case 3:
			updateStaffInfo();
			break;

		case 4:
			displayStaffList();
			break;

		case 5:
			generateReport();
			break;

		case 6:
			removeStaff();
			break;

		case 7:
			printf("Exit now.........\n");
			printf("\n\n");
			break;

		default:
			printf("Invalid option\n");
			printf("Please enter again\n");
			break;
		}
	} while (option != 7);
}

staffFirstMenu() {

	int option;
	Staff sta[MAXSTAFF];

	do {
		system("cls");
		printf("STAFF MAIN MENU\n");
		printf("===============\n");
		printf("1.Update Staff Information\n");
		printf("2.Display Staff Information\n");
		printf("3.Item Found!\n");
		printf("4.Show the list\n");
		printf("5.Remove item\n\n");
		printf("6.Exit\n");
		printf("Enter the number: ");
		scanf("%d", &option);

		switch (option) {

		case 1:
			updateStaInfo();
			break;

		case 2:
			searchStaff(sta,MAXSTAFF);
			break;

		case 3:
			foundItem();
			break;

		case 4:
			lostAndFoundList();
			system("pause");
			break;

		case 5:
			removeItem();
			break;

		case 6:
			removeStaff(sta, MAXSTAFF);
			break;

		case 7:
			printf("Exit now.........\n");
			printf("\n\n");
			break;

		default:
			printf("Invalid Number!!!\n");
			printf("Please enter again.\n");
			break;
		}
	} while (option != 7);
}

