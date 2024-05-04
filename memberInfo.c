#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<time.h>
#pragma warning(disable:4996)

#define MAXMEMBER 1000
#define MAXITEM 1000
#define MAXFOUND 1000

typedef struct {
	int day, month, year;
}Date;

typedef struct {
	int hours, minutes;
}Time;

typedef struct {
	char memberName[30];
	char memberGender;
	char memberIC[13];
	char memberContact[12];
	Date dateJoined[11];
	char memberPassword[30];
	char memberPassphrase[30];
	char memberID[7];
}Members;

typedef struct {
	char mealName[7], mainFood[100], drinks[100], snacks[100];
	double mealPrice;
}Meal;

typedef struct {
	char ticketID[10], psgName[100], psgIC[15], seatNo[4], coach, remarks[300];
	Meal selectedMeal;
	// psg = passenger
}Ticket;


typedef struct {
	//invoice
	char invoiceNo[10], invTrnID[7], memberID[7];
	int ticketQtt;
	double totalAmount;
	Date paymentDate;
	Ticket ticBook[120];
}Invoice;

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
}Found;

void memberFirstMenu();
int getValidChoice(int lowerBound, int upperBound);
void addMemberAcc();
void loginMemberAcc();
void forgetMemberPassword();
void memberSecondMenu();
bool memberInformation(Members* member, bool accountDeleted);
void searchMemberInformation(Members* mem);
void displayMemberInformation(Members* mem);
void modifyMemberInformation(Members* mem);
void memberLost();
void memberLostSearch();
void lostAndFoundList();
bool deleteMemberInformation(Members* mem, bool isAccountDeleted);
void memberMain();

void main() {
	int choice;
	do {
		system("cls");
		printf("=======================\n");
		printf("WELCOME TO TRAIN TICKETING SYSTEM!\n");
		printf("=======================\n\n");
		printf("MAIN MENU\n\n");
		printf("1. Staff Page\n");
		printf("2. Member Page\n");
		printf("3. Exit\n\n");
		printf("Please select your choice: ");
		choice = getValidChoice(1, 3);
		system("cls");
		switch (choice) {
		case 1:
			staffMain();
			break;
		case 2:
			memberMain();
			break;
		case 3:
			break;
		}
	} while (choice != 3);
}

void memberMain() {
	int memFirstChoice;

	do {
		
		memberFirstMenu();
		memFirstChoice = getValidChoice(1, 4);
		switch (memFirstChoice) {
		case 1:
			addMemberAcc();
			break;
		case 2:
			loginMemberAcc();
			break;
		case 3:
			forgetMemberPassword();
			break;
		case 4:
			break;
		}
		
	} while (memFirstChoice != 4);
	
}

void memberFirstMenu() {
	printf("MEMBER PAGE\n\n");
	printf("1. Register a new account\n");
	printf("2. Login your account\n");
	printf("3. Forget password?\n");
	printf("4. Back to main menu\n\n");
	printf("Please select your choice from the following: ");
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

void addMemberAcc() {
	char rePassword[30];
	char createChoice;	
	int i = 0;
	int isValid;
	Members member[MAXMEMBER];
	Members temp;
	FILE* addmem;
	time_t current_time = time(NULL);
	addmem = fopen("memberInfo.bin", "rb+");

	system("cls");
	if (addmem == NULL) {
		printf("Unable to open the file...\n\n");
		exit(-1);
	}

	printf("MEMBER REGISTRATION\n\n");
	printf("Enter your name: ");
	rewind(stdin);
	scanf("%[^\n]", &temp.memberName);
	for (int i = 0; temp.memberName[i] != '\0'; i++) {
		temp.memberName[i] = toupper(temp.memberName[i]);
	}
	printf("Enter your gender (M/F): ");
	scanf(" %c", &temp.memberGender);
	temp.memberGender = toupper(temp.memberGender);
	while (temp.memberGender != 'M' && temp.memberGender != 'F') {
		printf("Invalid gender. Please re-enter your gender: ");
		scanf(" %c", &temp.memberGender);
		temp.memberGender = toupper(temp.memberGender);
	}
	printf("Enter your IC (12 digits without '-'): ");
	rewind(stdin);
	scanf("%s", &temp.memberIC);

	//Check IC format
	do {
		isValid = 1;
		if (strlen(temp.memberIC) != 12) {
			isValid = 0;
			printf("Invalid IC format. Please enter 12 digits format (without '-'): ");
			rewind(stdin);
			scanf("%s", &temp.memberIC);
		}
		else {
			for (int i = 0; temp.memberIC[i] != '\0'; i++) {
				if (!isdigit(temp.memberIC[i])) {
					isValid = 0;
					printf("Invalid IC format. Please enter 12 digits format (without '-'): ");
					rewind(stdin);
					scanf("%s", &temp.memberIC);
				}
			}
		}
	} while (!isValid);

	printf("Enter your phone number (10 or 11 digits without '-'): ");
	rewind(stdin);
	scanf("%s", &temp.memberContact);

	//Check phone format
	do {
		isValid = 1;
		if (strlen(temp.memberContact) != 10 && strlen(temp.memberContact)!=11) {
			isValid = 0;
			printf("Invalid phone number format. Please enter 10 or 11 digits format (without '-'): ");
			rewind(stdin);
			scanf("%s", &temp.memberContact);
		}
		else {
			for (int i = 0; temp.memberContact[i] != '\0'; i++) {
				if (!isdigit(temp.memberContact[i])) {
					isValid = 0;
					printf("Invalid phone number format. Please enter 10 or 11 digits format (without '-'): ");
					rewind(stdin);
					scanf("%s", &temp.memberContact);
				}
			}
		}
	} while (!isValid);

	printf("Create your password: ");
	rewind(stdin);
	scanf("%[^\n]", &temp.memberPassword);

	while (strlen(temp.memberPassword) < 8) {
		printf("Your password must be at least 8 characters. Please create again: ");
		rewind(stdin);
		scanf("%[^\n]", &temp.memberPassword);
	}

	printf("Re-enter your password: ");
	rewind(stdin);
	scanf("%[^\n]", &rePassword);
	
	while(strcmp(temp.memberPassword, rePassword)!=0){
		printf("Password does not match. Please create again your password: ");
		rewind(stdin);
		scanf("%[^\n]", &temp.memberPassword);
		while (strlen(temp.memberPassword) < 8) {
			printf("Your password must be at least 8 characters. Please create again: ");
			rewind(stdin);
			scanf("%[^\n]", &temp.memberPassword);
		}
		printf("Re-enter your password: ");
		rewind(stdin);
		scanf("%[^\n]", &rePassword);
	}

	printf("Create your passphrase: ");
	rewind(stdin);
	scanf("%[^\n]", &temp.memberPassphrase);

	printf("Are you sure you want to create the account ? (Y=Yes/N=No): ");
	rewind(stdin);
	scanf("%c", &createChoice);

	while (toupper(createChoice) != 'Y' && toupper(createChoice) != 'N') {
		printf("Invalid choice. Please enter a valid choice. \n");
		printf("Are you sure you want to create the account ? (Y=Yes/N=No): ");
		rewind(stdin);
		scanf("%c", &createChoice);
	}
	printf("\n\n");

	if(toupper(createChoice) == 'Y') {
		i = 0;
		char lastMemberID[7];
		int newLastMemberID = 1;
		while (fread(&member[i], sizeof(Members), 1, addmem)) {
			i++;
		}

		if (i > 0) {
			strcpy(lastMemberID, member[i - 1].memberID);
			newLastMemberID = atoi(lastMemberID + 1) + 1;
		}
	
		sprintf(temp.memberID, "M%05d", newLastMemberID);
		strftime(temp.dateJoined, 11, "%Y-%m-%d", localtime(&current_time));
		member[i] = temp;

		fwrite(&member[i], sizeof(Members), 1, addmem);

		system("cls");
		printf("Your member ID is %s. Please login again. \n\n\n", member[i].memberID);
	}
	fclose(addmem);
}

void loginMemberAcc() {
	int found = 0;
	int i = 0;
	int loginArray;
	int count;
	int memSecondChoice;
	char memberID[7], memberPassword[30];
	bool accountDeleted = false;
	Members member[MAXMEMBER];
	FILE* loginMem;
	loginMem = fopen("memberInfo.bin", "rb");

	system("cls");
	if (loginMem == NULL) {
		printf("Unable to open the file...\n\n");
		exit(-1);
	}

	while (fread(&member[i], sizeof(Members), 1, loginMem)) {
		i++;
	}

	count = i;

	fclose(loginMem);


	printf("MEMBER LOGIN PAGE\n\n");
	printf("Please enter your member ID to login: ");
	rewind(stdin);
	scanf("%s", &memberID);
	printf("Please enter your password: ");
	rewind(stdin);
	scanf("%[^\n]", &memberPassword);
	for (int i = 0; i < count; i++) {
		if (strcmp(member[i].memberID, memberID) == 0) {
			if (strcmp(member[i].memberPassword, memberPassword) == 0) {
				found = 1;
				loginArray = i;
				break;
			}
		}
	}
	system("cls");
	if (found == 1) {
		printf("You are now succesfully login.\n\n");
		do {
			memberSecondMenu();
			memSecondChoice = getValidChoice(1, 4);
			system("cls");
			switch (memSecondChoice) {
			case 1:
				userMenuBK(&member[i]);
				break;
			case 2:
				//ziqing
				break;
			case 3:
				accountDeleted = memberInformation(&member[loginArray], &accountDeleted);
				break;
			case 4:
				system("cls");
				printf("You are now logged out.\n\n");
				break;
			}
		} while (memSecondChoice != 4 && accountDeleted == false);

	}
	else {
		printf("Member ID not found or wrong password entered. \n\n");
	}
}

void forgetMemberPassword() {
	Members member[MAXMEMBER];
	Members temp;
	int i = 0;
	int isValid;
	int found = 0;
	int count;
	char rePassword[30];
	FILE *forgetMemPass, *newMemPass;
	forgetMemPass = fopen("memberInfo.bin", "rb");

	system("cls");
	if (forgetMemPass == NULL) {
		printf("Unable to open the file...\n\n");
		exit(-1);
	}	

	while (fread(&member[i], sizeof(Members), 1, forgetMemPass)) {
		i++;
	}

	count = i;
	fclose(forgetMemPass);

	printf("PASSWORD RESET PAGE\n\n");
	printf("To verify you are the account holder, please enter the following data: \n");
	printf("Please enter your member ID: ");
	rewind(stdin);
	scanf("%s", &temp.memberID);
	printf("Please enter your IC (12 digits format without '-'): ");
	rewind(stdin);
	scanf("%s", &temp.memberIC);

	do {
		isValid = 1;
		if (strlen(temp.memberIC) != 12) {
			isValid = 0;
			printf("Invalid IC format. Please enter 12 digits format (without '-'): ");
			rewind(stdin);
			scanf("%s", &temp.memberIC);
		}
		else {
			for (int i = 0; temp.memberIC[i] != '\0'; i++) {
				if (!isdigit(temp.memberIC[i])) {
					isValid = 0;
					printf("Invalid IC format. Please enter 12 digits format (without '-'): ");
					rewind(stdin);
					scanf("%s", &temp.memberIC);
				}
			}
		}
	} while (!isValid);

	printf("Please enter your passphrase: ");
	rewind(stdin);
	scanf("%[^\n]", &temp.memberPassphrase);


	i = 0;
	while (i < count) {
		if (strcmp(member[i].memberID, temp.memberID) == 0 &&
			strcmp(member[i].memberIC, temp.memberIC) == 0 &&
			strcmp(member[i].memberPassphrase, temp.memberPassphrase) == 0) {
			found = 1;
			break;
		}
		else { 
			i++; 
		}
	}

	newMemPass = fopen("memberInfo.bin", "wb");

	if (newMemPass == NULL) {
		printf("Unable to open the file...\n\n");
		exit(-1);
	}
	
	if (found == 1) {
		printf("Please create a new password: ");
		rewind(stdin);
		scanf("%[^\n]", &temp.memberPassword);
		while (strlen(temp.memberPassword) < 8) {
			printf("Your password must be at least 8 characters. Please create again: ");
			rewind(stdin);
			scanf("%[^\n]", &temp.memberPassword);
		}
		printf("Re-enter your password: ");
		rewind(stdin);
		scanf("%[^\n]", &rePassword);
		while (strcmp(temp.memberPassword, rePassword) != 0) {
			printf("Password does not match. Please create again your password: ");
			rewind(stdin);
			scanf("%[^\n]", &temp.memberPassword);
			while (strlen(temp.memberPassword) < 8) {
				printf("Your password must be at least 8 characters. Please create again: ");
				rewind(stdin);
				scanf("%[^\n]", &temp.memberPassword);
			}
			printf("Re-enter your password: ");
			rewind(stdin);
			scanf("%[^\n]", &rePassword);
		}
		strcpy(member[i].memberPassword, temp.memberPassword);
		
	}

	for (i = 0; i < count; i++) {
		fwrite(&member[i], sizeof(Members), 1, newMemPass);
	}

	system("cls");
	if (found == 1) { 
		printf("Your password is now reset. Please login again. \n\n"); 
	}
	else {
		printf("Sorry, invalid member ID or wrong data entered.\n\n");
	}

	fclose(newMemPass);
}

void memberSecondMenu() {
	printf("MEMBER MENU\n\n");
	printf("1. Ticket booking\n");
	printf("2. Train scheduling\n");
	printf("3. Your information\n");
	printf("4. Log out\n\n");
	printf("Please select your choice from the following: ");
}

bool memberInformation(Members *member, bool accountDeleted) {
	int memThirdChoice, option;
	Members currentMem;
	currentMem = *member;
	accountDeleted = false;
	system("cls");
	do {
		printf("MEMBER INFORMATION\n\n");
		printf("1. Search booking history\n");
		printf("2. Modify your information\n");
		printf("3. Display your information\n");
		printf("4. Lost and found\n");
		printf("5. Delete account\n");
		printf("6. Back to previous menu\n\n");
		printf("Please select your choice from the following: ");
		memThirdChoice = getValidChoice(1, 6);
		system("cls");
		switch (memThirdChoice) {
		case 1:
			searchMemberInformation(&currentMem);
			break;
		case 2:
			modifyMemberInformation(&currentMem);
			break;
		case 3:
			displayMemberInformation(&currentMem);
			break;
		case 4:
			do {
				printf("LOST AND FOUND\n\n");
				printf("1. Report lost item\n");
				printf("2. Check lost item status\n");
				printf("3. Display lost item list\n");
				printf("4. Back to previous menu\n\n");
				printf("Please select your choice from the following: ");
				option = getValidChoice(1, 4);
				system("cls");
				switch (option) {
				case 1:
					memberLost();
					break;
				case 2:
					memberLostSearch();
					break;
				case 3:
					lostAndFoundList();
					break;
				case 4:
					break;
				default:
					printf("Invalid choice. Please enter a valid choice(1, 2, 3, 4).\n\n");
					break;
				}
			} while (option != 4);
			
			break;
		case 5:
			accountDeleted = deleteMemberInformation(&currentMem, &accountDeleted);
			break;
		case 6:
			break;
		}
	} while (memThirdChoice != 6 && accountDeleted == false);
	return accountDeleted;
}

void searchMemberInformation(Members *mem) {
	Invoice booking;
	char choice;
	char bookingID[10];
	int i = 0;
	int quantity;
	int found = 0;
	FILE* bookingPtr;
	bookingPtr = fopen("bookingTic.txt", "r");

	system("cls");
	if (bookingPtr == NULL) {
		printf("Unable to open the file...\n\n");
		exit(-1);
	}

	printf("SEARCH BOOKING HISTORY\n\n");
	printf("Do you want to search your booking history? (Y=Yes/N=No): ");
	scanf(" %c", &choice);

	while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
		printf("Invalid choice. Please re-enter your choice (Y=Yes/N=No): ");
		scanf(" %c", &choice);
	}
	system("cls");
	while (toupper(choice) == 'Y') {
		system("cls");
		printf("SEARCH BOOKING HISTORY\n\n");
		printf("Enter your booking ID to search: ");
		rewind(stdin);
		scanf("%s", &bookingID);

		while (fscanf(bookingPtr, "%[^|]|%[^|]|%[^|]|%d|%lf|%d/%d/%d\n",
			booking.invoiceNo, booking.invTrnID, &booking.memberID, &booking.ticketQtt, &booking.totalAmount,
			&booking.paymentDate.day, &booking.paymentDate.month, &booking.paymentDate.year) != EOF) {
			quantity = booking.ticketQtt;
			for (i = 0; i < quantity; i++) {
				fscanf(bookingPtr, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^\n]\n",
					booking.ticBook[i].ticketID, booking.ticBook[i].psgName, booking.ticBook[i].psgIC, booking.ticBook[i].seatNo,
					&booking.ticBook[i].coach, booking.ticBook[i].remarks);

				fscanf(bookingPtr, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", booking.ticBook[i].selectedMeal.mealName,
					booking.ticBook[i].selectedMeal.mainFood, booking.ticBook[i].selectedMeal.drinks,
					booking.ticBook[i].selectedMeal.snacks, &booking.ticBook[i].selectedMeal.mealPrice);
			}
			if (strcmp(booking.invoiceNo, bookingID) == 0 && strcmp(booking.memberID, mem->memberID) == 0) {
				found = 1;
				break;
			}
		}

		system("cls");
		if (found == 1) {
			printf("%s\t%s\t%s  \t%s     \t%s\n", "BOOKING ID", "TRAIN ID", "TICKET QUANTITY", "PAYMENT", "PAYMENT DATE");
			printf("==============\t==============\t======================\t=============\t===============\n");
			printf("%s\t%-10s\t%-20d\tRM%.2lf\t%02d/%02d/%d\n\n", booking.invoiceNo, booking.invTrnID, booking.ticketQtt, booking.totalAmount,
				booking.paymentDate.day, booking.paymentDate.month, booking.paymentDate.year);
			printf("%s\t%s             \t%s\t%s\t%s\n", "TICKET ID", "PASSENGER NAME", "SEAT NO", "COACH", "REMARKS");
			printf("==============\t==============================\t=======\t=====\t==========================\n");
			for (i = 0; i < quantity; i++) {
				printf("%s\t%-30s\t%s\t%-c\t%-20s\n", booking.ticBook[i].ticketID, booking.ticBook[i].psgName, booking.ticBook[i].seatNo,
					booking.ticBook[i].coach, booking.ticBook[i].remarks);
			}
			printf("\n");
			printf("%s\t%-20s\t%-20s\t%-20s\t%s\n", "MEAL NAME", "MAIN FOOD", "DRINKS", "SNACKS", "MEAL PRICE");
			printf("==============\t=====================\t=====================\t=====================\t=============\n");
			for (i = 0; i < quantity; i++) {
				printf("%s    \t%-20s\t%-20s\t%-20s\tRM%.2lf\n", booking.ticBook[i].selectedMeal.mealName,
					booking.ticBook[i].selectedMeal.mainFood, booking.ticBook[i].selectedMeal.drinks,
					booking.ticBook[i].selectedMeal.snacks, booking.ticBook[i].selectedMeal.mealPrice);
			}
			printf("\n");
		}
		else {
			printf("Booking record not found.\n\n");
		}
		
		printf("Any more booking history to search? (Y=Yes/N=No): ");
		scanf(" %c", &choice);

		while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
			printf("Invalid choice. Please re-enter your choice (Y=Yes/N=No): ");
			scanf(" %c", &choice);
		}
		system("cls");
	}
	fclose(bookingPtr);
}

void modifyMemberInformation(Members *mem) {
	FILE *readMemPtr, *modifyMemPtr;
	int memFourthChoice;
	int isValid;
	int i = 0;
	int count;
	int modifyArray;
	char newMemberContact[12];
	char oldMemberPassword[30];
	char newMemberPassword[30];
	char rePassword[30];
	char choice;
	Members modifyCurrentMem;
	Members member[MAXMEMBER];
	modifyCurrentMem = *mem;
	readMemPtr = fopen("memberInfo.bin", "rb");

	system("cls");
	if (readMemPtr == NULL) {
		printf("Unable to open the file...\n\n");
		exit(-1);
	}

	while (fread(&member[i], sizeof(Members), 1, readMemPtr)) {
		i++;
	}
	count = i;
	fclose(readMemPtr);

	do {
		printf("MODIFY YOUR INFORMATION\n\n");
		printf("1. Change contact\n");
		printf("2. Change password\n");
		printf("3. Back to previous menu\n\n");
		printf("Please select your choice from the following: ");
		memFourthChoice = getValidChoice(1, 3);
		system("cls");
		switch (memFourthChoice) {
		case 1:
			printf("CHANGE CONTACT\n\n");
			printf("Your current phone number is %s.\n\n", modifyCurrentMem.memberContact);
			printf("Please enter your new phone number (10 or 11 digits without '-'): ");
			rewind(stdin);
			scanf("%s", &newMemberContact);

			do {
				isValid = 1;
				if (strlen(newMemberContact) != 10 && strlen(newMemberContact) != 11) {
					isValid = 0;
					printf("Invalid phone number format. Please enter 10 or 11 digits format (without '-'): ");
					rewind(stdin);
					scanf("%s", &newMemberContact);
				}
				else {
					for (int i = 0; newMemberContact[i] != '\0'; i++) {
						if (!isdigit(newMemberContact[i])) {
							isValid = 0;
							printf("Invalid phone number format. Please enter 10 or 11 digits format (without '-'): ");
							rewind(stdin);
							scanf("%s", &newMemberContact);
						}
					}
				}
			} while (!isValid);

			printf("Are you sure you want to change your phone number? (Y=Yes/N=No): ");
			scanf(" %c", &choice);
			while (toupper(choice != 'Y' && toupper(choice) != 'N')) {
				printf("Invalid choice. Please re-enter your choice (Y=Yes/N=No): ");
				scanf(" %c", &choice);
			}
			system("cls");
			if (toupper(choice) == 'Y') {
				strcpy(modifyCurrentMem.memberContact, newMemberContact);

				modifyMemPtr = fopen("memberInfo.bin", "wb");

				if (modifyMemPtr == NULL) {
					printf("Unable to open the file...\n\n");
					exit(-1);
				}

				for (i = 0; i < count; i++) {
					if (strcmp(member[i].memberID, modifyCurrentMem.memberID) == 0) {
						strcpy(member[i].memberContact, modifyCurrentMem.memberContact);
						modifyArray = i;
						break;
					}
				}

				for (i = 0; i < count; i++) {
					fwrite(&member[i], sizeof(Members), 1, modifyMemPtr);
				}
				
				printf("Your phone number is now changed to %s.\n\n", member[modifyArray].memberContact);

				fclose(modifyMemPtr);
			}
			break;
		case 2:
			printf("CHANGE PASSWORD\n\n");
			printf("Enter your old password: ");
			rewind(stdin);
			scanf("%[^\n]", &oldMemberPassword);
			while (strcmp(modifyCurrentMem.memberPassword, oldMemberPassword) != 0) {
				printf("Wrong password entered. Enter again: ");
				rewind(stdin);
				scanf("%[^\n]", &oldMemberPassword);
			}
			printf("Enter your new password: ");
			rewind(stdin);
			scanf("%[^\n]", &newMemberPassword);
			while (strlen(newMemberPassword) < 8) {
				printf("Your password must be at least 8 characters. Please create again: ");
				rewind(stdin);
				scanf("%[^\n]", &newMemberPassword);
			}
			printf("Re-enter your new password: ");
			rewind(stdin);
			scanf("%[^\n]", &rePassword);
			while (strcmp(newMemberPassword, rePassword) != 0) {
				printf("Password does not match. Please create again your password: ");
				rewind(stdin);
				scanf("%[^\n]", &newMemberPassword);
				while (strlen(newMemberPassword) < 8) {
					printf("Your password must be at least 8 characters. Please create again: ");
					rewind(stdin);
					scanf("%[^\n]", &newMemberPassword);
				}
				printf("Re-enter your password: ");
				rewind(stdin);
				scanf("%[^\n]", &rePassword);
			}
			strcpy(modifyCurrentMem.memberPassword, newMemberPassword);
			modifyMemPtr = fopen("memberInfo.bin", "wb");

			if (modifyMemPtr == NULL) {
				printf("Unable to open the file...\n\n");
				exit(-1);
			}

			for (i = 0; i < count; i++) {
				if (strcmp(member[i].memberID, modifyCurrentMem.memberID) == 0) {
					strcpy(member[i].memberPassword, modifyCurrentMem.memberPassword);
					break;
				}
			}

			for (i = 0; i < count; i++) {
				fwrite(&member[i], sizeof(Members), 1, modifyMemPtr);
			}
			system("cls");
			printf("Your password is now changed.\n\n");
			fclose(modifyMemPtr);
			break;
		case 3:
			break;
		}
	} while (memFourthChoice != 3);

}

void displayMemberInformation(Members *mem) {
	system("cls");
	printf("MEMBER INFORMATION\n\n");
	printf("%-12s%-30s%-8s%-13s%-12s%-30s%-12s\n", "MEMBER ID", "NAME", "GENDER", "NRIC", "PHONE", "PASSPHRASE", "DATE JOINED");
	printf("=========== ============================= ======= ============ =========== ============================= ============\n");
	printf("%-12s%-30s%-8c%-13s%-12s%-30s%-12s\n\n", mem->memberID, mem->memberName, 
		mem->memberGender, mem->memberIC, mem->memberContact, mem->memberPassphrase,  mem->dateJoined);
}

void memberLost() {

	FILE* lostPtr;
	Lost lost[MAXITEM];
	Lost temp;
	int i = 0;
	char lastItemID[7];
	int newLastItemID = 1;
	char choice;
	lostPtr = fopen("lost.bin", "ab+");

	system("cls");
	if (lostPtr == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}

	while (fread(&lost[i], sizeof(Lost), 1, lostPtr)) {
		i++;
	}

	if (i > 0) {
		strcpy(lastItemID, lost[i - 1].itemID);
		newLastItemID = atoi(lastItemID + 1) + 1;
	}

	do {
		printf("REPORT LOST ITEM\n\n");
		printf("Enter your lost item: ");
		rewind(stdin);
		scanf("%[^\n]", &temp.description);
		printf("Enter your item lost date (dd/mm/yyyy): ");
		rewind(stdin);
		scanf("%d/%d/%d", &temp.lostDate.day, &temp.lostDate.month, &temp.lostDate.year);
		printf("Enter your item lost time (hh:mm): ");
		rewind(stdin);
		scanf("%d:%d", &temp.lostTime.hours, &temp.lostTime.minutes);
		printf("Enter your item lost place: ");
		rewind(stdin);
		scanf("%[^\n]", &temp.lostPlace);

		sprintf(temp.itemID, "L%05d", newLastItemID);

		lost[i] = temp;

		fwrite(&lost[i], sizeof(Lost), 1, lostPtr);

		system("cls");
		printf("Your lost item ID is %s. Do refer to this ID to check its status.\n\n", lost[i].itemID);

		newLastItemID++;

		printf("Any more lost item? (Y=Yes/N=No): ");
		scanf(" %c", &choice);

		while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
			printf("Invalid choice. Please enter a valid choice (Y=Yes/N=No): ");
			scanf(" %c", &choice);
		}
		system("cls");
	} while (toupper(choice) == 'Y');

	fclose(lostPtr);
}

void memberLostSearch() {

	FILE* lostCheckPtr, * foundCheckPtr;
	Lost lost;
	Found found;
	char checkItemID[7];
	int matched = 0;
	int lostRecord = 0;
	char choice;
	lostCheckPtr = fopen("lost.bin", "rb");
	foundCheckPtr = fopen("found.bin", "rb");

	system("cls");
	if (foundCheckPtr == NULL || lostCheckPtr == NULL) {
		printf("Unable to open the file(s)...\n\n");
		exit(-1);
	}

	do {
		printf("CHECK LOST ITEM STATUS\n\n");
		printf("Enter your lost item ID to check the status: ");
		rewind(stdin);
		scanf("%s", &checkItemID);

		while (fread(&found, sizeof(Found), 1, foundCheckPtr)) {
			if (strcmp(found.itemID, checkItemID) == 0) {
				matched = 1;
				break;
			}
		}

		if (!matched) {
			while (fread(&lost, sizeof(Lost), 1, lostCheckPtr)) {
				if (strcmp(lost.itemID, checkItemID) == 0) {
					lostRecord = 1;
					break;
				}
			}
		}

		system("cls");
		if (matched == 1) {
			printf("%-14s%-17s%-17s\n", "LOST ITEM ID", "ITEM FOUND DATE", "ITEM FOUND TIME");
			printf("============  ===============  ===============\n");
			printf("%-14s%02d/%02d/%4d %02d:%02d\n\n", found.itemID, found.foundDate.day, found.foundDate.month, found.foundDate.year, found.foundTime.hours, found.foundTime.minutes);
		}
		else {
			if (lostRecord == 1) {
				printf("%-14s%-30s  %-15s %-15s %-20s  %-12s\n", "LOST ITEM ID", "LOST ITEM", "LOST ITEM DATE", "LOST ITEM TIME", "LOST ITEM PLACE", "LOST STATUS");
				printf("============  ==============================  ==============  ==============  ====================  ============\n");
				printf("%-14s%-30s  %02d/%02d/%-4d      %02d:%02d           %-20s  %-10s\n\n", lost.itemID, lost.description, lost.lostDate.day,
					lost.lostDate.month, lost.lostDate.year, lost.lostTime.hours, lost.lostTime.minutes,
					lost.lostPlace, "NOT FOUND");
			}
			else {
				printf("Your lost item has no record.\n\n");
			}
		}

		printf("Any more lost item to check? (Y=Yes/N=No) :");
		scanf(" %c", &choice);

		while (toupper(choice) != 'Y' && toupper(choice) != 'N') {
			printf("Invalid choice. Please enter a valid choice (Y=Yes/N=No): ");
			scanf(" %c", &choice);
		}
		system("cls");
	} while (toupper(choice) == 'Y');

	fclose(foundCheckPtr);
	fclose(lostCheckPtr);
}

void lostAndFoundList() {

	FILE* lostPtr;
	Lost lost[MAXITEM];
	int i = 0;
	int count = 0;
	lostPtr = fopen("lost.bin", "ab+");

	system("cls");
	if (lostPtr == NULL) {
		printf("Unable to open the file!\n");
		exit(-1);
	}

	printf("%-14s%-30s  %-15s %-15s %-20s  %-12s\n", "LOST ITEM ID", "LOST ITEM", "LOST ITEM DATE", "LOST ITEM TIME", "LOST ITEM PLACE", "LOST STATUS");
	printf("============  ==============================  ==============  ==============  ====================  ============\n");
	while (fread(&lost[i], sizeof(Lost), 1, lostPtr) == 1) {
		printf("%-14s%-30s  %02d/%02d/%-4d      %02d:%02d           %-20s  %-10s\n\n", lost[i].itemID, lost[i].description, lost[i].lostDate.day,
			lost[i].lostDate.month, lost[i].lostDate.year, lost[i].lostTime.hours, lost[i].lostTime.minutes,
			lost[i].lostPlace, "NOT FOUND");
		i++;
		count++;
	}
	printf("%d lost item(s) displayed.\n\n", count);
}


bool deleteMemberInformation(Members *mem, bool isAccountDeleted) {
	FILE* fCopy, * fPaste;
	char confirm;
	int i = 0;
	Members member[MAXMEMBER];

	system("cls");
	printf("DELETE ACCOUNT\n\n");
	printf("Are you sure you want to delete your account? \n");
	printf("(Y=Yes/N=No): ");
	scanf(" %c", &confirm);

	while (toupper(confirm) != 'Y' && toupper(confirm) != 'N') {
		printf("Invalid choice. Please re-enter your choice (Y=Yes/N=No): ");
		scanf(" %c", &confirm);
	}

	system("cls");
	if (toupper(confirm) == 'Y') {
		fCopy = fopen("memberInfo.bin", "rb");
		fPaste = fopen("memberInfoTemp.bin", "wb");

		if (fCopy == NULL || fPaste == NULL) {
			printf("Unable to open the file(s)...\n\n");
			exit(-1);
		}

		while (fread(&member[i], sizeof(Members), 1, fCopy)) {
			if (strcmp(member[i].memberID, mem->memberID) != 0) {
				fwrite(&member[i], sizeof(Members), 1, fPaste);
			}
			i++;
		}

		fclose(fCopy);
		fclose(fPaste);
		remove("memberInfo.bin");

		if (rename("memberInfoTemp.bin", "memberInfo.bin") == 0) {
			printf("Your account is deleted. We are sad to see you go. \n\n");
			isAccountDeleted = true;
		}

		return isAccountDeleted;
	}
	else {
		isAccountDeleted = false;
		return isAccountDeleted;
	}
}
