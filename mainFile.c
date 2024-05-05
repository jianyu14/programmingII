#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int getValidChoice(int lowerBound, int upperBound);
staffMainMenu();

void main() {
	system("cls");
	printf("_________    ___    ___         ___       _________    ___     ___   ___    ___   ___            ___\n");
	printf("|__   __|    |  |   |  |       /   \\      |__   __|   |  |    /  /   |  |   |  |  |  |          /   \\\n");
	printf("  |   |      |  |___|  |      /     \\       |   |     |  |___/  /    |  |   |  |  |  |         /     \\\n");
	printf("  |   |      |   ___   |     /       \\      |   |     |   ___  /     |  |   |  |  |  |        /       \\\n");
	printf("  |   |      |  |   |  |    /   ___   \\   __|   |__   |  |   \\  \\    |  |___|  |  |  |___    /   ___   \\\n");
	printf("  |___|      |__|   |__|   /___/   \\___\\ |_________|  |__|    \\__\\   |_________|  |______|  /___/   \\___\\\n\n");

	int choice;
	do {
		system("cls");
		printf("=============================================\n");
		printf("WELCOME TO THAI KU LA TRAIN TICKETING SYSTEM!\n");
		printf("=============================================\n\n");
		printf("MAIN MENU\n\n");
		printf("1. Staff Page\n");
		printf("2. Member Page\n");
		printf("3. Exit\n\n");
		printf("Please select your choice: ");
		choice = getValidChoice(1, 3);
		system("cls");
		switch (choice) {
		case 1:
			staffMainMenu();
			break;
		case 2:
			memberMain();
			break;
		case 3:
			break;
		}
	} while (choice != 3);

}
int getValidChoice(int lowerBound, int upperBound) {
	char input[10];
	int choice;
	do {
		scanf("%s", input);

		//convert the input to integer for choice
		choice = atoi(input);
		if (choice < lowerBound || choice > upperBound) {
			printf("Invalid choice. Please enter a number between %d and %d: ", lowerBound, upperBound);
		}
		else {
			return choice;
		}
	} while (1);
}

staffMainMenu() {
	int choice;
	do {
		system("cls");
		printf("===========================\n");
		printf("WELCOME TO STAFF MAIN MENU!\n");
		printf("===========================\n\n");
		printf("MAIN MENU\n\n");
		printf("1. Staff Information\n");
		printf("2. Train Scheduling\n");
		printf("3. Booking Ticket\n");
		printf("4. Return To Previous Page\n\n");
		printf("Please select your choice: ");
		choice = getValidChoice(1, 4);
		system("cls");
		switch (choice) {
		case 1:
			menuStaff();
			break;
		case 2:
			tSchedulingStaffMenu();;
			break;
		case 3:
			staffMenuBK();
			break;
		case 4:
			break;
		}
	} while (choice != 4);
};
