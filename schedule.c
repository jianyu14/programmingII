#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#pragma warning (disable:4996)


void tSchedulingStaffMenu();
/*Staff

trainID = TRN001
drivingMode = manual / auto
scheduleNo = S0001
duration in minutes

*/



typedef struct {
	char trainID[7];
	int trainCoach, trainCapacity;
	char drivingMode[7];
}TrainInfo;

typedef struct {
	char mealName[7], mainFood[100], drinks[100], snacks[100];
	double mealPrice;
}Meal;

typedef struct {
	int day, month, year;
}Date;

typedef struct {
	int hours, minutes;
}Time;

typedef struct {
	char staffID[8], staffName[100];
}Staff;

typedef struct {
	char driverID[7], driverName[100];
}Driver;

typedef struct {
	char scheduleNo[6], trainID[7], departureStation[100], arrivalStation[100];
	Date departureDate;
	Time departureTime;
	Date arrivalDate;
	Time arrivalTime;
	int duration;
	Meal mealList[3];
	Staff staff[10];
	Driver driver[2];
	double schTrnPrice;
	char status[100];
}TrainSchedule;

typedef struct {
	char seatNo[4], status;
}Seat;

typedef struct {
	char schNo[6];
	Seat seat[120];
}SeatDisplay;

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
}Staffs;



int chkScheduleFormat(char scheduleNo[]);
int chkTrainIdFormat(char trainID[]);
int chkDriverIdFormat(char driverID[]);
int chkDrivingMode(char drvMode[]);
int chkInvalid(int rtr);

// Function to calculate the number of days in a month
int daysInMonth(int month, int year);
// Function to calculate the difference in days between two dates
int dateDifference(Date d1, Date d2);
// Function to calculate duration in minutes
int calDuration(TrainSchedule trnSch);

void addFunction();
void addNewTrain();
void addNewMealList();
void addTrainSchedule();

//Staff Search Function
void staffSearchTrain();
void staffSearchTrainInfo();
void staffSearchTrainID();
void staffSearchTrainSchedule();
void staffSearchDptDate();
void staffSearchArrDate();
void staffSearchDptStation();
void staffSearchArrStation();
void staffSearchScheduleNo();
void staffSearchTrainInfoByTrnID();
void staffSearchTrainInfoByDrvMode();
void staffSearchScheduleStatus();

//Modify Functions
TrainSchedule changeTrainID(TrainSchedule* trainID);
TrainSchedule changeDateTime(TrainSchedule* dateTime);
TrainSchedule changeMealList(TrainSchedule* mealList);
TrainSchedule changeStaff(TrainSchedule* staff);
TrainSchedule changeDriver(TrainSchedule* driver);
TrainSchedule addDriver(TrainSchedule* driver);
TrainSchedule changeStatus(TrainSchedule* status);

//Display Function for Staff
void staffDisplaySeatList();
void staffDisplayMealList();
void staffDisplayTrainList();
void staffDisplayStaffList();
void staffDisplayDriverList();
void tSchedulingStaffDisplay();

//Modify Train Schedule
void modifyTrainSchedule();

//Delete function
void deleteTrainSchedule();
void tSchedulingDelete();

//Generate report
void tSchedulingReport();
void delayedReport();


//User

void tSchedulingUserMenu();

//User Search Function
void userSearchTrain();
void userSearchTrainInfo();
void userSearchTrainID();
void userSearchTrainSchedule();
void userSearchDptDate();
void userSearchArrDate();
void userSearchDptStation();
void userSearchArrStation();
void userSearchScheduleNo();
void userSearchTrainInfoByTrnID();
void userSearchTrainInfoByDrvMode();
void userSearchScheduleStatus();


//Display Function for User
void userDisplaySeatList();
void userDisplayMealList();
void userDisplayTrainList();
void tSchedulingUserDisplay();


//Staff Menu
void tSchedulingStaffMenu() {
	int chooseFunction;

	Staffs staffL[1000];
	int countStaff = 0;
	FILE* staffInfo = fopen("staff1.bin", "rb");
	if (!staffInfo) {
		printf("Error: Cannot open staff1.bin!!\n");
		exit(-1);
	}
	else {
		while (fread(&staffL[countStaff], sizeof(Staff), 1, staffInfo) != EOF) {
			FILE* staffTxt = fopen("staffList.txt", "w");
			if (!staffTxt) {
				printf("Error: Cannot open staffList.txt!!\n");
				exit(-1);
			}
			else {
				fprintf(staffTxt, "%s|%s\n", staffL[countStaff].ID, staffL[countStaff].name);
				countStaff++;
			}
			fclose(staffTxt);
		}
		fclose(staffInfo);
		

	}

	do {
		printf("Staff - Train Scheduling\n\n");
		printf("1. Add\n");
		printf("2. Search\n");
		printf("3. Modify\n");
		printf("4. Display\n");
		printf("5. Delete\n");
		printf("6. Report\n");
		printf("7. Exit\n\n");
		printf("Choose a function to continue: ");
		scanf("%d", &chooseFunction);

		switch (chooseFunction) {
		case 1:
			system("cls");
			addFunction();
			break;
		case 2:
			system("cls");
			staffSearchTrain();
			break;
		case 3:
			system("cls");
			modifyTrainSchedule();
			break;
		case 4:
			system("cls");
			tSchedulingStaffDisplay();
			break;
		case 5:
			system("cls");
			tSchedulingDelete();
			break;
		case 6:
			system("cls");
			tSchedulingReport();
			break;
		case 7:
			system("cls");
			main();
			break;
		default:
			chooseFunction = chkInvalid(chooseFunction);
		}
	} while (chooseFunction == -1);
}



//Display in add train schedule function
void displayMealList() {

	FILE* list = fopen("mealList.txt", "r");
	Meal mealList;

	if (!list) {
		printf("Error: Cannot open mealList.txt!!\n");
		exit(-1);
	}
	else {
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

		for (int i = 0; i < 3; i++) {
		}

		while (fscanf(list, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &mealList.mealName, &mealList.mainFood, &mealList.drinks, &mealList.snacks, &mealList.mealPrice) != EOF) {

			printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", mealList.mealName, mealList.mainFood, mealList.drinks, mealList.snacks, " ", mealList.mealPrice);

		}

		fclose(list);
	}
}

void displayTrainList() {
	FILE* train = fopen("newTrain.txt", "r");
	TrainInfo trnInfo;

	if (!train) {
		printf("Error: Cannot open newTrain.txt!!\n");
		exit(-1);
	}
	else {

		printf("%-19s  %-18s  %-21s  %-s\n", "==================", "=================", "====================", "================");
		printf("%-19s  %-18s  %-21s  %-s\n", "     TRAIN ID     ", "   TRAIN COACH   ", "   TRAIN CAPACITY   ", "  DRIVING MODE  ");
		printf("%-19s  %-18s  %-21s  %-s\n", "==================", "=================", "====================", "================");

		while (fscanf(train, "%[^|]|%d|%d|%[^\n]\n", &trnInfo.trainID, &trnInfo.trainCoach, &trnInfo.trainCapacity, &trnInfo.drivingMode) != EOF) {

			printf("%-19s  %-18d  %-21d  %-s\n", trnInfo.trainID, trnInfo.trainCoach, trnInfo.trainCapacity, trnInfo.drivingMode);

		}

		fclose(train);
	}

}

void displayStaffList() {

	FILE* stfList = fopen("staffList.txt", "r");
	Staff staff;

	if (!stfList) {
		printf("Error: Cannot open staffList.txt!!\n");
		exit(-1);
	}
	else {

		printf("\n%-25s  %-s\n", "========================", "====================");
		printf("%-25s  %-s\n", "        STAFF ID        ", "     STAFF NAME     ");
		printf("%-25s  %-s\n", "========================", "====================");

		while (fscanf(stfList, "%[^|]|%[^\n]\n", &staff.staffID, &staff.staffName) != EOF) {

			printf("%-25s  %-s\n", staff.staffID, staff.staffName);

		}

		fclose(stfList);
	}
}

void displayDriverList() {

	FILE* drvList = fopen("driverList.txt", "r");
	Driver driver;

	if (!drvList) {
		printf("Error: Cannot open driverList.txt!!\n");
		exit(-1);
	}
	else {

		printf("\n%-24s  %-s\n", "=======================", "=====================");
		printf("%-24s  %-s\n", "       DRIVER ID       ", "     DRIVER NAME     ");
		printf("%-24s  %-s\n", "=======================", "=====================");

		while (fscanf(drvList, "%[^|]|%[^\n]\n", &driver.driverID, &driver.driverName) != EOF) {

			printf("%-24s  %-s\n", driver.driverID, driver.driverName);

		}

		fclose(drvList);

	}
}

void displaySeatList() {
	int  index = 0;
	SeatDisplay seatTable;

	FILE* seat = fopen("seatList.txt", "r");
	if (!seat) {
		printf("Error: Cannot open seatList.txt!!\n");
		exit(-1);
	}
	else {
		while (fscanf(seat, "%[^\n]\n", seatTable.schNo) != EOF) {
			for (int y = 0; y < 120; y++) {
				fscanf(seat, "%[^|]|%c\n", &seatTable.seat[y].seatNo, &seatTable.seat[y].status);
			}
		}

		printf("********************************* Full Seat List **************************************\n\n");
		for (int t = 0; t < 40; t += 4) {
			for (int u = 0; u < 3; u++) {
				for (int v = 0; v < 4; v++) {

					if (seatTable.seat[index].status == 'A')
						printf("[%s]", seatTable.seat[index].seatNo);
					else
						printf("{%s}", seatTable.seat[index].seatNo);

					if (v == 1)
						printf("--");
					index++;
				}
				printf("\t\t");
				index += 36;
			}
			printf("\n");
			index = t + 4;
		}
		printf("\n***************************************************************************************\n\n");

		printf("[ ] = Available\t{ } = Booked\n");

		fclose(seat);
	}

}


//Display Functions for Staff
void staffDisplayMealList() {

	FILE* list = fopen("mealList.txt", "r");
	Meal mealList;
	char ans;

	if (!list) {
		printf("Error: Cannot open mealList.txt!!\n");
		exit(-1);
	}
	else {
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

		for (int i = 0; i < 3; i++) {
		}

		while (fscanf(list, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &mealList.mealName, &mealList.mainFood, &mealList.drinks, &mealList.snacks, &mealList.mealPrice) != EOF) {

			printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", mealList.mealName, mealList.mainFood, mealList.drinks, mealList.snacks, " ", mealList.mealPrice);

		}

		fclose(list);

		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page ): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingStaffDisplay();
		}
		else {
			tSchedulingStaffMenu();
		}
	}
}

void staffDisplayTrainList() {
	FILE* train = fopen("newTrain.txt", "r");
	TrainInfo trnInfo;
	char ans;

	if (!train) {
		printf("Error: Cannot open newTrain.txt!!\n");
		exit(-1);
	}
	else {

		printf("%-19s  %-18s  %-21s  %-s\n", "==================", "=================", "====================", "================");
		printf("%-19s  %-18s  %-21s  %-s\n", "     TRAIN ID     ", "   TRAIN COACH   ", "   TRAIN CAPACITY   ", "  DRIVING MODE  ");
		printf("%-19s  %-18s  %-21s  %-s\n", "==================", "=================", "====================", "================");

		while (fscanf(train, "%[^|]|%d|%d|%[^\n]\n", &trnInfo.trainID, &trnInfo.trainCoach, &trnInfo.trainCapacity, &trnInfo.drivingMode) != EOF) {

			printf("%-19s  %-18d  %-21d  %-s\n", trnInfo.trainID, trnInfo.trainCoach, trnInfo.trainCapacity, trnInfo.drivingMode);

		}

		fclose(train);

		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page ): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingStaffDisplay();
		}
		else {
			tSchedulingStaffMenu();
		}
	}

}

void staffDisplayStaffList() {

	FILE* stfList = fopen("staffList.txt", "r");
	Staff staff;
	char ans;

	if (!stfList) {
		printf("Error: Cannot open staffList.txt!!\n");
		exit(-1);
	}
	else {

		printf("\n%-25s  %-s\n", "========================", "====================");
		printf("%-25s  %-s\n", "        STAFF ID        ", "     STAFF NAME     ");
		printf("%-25s  %-s\n", "========================", "====================");

		while (fscanf(stfList, "%[^|]|%[^\n]\n", &staff.staffID, &staff.staffName) != EOF) {

			printf("%-25s  %-s\n", staff.staffID, staff.staffName);

		}

		fclose(stfList);

		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page ): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingStaffDisplay();
		}
		else {
			tSchedulingStaffMenu();
		}
	}
}

void staffDisplayDriverList() {

	FILE* drvList = fopen("driverList.txt", "r");
	Driver driver;
	char ans;

	if (!drvList) {
		printf("Error: Cannot open driverList.txt!!\n");
		exit(-1);
	}
	else {

		printf("\n%-24s  %-s\n", "=======================", "=====================");
		printf("%-24s  %-s\n", "       DRIVER ID       ", "     DRIVER NAME     ");
		printf("%-24s  %-s\n", "=======================", "=====================");

		while (fscanf(drvList, "%[^|]|%[^\n]\n", &driver.driverID, &driver.driverName) != EOF) {

			printf("%-24s  %-s\n", driver.driverID, driver.driverName);

		}

		fclose(drvList);

		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page ): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingStaffDisplay();
		}
		else {
			tSchedulingStaffMenu();
		}

	}
}

void staffDisplaySeatList() {

	int  index = 0, frmt;
	char ans, inp[6];
	SeatDisplay seatTable;

	FILE* seat = fopen("seatList.txt", "r");
	if (!seat) {
		printf("Error: Cannot open seatList.txt!!\n");
		exit(-1);
	}
	else {
		do {
			frmt = 0;
			printf("Which train schedule's seat list you want to display?\n");
			printf("Enter the Schedule No: ");
			rewind(stdin);
			scanf("%s", &inp);
			lowerToUpper(inp, funcArrayLength(inp));
			frmt = chkScheduleFormat(inp);

			if (frmt != 1) {
				frmt = chkInvalid(frmt);
			}
		} while (frmt == -1);

		system("cls");
		fseek(seat, SEEK_SET, 0);
		while (fscanf(seat, "%[^\n]\n", &seatTable.schNo) != EOF) {
			for (int y = 0; y < 120; y++) {
				if (y != 119)
					fscanf(seat, "%[^|]|%c\n", &seatTable.seat[y].seatNo, &seatTable.seat[y].status);
				else
					fscanf(seat, "%[^|]|%c\n", &seatTable.seat[y].seatNo, &seatTable.seat[y].status);
			}
			if (strcmp(inp, seatTable.schNo) == 0) {
				printf("********************************* Seat List for [ %s ]**************************************\n\n", seatTable.schNo);

				for (int t = 0; t < 40; t += 4) {
					for (int u = 0; u < 3; u++) {
						for (int v = 0; v < 4; v++) {

							if (seatTable.seat[index].status == 'A')
								printf("[%s]", seatTable.seat[index].seatNo);
							else
								printf("{%s}", seatTable.seat[index].seatNo);

							if (v == 1)
								printf("--");
							index++;
						}
						printf("\t\t");
						index += 36;
					}
					printf("\n");
					index = t + 4;
				}
				printf("\n**********************************************************************************************\n\n");

				printf("[ ] = Available\t{ } = Booked\n");
			}

		}



		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page ): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingStaffDisplay();
		}
		else {
			tSchedulingStaffMenu();
		}

		fclose(seat);
	}
}

//Add Functions
void addFunction() {
	int addChoice;

	system("cls");
	do {
		printf("*********************************\n");
		printf("%10s%s\n", "", "Add Function");
		printf("*********************************\n");
		printf("1. Add New Train Information\n");
		printf("2. Add Train Schedule Information\n");
		printf("3. Add New Meal List\n");
		printf("4. Exit to Staff Menu page\n\n");
		printf("Choice: ");
		scanf("%d", &addChoice);

		switch (addChoice) {
		case 1:
			system("cls");
			addNewTrain();
			break;
		case 2:
			system("cls");
			addTrainSchedule();
			break;
		case 3:
			system("cls");
			addNewMealList();
			break;
		case 4:
			system("cls");
			tSchedulingStaffMenu();
			break;
		default:
			addChoice = chkInvalid(addChoice);
		}
	} while (addChoice == -1);
}

void addNewTrain() {
	TrainInfo info;
	char trainID[7], ans;

	FILE* newTrain = fopen("newTrain.txt", "r");


	if (!newTrain) {
		printf("Error: Cannot open newTrain.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int count = 0;

			system("cls");
			fseek(newTrain, SEEK_SET, 0);

			//auto increment trainID
			while (fscanf(newTrain, "%[^|]|%d|%d|%[^\n]\n", &info.trainID, &info.trainCoach, &info.trainCapacity, &info.drivingMode) != EOF) {
				count++;
			}
			strcpy(trainID, info.trainID);
			sprintf(info.trainID, "TRN%03d", atoi(trainID + 3) + 1);

			printf("Enter [%s]'s coach: ", info.trainID);
			scanf("%d", &info.trainCoach);
			printf("Enter [%s]'s capacity: ", info.trainID);
			scanf("%d", &info.trainCapacity);
			printf("Enter [%s]'s driving mode ( Manual / Auto): ", info.trainID);
			rewind(stdin);
			scanf("%s", &info.drivingMode);
			lowerToUpper(info.drivingMode, funcArrayLength(info.drivingMode));

			FILE* writeInfo = fopen("newTrain.txt", "a");
			if (!writeInfo) {
				printf("Error: Cannot open newTrain.txt!!\n");
				exit(-1);
			}
			else {
				fprintf(writeInfo, "%s|%d|%d|%s\n", info.trainID, info.trainCoach, info.trainCapacity, info.drivingMode);
				printf("\n\nNew train information successfully added!!\n");
				fclose(writeInfo);
			}

			printf("\n\nDo you want to add more new train? ( Y = Yes ): ");
			rewind(stdin);
			scanf("%c", &ans);


			if (toupper(ans) != 'Y') {
				addFunction();
			}

		} while (toupper(ans) == 'Y');

		fclose(newTrain);
	}
}

void addNewMealList() {
	Meal mealList;

	int mealNo = 64, i = 0;
	char ques, ans, see;
	char mealName[7];

	do {
		do {
			see = 0;
			printf("\nDo you want to see previous meal list? ( Y = Yes / N = No ): ");
			rewind(stdin);
			scanf("%c", &ques);

			ques = toupper(ques);

			if (ques == 'Y') {

				system("cls");
				displayMealList();
			}
			else if (ques != 'N' && ques != 'Y') {
				see = chkInvalid(see);
			}
			else {
				system("cls");
			}

		} while (see == -1);


		FILE* mList = fopen("mealList.txt", "r");

		if (!mList) {
			printf("Error: Cannot open mealList.txt!!\n\n");
			exit(-1);
		}

		while (fscanf(mList, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &mealList.mealName, &mealList.mainFood, &mealList.drinks, &mealList.snacks, &mealList.mealPrice) != EOF) {
			mealNo++;
			i++;
		}

		fclose(mList);

		FILE* addMList = fopen("mealList.txt", "a");
		strcpy(mealName, mealList.mealName);
		sprintf(mealList.mealName, "MEAL %c", mealName[5] + 1);
		printf("\nEnter Main Food for %s: ", mealList.mealName);
		rewind(stdin);
		scanf("%[^\n]", &mealList.mainFood);
		lowerToUpper(mealList.mainFood, funcArrayLength(mealList.mainFood));
		printf("Enter Drinks for Meal %c: ", mealList.mealName);
		rewind(stdin);
		scanf("%[^\n]", &mealList.drinks);
		lowerToUpper(mealList.drinks, funcArrayLength(mealList.drinks));
		printf("Enter Snacks for Meal %c: ", mealList.mealName);
		rewind(stdin);
		scanf("%[^\n]", &mealList.snacks);
		lowerToUpper(mealList.snacks, funcArrayLength(mealList.snacks));
		printf("Enter Price for Meal %c: ", mealList.mealName);
		scanf("%lf", &mealList.mealPrice);

		fprintf(addMList, "MEAL %c|%s|%s|%s|%.2f\n", mealList.mealName, mealList.mainFood, mealList.drinks, mealList.snacks, mealList.mealPrice);
		printf("\n\nNew meal list successfully added!!\n");
		fclose(addMList);

		printf("Do you want to add more new meal list? ( Y = Yes ): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) != 'Y') {
			addFunction();
		}

	} while (toupper(ans) == 'Y');
}

void addTrainSchedule() {
	TrainSchedule schedule, newSch;
	TrainInfo drvMode;
	int count, frmtTrnID, frmtDrvID;
	char schNo[6], again;

	FILE* getTrnSch = fopen("trainSchedule.txt", "r");

	if (!getTrnSch) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
			count = 0;
			while (fscanf(getTrnSch, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&schedule.scheduleNo, &schedule.trainID,
				&schedule.departureStation, &schedule.arrivalStation,
				&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year, &schedule.departureTime.hours, &schedule.departureTime.minutes,
				&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes,
				&schedule.duration,
				&schedule.mealList[0].mealName, &schedule.mealList[0].mainFood, &schedule.mealList[0].drinks, &schedule.mealList[0].snacks, &schedule.mealList[0].mealPrice,
				&schedule.mealList[1].mealName, &schedule.mealList[1].mainFood, &schedule.mealList[1].drinks, &schedule.mealList[1].snacks, &schedule.mealList[1].mealPrice,
				&schedule.mealList[2].mealName, &schedule.mealList[2].mainFood, &schedule.mealList[2].drinks, &schedule.mealList[2].snacks, &schedule.mealList[2].mealPrice,
				&schedule.staff[0].staffID, &schedule.staff[0].staffName,
				&schedule.staff[1].staffID, &schedule.staff[1].staffName,
				&schedule.staff[2].staffID, &schedule.staff[2].staffName,
				&schedule.staff[3].staffID, &schedule.staff[3].staffName,
				&schedule.staff[4].staffID, &schedule.staff[4].staffName,
				&schedule.staff[5].staffID, &schedule.staff[5].staffName,
				&schedule.staff[6].staffID, &schedule.staff[6].staffName,
				&schedule.staff[7].staffID, &schedule.staff[7].staffName,
				&schedule.staff[8].staffID, &schedule.staff[8].staffName,
				&schedule.staff[9].staffID, &schedule.staff[9].staffName,
				&schedule.driver[0].driverID, &schedule.driver[0].driverName,
				&schedule.driver[1].driverID, &schedule.driver[1].driverName,
				&schedule.schTrnPrice,
				&schedule.status) != EOF) {
				count++;
			}

			do {
				sprintf(newSch.scheduleNo, "S%04d", atoi(schedule.scheduleNo + 1) + 1);
				displayTrainList();
				printf("\nEnter Train ID for [ %s ]: ", newSch.scheduleNo);
				rewind(stdin);
				scanf("%s", &newSch.trainID);
				lowerToUpper(newSch.trainID, funcArrayLength(newSch.trainID));

				frmtTrnID = chkTrainIdFormat(newSch.trainID);

				if (frmtTrnID != 1) {
					frmtTrnID = chkInvalid(frmtTrnID);
				}
			} while (frmtTrnID == -1);

			//if driving mode is auto, drivers will NULL, otherwise, have to enter 2 drivers
			FILE* getDrvMode = fopen("newTrain.txt", "r");
			if (!getDrvMode) {
				printf("\nError: Cannot open newTrain.txt!!\n");
				exit(-1);
			}
			else {
				system("cls");
				while (fscanf(getDrvMode, "%[^|]|%d|%d|%[^\n]\n", &drvMode.trainID, &drvMode.trainCoach, &drvMode.trainCapacity, &drvMode.drivingMode) != EOF) {
					if (strcmp(newSch.trainID, drvMode.trainID) == 0) {
						if (strcmp(drvMode.drivingMode, "AUTO") == 0) {
							for (int i = 0; i < 2; i++) {
								strcpy(newSch.driver[i].driverID, "NULL");
								strcpy(newSch.driver[i].driverName, "NULL");
							}
						}
						else {
							system("cls");
							displayDriverList();
							for (int j = 0; j < 2; j++) {
								do {
									frmtDrvID = 0;
									printf("\nEnter Driver [%d]' ID: ", j + 1);
									rewind(stdin);
									scanf("%s", &newSch.driver[j].driverID);
									lowerToUpper(newSch.driver[j].driverID, funcArrayLength(newSch.driver[j].driverID));

									//chk driver ID format
									frmtDrvID = chkDriverIdFormat(newSch.driver[j].driverID);

									if (frmtDrvID != 1) {
										frmtDrvID = chkInvalid(frmtDrvID);
									}
									else {
										FILE* getDrvName = fopen("driverList.txt", "r");
										Driver drvName;

										if (!getDrvName) {
											printf("Error: Cannot open driverList.txt!!\n");
											exit(-1);
										}
										else {
											while (fscanf(getDrvName, "%[^|]|%[^\n]\n", &drvName.driverID, &drvName.driverName) != EOF) {
												if (strcmp(newSch.driver[j].driverID, drvName.driverID) == 0) {
													strcpy(newSch.driver[j].driverName, drvName.driverName);
												}
												//printf("%s %s\n", newSch.driver[j].driverID, newSch.driver[j].driverName);

											}

										}
										fclose(getDrvName);
									}
								} while (frmtDrvID == -1);
							}
						}
					}
				}

			}
			fclose(getDrvMode);
			fclose(getTrnSch);

			system("cls");

			//Enter departure info
			printf("\nEnter Departure Station for [ %s ]: ", newSch.scheduleNo);
			rewind(stdin);
			scanf("%[^\n]", &newSch.departureStation);
			lowerToUpper(newSch.departureStation, funcArrayLength(newSch.departureStation));

			printf("\nEnter Departure Date and Time for [ %s ] in ( DD/MM/YYYY HH:MM ): ", newSch.scheduleNo);
			scanf("%d/%d/%d %d:%d", &newSch.departureDate.day, &newSch.departureDate.month, &newSch.departureDate.year, &newSch.departureTime.hours, &newSch.departureTime.minutes);

			//Enter arrival info
			printf("\n\nEnter Arrival Station for [ %s ]: ", newSch.scheduleNo);
			rewind(stdin);
			scanf("%[^\n]", &newSch.arrivalStation);
			lowerToUpper(newSch.arrivalStation, funcArrayLength(newSch.arrivalStation));


			printf("\nEnter Arrival Date and Time for [ %s ] in ( DD/MM/YYYY HH:MM ): ", newSch.scheduleNo);
			scanf("%d/%d/%d %d:%d", &newSch.arrivalDate.day, &newSch.arrivalDate.month, &newSch.arrivalDate.year, &newSch.arrivalTime.hours, &newSch.arrivalTime.minutes);

			newSch.duration = calDuration(newSch);

			//Enter Meal list info
			system("cls");

			displayMealList();

			for (int i = 0; i < 3; i++) {
				printf("\nEnter Meal [%d] for [ %s ] with meal name: ", i + 1, newSch.scheduleNo);
				rewind(stdin);
				scanf("%[^\n]", &newSch.mealList[i].mealName);
				lowerToUpper(newSch.mealList[i].mealName, funcArrayLength(newSch.mealList[i].mealName));

				FILE* getMeal = fopen("mealList.txt", "r");
				Meal mList;
				if (!getMeal) {
					printf("Error: Cannot open mealList.txt!!\n");
					exit(-1);
				}
				else {
					fseek(getMeal, SEEK_SET, 0);
					while (fscanf(getMeal, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &mList.mealName, &mList.mainFood, &mList.drinks, &mList.snacks, &mList.mealPrice) != EOF) {
						if (strcmp(mList.mealName, newSch.mealList[i].mealName) == 0) {
							strcpy(newSch.mealList[i].mainFood, mList.mainFood);
							strcpy(newSch.mealList[i].drinks, mList.drinks);
							strcpy(newSch.mealList[i].snacks, mList.snacks);
							newSch.mealList[i].mealPrice = mList.mealPrice;
						}
					}
				}
				fclose(getMeal);
			}

			//Enter staff list info
			system("cls");

			displayStaffList();

			for (int i = 0; i < 10; i++) {
				printf("\nEnter Staff [%d] for [ %s ] with Staff ID: ", i + 1, newSch.scheduleNo);
				rewind(stdin);
				scanf("%s", &newSch.staff[i].staffID);
				lowerToUpper(newSch.staff[i].staffID, funcArrayLength(newSch.staff[i].staffID));

				FILE* getStaffID = fopen("staffList.txt", "r");
				Staff staff;
				if (!getStaffID) {
					printf("\nError: Cannot open staffList.txt!!\n");
					exit(-1);
				}
				else {
					fseek(getStaffID, SEEK_SET, 0);
					while (fscanf(getStaffID, "%[^|]|%[^\n]\n", &staff.staffID, &staff.staffName) != EOF) {
						if (strcmp(newSch.staff[i].staffID, staff.staffID) == 0) {
							strcpy(newSch.staff[i].staffName, staff.staffName);
						}
					}
					fclose(getStaffID);
				}
			}

			//Enter Price

			system("cls");

			printf("Enter Price for [ %s ]: ", newSch.scheduleNo);
			scanf("%lf", &newSch.schTrnPrice);

			//Status will be PREPARING
			strcpy(newSch.status, "PREPARING");

			FILE* addSch = fopen("trainSchedule.txt", "a");
			if (!addSch) {
				printf("Error: Cannot open trainSchedule.txt!!\n");
				exit(-1);
			}
			else {
				FILE* seatL = fopen("seatList.txt", "a");
				if (!seatL) {
					printf("Error: Cannot open seatList.txt!!\n");
					exit(-1);
				}
				fprintf(seatL, "\n\n%s\n", newSch.scheduleNo);
				for (int d = 0; d < 40; d++) {
					fprintf(seatL, "A%02d|A\n", d + 1);
				}
				for (int d = 0; d < 40; d++) {
					fprintf(seatL, "B%02d|A\n", d + 1);
				}
				for (int d = 0; d < 40; d++) {
					fprintf(seatL, "C%02d|A\n", d + 1);
				}
				fclose(seatL);
				fprintf(addSch, "%s|%s\n%s|%s\n%02d/%02d/%04d|%02d:%02d\n%02d/%02d/%04d|%02d:%02d\n%d\n%s|%s|%s|%s|%.2f\n%s|%s|%s|%s|%.2f\n%s|%s|%s|%s|%.2f\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%.2f\n%s\n\n",
					newSch.scheduleNo, newSch.trainID,
					newSch.departureStation, newSch.arrivalStation,
					newSch.departureDate.day, newSch.departureDate.month, newSch.departureDate.year, newSch.departureTime.hours, newSch.departureTime.minutes,
					newSch.arrivalDate.day, newSch.arrivalDate.month, newSch.arrivalDate.year, newSch.arrivalTime.hours, newSch.arrivalTime.minutes,
					newSch.duration,
					newSch.mealList[0].mealName, newSch.mealList[0].mainFood, newSch.mealList[0].drinks, newSch.mealList[0].snacks, newSch.mealList[0].mealPrice,
					newSch.mealList[1].mealName, newSch.mealList[1].mainFood, newSch.mealList[1].drinks, newSch.mealList[1].snacks, newSch.mealList[1].mealPrice,
					newSch.mealList[2].mealName, newSch.mealList[2].mainFood, newSch.mealList[2].drinks, newSch.mealList[2].snacks, newSch.mealList[2].mealPrice,
					newSch.staff[0].staffID, newSch.staff[0].staffName,
					newSch.staff[1].staffID, newSch.staff[1].staffName,
					newSch.staff[2].staffID, newSch.staff[2].staffName,
					newSch.staff[3].staffID, newSch.staff[3].staffName,
					newSch.staff[4].staffID, newSch.staff[4].staffName,
					newSch.staff[5].staffID, newSch.staff[5].staffName,
					newSch.staff[6].staffID, newSch.staff[6].staffName,
					newSch.staff[7].staffID, newSch.staff[7].staffName,
					newSch.staff[8].staffID, newSch.staff[8].staffName,
					newSch.staff[9].staffID, newSch.staff[9].staffName,
					newSch.driver[0].driverID, newSch.driver[0].driverName,
					newSch.driver[1].driverID, newSch.driver[1].driverName,
					newSch.schTrnPrice,
					newSch.status);
					
				printf("New Train Schedule Information has successfully added!!\n\n");
				fclose(addSch);
			}

			printf("Do you want to add more new train schedule information? ( Y = Yes ): ");
			rewind(stdin);
			scanf("%c", &again);

			if (toupper(again) == 'Y') {
				system("cls");
				addTrainSchedule();
			}
			else {
				system("cls");
				addFunction();
			}
	}

}

//Staff Search Functions
void staffSearchTrain() {
	int opt;
	do {
		printf("What you want to search for?\n");
		printf("1. Train Information\n");
		printf("2. Train Schedule Information\n");
		printf("3. Exit to previous page\n");
		printf("\nChoice: ");
		scanf("%d", &opt);

		if (opt == 1) {
			system("cls");
			staffSearchTrainInfo();
		}
		else if (opt == 2) {
			system("cls");
			staffSearchTrainSchedule();
		}
		else if (opt == 3) {
			system("cls");
			tSchedulingStaffMenu();
		}
		else {
			opt = chkInvalid(opt);
		}

	} while (opt == -1);
}

void staffSearchTrainInfo() {
	int opt;
	do {
		printf("Which way you want to search by?\n");
		printf("1. Train ID\n");
		printf("2. Train Driving Mode\n");
		printf("3. Exit to previous page\n");
		printf("\nChoice: ");
		scanf("%d", &opt);

		if (opt == 1) {
			system("cls");
			staffSearchTrainInfoByTrnID();
		}
		else if (opt == 2) {
			system("cls");
			staffSearchTrainInfoByDrvMode();
		}
		else if (opt == 3) {
			system("cls");
			staffSearchTrain();
		}
		else {
			opt = chkInvalid(opt);
		}

	} while (opt == -1);
}

void staffSearchTrainInfoByTrnID() {
	char trainID[7];
	TrainInfo info;
	char ans;

	FILE* trnInfo = fopen("newTrain.txt", "r");
	if (!trnInfo) {
		printf("Error: Cannot open newTrain.txt!\n");
		exit(-1);
	}
	else {
		do {
			int frmt;
			int condt = 0;

			printf("--------------------------------------\n");
			printf("Search Train Information By [TRAIN ID]\n");
			printf("--------------------------------------\n\n");

			do {
				frmt = 1;


				printf("Enter Train ID: ");
				rewind(stdin);
				scanf("%[^\n]", &trainID);
				lowerToUpper(trainID, funcArrayLength(trainID));

				//check train id format
				frmt = chkTrainIdFormat(trainID);

				if (frmt == 0) {
					printf("Wrong train ID format!! Please enter again!\n\n");
				}
				else {
					fseek(trnInfo, SEEK_SET, 0);
					system("cls");
				}

			} while (frmt == 0);

			while (fscanf(trnInfo, "%[^|]|%d|%d|%[^\n]\n", &info.trainID, &info.trainCoach, &info.trainCapacity, &info.drivingMode) != EOF) {
				if (strcmp(info.trainID, trainID) == 0) {
					printf("\n-Here is the information for train [%s]-\n\n", info.trainID);
					printf("Train ID: %s\n", info.trainID);
					printf("Number of Train Coach: %d\n", info.trainCoach);
					printf("Train Capacity: %d\n", info.trainCapacity);
					printf("Train Driving Mode: %s\n\n", info.drivingMode);
					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train information for this train ID!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrain();
			}
		} while (toupper(ans) == 'Y');

		fclose(trnInfo);
	}

}

void staffSearchTrainInfoByDrvMode() {
	char drvMode[7];
	TrainInfo info;
	char ans;

	FILE* trnInfo = fopen("newTrain.txt", "r");
	if (!trnInfo) {
		printf("Error: Cannot open newTrain.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int frmt;

			printf("------------------------------------------------\n");
			printf("Search Train Information By [TRAIN DRIVING MODE]\n");
			printf("------------------------------------------------\n\n");

			do {
				frmt = 1;

				printf("Enter Train Driving Mode ( MANUAL / AUTO): ");
				rewind(stdin);
				scanf("%s", &drvMode);
				lowerToUpper(drvMode, funcArrayLength(drvMode));

				//check input is manual or auto or else
				frmt = chkDrivingMode(drvMode);

				if (frmt == 0) {
					printf("Wrong input for Driving Mode!! Please enter again!\n\n");
				}
				else {
					system("cls");
				}

			} while (frmt == 0);
			fseek(trnInfo, SEEK_SET, 0);

			while (fscanf(trnInfo, "%[^|]|%d|%d|%[^\n]\n", &info.trainID, &info.trainCoach, &info.trainCapacity, &info.drivingMode) != EOF) {
				if (strcmp(info.drivingMode, drvMode) == 0) {
					printf("\n-Here is the information for train [%s]-\n\n", info.trainID);
					printf("Train ID: %s\n", info.trainID);
					printf("Number of Train Coach: %d\n", info.trainCoach);
					printf("Train Capacity: %d\n", info.trainCapacity);
					printf("Train Driving Mode: %s\n\n", info.drivingMode);
				}
			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrain();
			}
		} while (toupper(ans) == 'Y');

		fclose(trnInfo);
	}

}

void staffSearchTrainID() {
	char trainID[7];
	TrainSchedule trnSch;
	char ans;

	FILE* trnID = fopen("trainSchedule.txt", "r");
	if (!trnID) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int frmt;
			int condt = 0;
			do {
				frmt = 1;

				printf("Enter train ID: ");
				rewind(stdin);
				scanf("%s", &trainID);
				lowerToUpper(trainID, funcArrayLength(trainID));

				//check train ID format
				frmt = chkTrainIdFormat(trainID);

				if (frmt == 0) {
					printf("Wrong train ID format!! Please enter again!\n\n");
				}
				else {
					fseek(trnID, SEEK_SET, 0);
					system("cls");
				}
			} while (frmt == 0);
			while (fscanf(trnID, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(trainID, trnSch.trainID) == 0) {
					printf("Schedule No: %s\n\n", trnSch.scheduleNo);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch.staff[j].staffID, trnSch.staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch.driver[k].driverID, trnSch.driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this train ID!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');


		fclose(trnID);
	}
}

void staffSearchDptDate() {
	int day, month, year;
	TrainSchedule trnSch;
	char ans;

	FILE* date = fopen("trainSchedule.txt", "r");
	if (!date) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(date, SEEK_SET, 0);
			printf("Enter Departure Date in format (DD/MM/YYY): ");
			scanf("%d/%d/%d", &day, &month, &year);

			system("cls");

			while (fscanf(date, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if ((day == trnSch.departureDate.day) && (month == trnSch.departureDate.month) && (year == trnSch.departureDate.year)) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch.staff[j].staffID, trnSch.staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch.driver[k].driverID, trnSch.driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this departure date!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(date);

	}


}

void staffSearchArrDate() {
	int day, month, year;
	TrainSchedule trnSch;
	char ans;

	FILE* date = fopen("trainSchedule.txt", "r");
	if (!date) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(date, SEEK_SET, 0);
			printf("Enter Arrival Date in format (DD/MM/YYY): ");
			scanf("%d/%d/%d", &day, &month, &year);

			system("cls");

			while (fscanf(date, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if ((day == trnSch.arrivalDate.day) && (month == trnSch.arrivalDate.month) && (year == trnSch.arrivalDate.year)) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch.staff[j].staffID, trnSch.staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch.driver[k].driverID, trnSch.driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this arrival date!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(date);

	}
}

void staffSearchDptStation() {

	char dptStation[100];
	TrainSchedule trnSch;
	char ans;

	FILE* station = fopen("trainSchedule.txt", "r");
	if (!station) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(station, SEEK_SET, 0);
			printf("Enter Departure Station: ");
			rewind(stdin);
			scanf("%[^\n]", &dptStation);
			lowerToUpper(dptStation, funcArrayLength(dptStation));
			system("cls");

			while (fscanf(station, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(dptStation, trnSch.departureStation) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch.staff[j].staffID, trnSch.staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch.driver[k].driverID, trnSch.driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this departure station!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(station);

	}

}

void staffSearchArrStation() {

	char arrStation[100];
	TrainSchedule trnSch;
	char ans;

	FILE* station = fopen("trainSchedule.txt", "r");
	if (!station) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(station, SEEK_SET, 0);
			printf("Enter Arrival Station: ");
			rewind(stdin);
			scanf("%[^\n]", &arrStation);
			lowerToUpper(arrStation, funcArrayLength(arrStation));
			system("cls");

			while (fscanf(station, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(arrStation, trnSch.arrivalStation) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch.staff[j].staffID, trnSch.staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch.driver[k].driverID, trnSch.driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this arrival station!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(station);

	}
}

void staffSearchScheduleNo() {

	char schNo[6];
	TrainSchedule trnSch;
	char ans;

	FILE* scheduleNo = fopen("trainSchedule.txt", "r");
	if (!scheduleNo) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;
			int frmt;

			do {
				frmt = 1;

				printf("Enter Schedule No: ");
				rewind(stdin);
				scanf("%[^\n]", &schNo);

				//check Schedule no format
				lowerToUpper(schNo, funcArrayLength(schNo));
				frmt = chkScheduleFormat(schNo);
				if (frmt == 0) {
					printf("Wrong schedule no format!! Please enter again!\n\n");
				}
				else {
					fseek(scheduleNo, SEEK_SET, 0);
					system("cls");
				}
			} while (frmt == 0);

			while (fscanf(scheduleNo, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(schNo, trnSch.scheduleNo) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch.staff[j].staffID, trnSch.staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch.driver[k].driverID, trnSch.driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this schedule no!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(scheduleNo);

	}
}

void staffSearchScheduleStatus() {

	char status[100];
	TrainSchedule trnSch;
	char ans;

	FILE* schStatus = fopen("trainSchedule.txt", "r");
	if (!schStatus) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;
			int inp;

			do {
				inp = 1;
				printf("Enter Status ( COMPLETED / PREPARING / DELAYED ): ");
				rewind(stdin);
				scanf("%s", &status);

				lowerToUpper(status, funcArrayLength(status));

				if (strcmp(status, "COMPLETED") == 0 || strcmp(status, "PREPARING") == 0 || strcmp(status, "DELAYED") == 0) {
					inp = 0;
					fseek(schStatus, SEEK_SET, 0);
					system("cls");
				}
				else {
					printf("Invalid Input! Please Enter Again!\n");
				}

			} while (inp != 0);

			while (fscanf(schStatus, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(status, trnSch.status) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch.staff[j].staffID, trnSch.staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch.driver[k].driverID, trnSch.driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this schedule status!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				staffSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(schStatus);
	}
}

void staffSearchTrainSchedule() {
	int choice;

	do {
		system("cls");
		printf("Which way you want to search by?\n");
		printf("1. Train ID\n");
		printf("2. Departure Date\n");
		printf("3. Arrival Date\n");
		printf("4. Departure Station\n");
		printf("5. Arrival Station\n");
		printf("6. Schedule No\n");
		printf("7. Train Schedule Status\n");
		printf("8. Exit to previous page\n");
		printf("\nOption: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			staffSearchTrainID();
			break;
		case 2:
			system("cls");
			staffSearchDptDate();
			break;
		case 3:
			system("cls");
			staffSearchArrDate();
			break;
		case 4:
			system("cls");
			staffSearchDptStation();
			break;
		case 5:
			system("cls");
			staffSearchArrStation();
			break;
		case 6:
			system("cls");
			staffSearchScheduleNo();
			break;
		case 7:
			system("cls");
			staffSearchScheduleStatus();
			break;
		case 8:
			system("cls");
			tSchedulingStaffMenu();
			break;
		default:
			choice = chkInvalid(choice);
		}
	} while (choice == -1);
}


TrainSchedule changeTrainID(TrainSchedule* trainID) {
	char confirm, oldTrnID[7], newTrnID[7];
	int frmt;

	system("cls");

	do {
		printf("Current Train ID for [ %s ]: %s\n\n", trainID->scheduleNo, trainID->trainID);

		//Display whole train lists
		displayTrainList();

		printf("\nChange to which train?\n");
		printf("Enter the train ID: ");
		rewind(stdin);
		scanf("%s", &newTrnID);
		lowerToUpper(newTrnID, funcArrayLength(newTrnID));

		frmt = chkTrainIdFormat(newTrnID);

	} while (frmt != 1);

	strcpy(oldTrnID, trainID->trainID);

	printf("\nConfirmation Message:\n");
	printf("Are you sure want to change Train ID from [ %s ] to [ %s ]? ( Y = Yes ): ", oldTrnID, newTrnID);
	rewind(stdin);
	scanf("%c", &confirm);

	if (toupper(confirm) == 'Y') {
		strcpy(trainID->trainID, newTrnID);

		printf("\nTrain ID for %s has successfully changed!!\n\n", trainID->scheduleNo);
	}

	return *trainID;
}

TrainSchedule changeDateTime(TrainSchedule* dateTime) {
	char confirm;
	int choice;
	Date oldDate, newDate;
	Time oldTime, newTime;
	int oldDuration, newDuration;

	system("cls");

	do {

		printf("\nWhich Date and Time you are going to change?\n");
		printf("1. Departure Date and Time\n");
		printf("2. Arrival Date and Time\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			oldDate = dateTime->departureDate;
			oldTime = dateTime->departureTime;

			printf("\n\nEnter new departure date in format ( DD/MM/YYYY ): ");
			scanf("%d/%d/%d", &newDate.day, &newDate.month, &newDate.year);

			printf("\nEnter new departure time in ( HH:MM ): ");
			scanf("%d:%d", &newTime.hours, &newTime.minutes);

			printf("\nConfirmation Message:\n");
			printf("Are you sure want to change Departure Date and Time from [ %02d/%02d/%04d %02d:%02d ] to [ %02d/%02d/%04d %02d:%02d ]? ( Y = Yes ): ", oldDate.day, oldDate.month, oldDate.year, oldTime.hours, oldTime.minutes, newDate.day, newDate.month, newDate.year, newTime.hours, newTime.minutes);
			rewind(stdin);
			scanf("%c", &confirm);

			if (toupper(confirm) == 'Y') {
				dateTime->departureDate = newDate;
				dateTime->departureTime = newTime;

				printf("\nDeparture Date and Time for %s has successfully changed!!\n\n", dateTime->scheduleNo);

			}

			return *dateTime;

			break;
		case 2:
			system("cls");
			oldDate = dateTime->arrivalDate;
			oldTime = dateTime->arrivalTime;

			printf("\n\nEnter new arrival date in format ( DD/MM/YYYY ): ");
			scanf("%d/%d/%d", &newDate.day, &newDate.month, &newDate.year);

			printf("\nEnter new arrival time in ( HH:MM ): ");
			scanf("%d:%d", &newTime.hours, &newTime.minutes);

			printf("\nConfirmation Message:\n");
			printf("Are you sure want to change Arrival Date and Time from [ %02d/%02d/%04d %02d:%02d ] to [ %02d/%02d/%04d %02d:%02d ]? ( Y = Yes ): ", oldDate.day, oldDate.month, oldDate.year, oldTime.hours, oldTime.minutes, newDate.day, newDate.month, newDate.year, newTime.hours, newTime.minutes);
			rewind(stdin);
			scanf("%c", &confirm);

			if (toupper(confirm) == 'Y') {
				dateTime->arrivalDate = newDate;
				dateTime->arrivalTime = newTime;

				printf("\nArrival Date and Time for %s has successfully changed!!\n\n", dateTime->scheduleNo);

			}

			return *dateTime;

			break;
		default:
			choice = chkInvalid(choice);
		}
	} while (choice == -1);
}

TrainSchedule changeMealList(TrainSchedule* mealList) {
	char confirm, currentMeal[7], changedMeal[7];
	Meal oldMeal, newMeal;

	system("cls");
	//Display current meal list
	printf("---- Current Meal List ----\n\n");
	printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
	printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
	printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

	for (int i = 0; i < 3; i++) {

		printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", mealList->mealList[i].mealName, mealList->mealList[i].mainFood, mealList->mealList[i].drinks, mealList->mealList[i].snacks, " ", mealList->mealList[i].mealPrice);

	}

	//which meal to change
	printf("\n\nWhich meal you want to change?\n");
	printf("Enter the meal name: ");
	rewind(stdin);
	scanf("%[^\n]", &currentMeal);
	lowerToUpper(currentMeal, funcArrayLength(currentMeal));

	for (int j = 0; j < 3; j++) {
		if (strcmp(mealList->mealList[j].mealName, currentMeal) == 0) {
			oldMeal = mealList->mealList[j];

			//Display whole meal lists
			printf("\n---- Full Meal Lists ----\n");
			displayMealList();

			printf("\nChange to which meal?\n");
			printf("Enter the meal name:");
			rewind(stdin);
			scanf("%[^\n]", &changedMeal);
			lowerToUpper(changedMeal, funcArrayLength(changedMeal));

			FILE* mList = fopen("mealList.txt", "r");
			Meal findMeal;

			if (!mList) {
				printf("Error: Cannot open mealList.txt!!\n");
				exit(-1);
			}
			else {
				while (fscanf(mList, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &findMeal.mealName, &findMeal.mainFood, &findMeal.drinks, &findMeal.snacks, &findMeal.mealPrice) != EOF) {
					if (strcmp(findMeal.mealName, changedMeal) == 0) {

						printf("\nConfirmation message:\n");
						printf("Are you sure want to change one of the meals from [ %s ] to [ %s ]? ( Y = Yes ): ", oldMeal.mealName, findMeal.mealName);
						rewind(stdin);
						scanf("%c", &confirm);

						if (toupper(confirm) == 'Y') {
							newMeal = findMeal;
							mealList->mealList[j] = newMeal;
							printf("\nOne of the Meal List for %s has successfully changed!!\n\n", mealList->scheduleNo);

							return *mealList;
						}
					}
				}
			}
			fclose(mList);
		}

	}
}

TrainSchedule changeStaff(TrainSchedule* staff) {
	char confirm, currentStaffID[8], changedStaffID[8];
	Staff oldStaff, newStaff;

	system("cls");

	//Display current staff
	printf("---- Current Staff Lists----\n");
	printf("\n%-25s  %-s\n", "========================", "====================");
	printf("%-25s  %-s\n", "        STAFF ID        ", "     STAFF NAME     ");
	printf("%-25s  %-s\n", "========================", "====================");

	for (int i = 0; i < 10; i++) {

		printf("%-25s  %-s\n", staff->staff[i].staffID, staff->staff[i].staffName);

	}

	//which staff to change
	printf("\n\nWhich staff you want to change?\n");
	printf("Enter the Staff ID: ");
	rewind(stdin);
	scanf("%[^\n]", &currentStaffID);
	lowerToUpper(currentStaffID, funcArrayLength(currentStaffID));


	for (int j = 0; j < 10; j++) {
		if (strcmp(staff->staff[j].staffID, currentStaffID) == 0) {
			oldStaff = staff->staff[j];

			//Display whole staff lists
			printf("\n---- Full Staff Lists ----\n");
			displayStaffList();

			printf("\nChange to which Staff?\n");
			printf("Enter the Staff ID:");
			rewind(stdin);
			scanf("%s", &changedStaffID);
			lowerToUpper(changedStaffID, funcArrayLength(changedStaffID));

			FILE* stfList = fopen("staffList.txt", "r");
			Staff findStaff;

			if (!stfList) {
				printf("Error: Cannot open staffList.txt!!\n");
				exit(-1);
			}
			else {
				while (fscanf(stfList, "%[^|]|%[^\n]\n", &findStaff.staffID, &findStaff.staffName) != EOF) {
					if (strcmp(findStaff.staffID, changedStaffID) == 0) {

						printf("\nConfirmation message:\n");
						printf("Are you sure want to change one of the staff from [ %s ] to [ %s ]? ( Y = Yes ): ", oldStaff.staffID, findStaff.staffID);
						rewind(stdin);
						scanf("%c", &confirm);

						if (toupper(confirm) == 'Y') {
							newStaff = findStaff;
							staff->staff[j] = newStaff;
							printf("\nOne of the Staff for %s has successfully changed!!\n\n", staff->scheduleNo);

							return *staff;
						}
					}
				}
			}
			fclose(stfList);
		}

	}
}

TrainSchedule changeDriver(TrainSchedule* driver) {
	char confirm, currentDriverID[8], changedDriverID[8];
	Driver oldDriver, newDriver;
	int frmt;

	system("cls");

	//Display current driver
	printf("---- Current Driver Lists----\n");
	printf("\n%-24s  %-s\n", "=======================", "=====================");
	printf("%-24s  %-s\n", "       DRIVER ID       ", "     DRIVER NAME     ");
	printf("%-24s  %-s\n", "=======================", "=====================");

	for (int i = 0; i < 2; i++) {
		//(fscanf(drvList, "%[^|]|%[^\n]\n", &driver.driverID, &driver.driverName) != EOF) {

		printf("%-24s  %-s\n", driver->driver[i].driverID, driver->driver[i].driverName);

	}

	do {
		frmt = 0;
		//which driver to change
		printf("\n\nWhich driver you want to change?\n");
		printf("Enter the Driver ID: ");
		rewind(stdin);
		scanf("%[^\n]", &currentDriverID);
		lowerToUpper(currentDriverID, funcArrayLength(currentDriverID));
		//chk driverID format
		frmt = chkDriverIdFormat(currentDriverID);
	} while (frmt != 1);

	for (int j = 0; j < 2; j++) {
		if (strcmp(driver->driver[j].driverID, currentDriverID) == 0) {
			oldDriver = driver->driver[j];

			//Display whole driver lists
			printf("\n---- Full Driver Lists ----\n");
			displayDriverList();

			do {
				frmt = 0;
				printf("\nChange to which Driver?\n");
				printf("Enter the Driver ID:");
				rewind(stdin);
				scanf("%s", &changedDriverID);
				lowerToUpper(changedDriverID, funcArrayLength(changedDriverID));
				//chk driverID format
				frmt = chkDriverIdFormat(changedDriverID);
			} while (frmt != 1);

			FILE* drvList = fopen("driverList.txt", "r");
			Driver findDriver;

			if (!drvList) {
				printf("Error: Cannot open driverList.txt!!\n");
				exit(-1);
			}
			else {
				while (fscanf(drvList, "%[^|]|%[^\n]\n", &findDriver.driverID, &findDriver.driverName) != EOF) {
					if (strcmp(findDriver.driverID, changedDriverID) == 0) {

						printf("\nConfirmation message:\n");
						printf("Are you sure want to change one of the driver from [ %s ] to [ %s ]? ( Y = Yes ): ", oldDriver.driverID, findDriver.driverID);
						rewind(stdin);
						scanf("%c", &confirm);

						if (toupper(confirm) == 'Y') {
							newDriver = findDriver;
							driver->driver[j] = newDriver;
							printf("\nOne of the Driver for %s has successfully changed!!\n\n", driver->scheduleNo);

							return *driver;
						}
					}
				}
			}
			fclose(drvList);
		}

	}
}

TrainSchedule addDriver(TrainSchedule* driver) {
	Driver newDriver[2], chkDriver;
	int frmt;
	char confirm;

	FILE* drvList = fopen("driverList.txt", "r");
	if (!drvList) {
		printf("Error: Cannot open driverList.txt!!\n");
		exit(-1);
	}
	else {
		system("cls");
		//Display whole driver lists
		printf("\n---- Full Driver Lists ----\n");
		displayDriverList();

		printf("Please enter 2 drivers for [ %s ]:\n", driver->scheduleNo);
		for (int i = 0; i < 2; i++) {
			do {
				printf("\nDriver [%d] ID: ", i + 1);
				scanf("%s", &newDriver[i].driverID);
				lowerToUpper(newDriver[i].driverID, funcArrayLength(newDriver[i].driverID));
				frmt = chkDriverIdFormat(newDriver[i].driverID);
				if (frmt == 1) {
					printf("\nConfirmation Message:\n");
					printf("Are you sure want to add Driver [ %s ] to train schedule [ %s ]? ( Y = Yes ): ", newDriver[i].driverID, driver->scheduleNo);
					rewind(stdin);
					scanf("%c", &confirm);

					if (toupper(confirm) == 'Y') {
						fseek(drvList, SEEK_SET, 0);
						while (fscanf(drvList, "%[^|]|%[^\n]\n", &chkDriver.driverID, &chkDriver.driverName) != EOF) {
							if (strcmp(newDriver[i].driverID, chkDriver.driverID) == 0) {
								strcpy(newDriver[i].driverName, chkDriver.driverName);
								driver->driver[i] = newDriver[i];

								printf("\nDriver [ %s ] has successfully added to train schedule [ %s ]!!\n", newDriver[i].driverID, driver->scheduleNo);
							}
						}
					}
				}
			} while (frmt != 1);
		}

		fclose(drvList);
		return *driver;
	}
}

TrainSchedule changeStatus(TrainSchedule* status) {
	char confirm, oldStatus[100], newStatus[100];
	int inp;

	system("cls");

	do {
		inp = 0;
		printf("Current Status for [ %s ]: %s\n", status->scheduleNo, status->status);
		printf("\nEnter new Status ( COMPLETED / PREPARING / DELAYED ): ");
		rewind(stdin);
		scanf("%s", &newStatus);
		lowerToUpper(newStatus, funcArrayLength(newStatus));

		if (strcmp(newStatus, "COMPLETED") == 0 || strcmp(newStatus, "PREPARING") == 0 || strcmp(newStatus, "DELAYED") == 0) {
			inp = 0;
		}
		else {
			inp = chkInvalid(inp);
		}

	} while (inp == -1);

	strcpy(oldStatus, status->status);

	printf("\nConfirmation Message:\n");
	printf("Are you sure want to change Train Schedule Status from [ %s ] to [ %s ]? ( Y = Yes ): ", oldStatus, newStatus);
	rewind(stdin);
	scanf("%c", &confirm);

	if (toupper(confirm) == 'Y') {
		strcpy(status->status, newStatus);

		printf("\nTrain Schedule Status for %s has successfully changed!!\n\n", status->scheduleNo);
	}
	return *status;
}


void modifyTrainSchedule() {
	int x = 0, cond = 0, schIndex, choice;
	char schNo[6], ans, ans1;
	TrainSchedule schedule;

	system("cls");

	TrainSchedule* trnSch = (TrainSchedule*)malloc(1000 * sizeof(TrainSchedule));
	if (trnSch == NULL) {
		printf("Failed to allocate memory to schedule structure!\n");
	}

	do {
		printf("Enter the Train Schedule No that you want to change information: ");
		rewind(stdin);
		scanf("%s", &schNo);
		lowerToUpper(schNo, funcArrayLength(schNo));

		FILE* trainSch = fopen("trainSchedule.txt", "r");
		if (!trainSch) {
			printf("Error: Cannot open trainSchedule.txt!!\n");
			exit(-1);
		}
		else {

			while (fscanf(trainSch, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch[x].scheduleNo, &trnSch[x].trainID,
				&trnSch[x].departureStation, &trnSch[x].arrivalStation,
				&trnSch[x].departureDate.day, &trnSch[x].departureDate.month, &trnSch[x].departureDate.year, &trnSch[x].departureTime.hours, &trnSch[x].departureTime.minutes,
				&trnSch[x].arrivalDate.day, &trnSch[x].arrivalDate.month, &trnSch[x].arrivalDate.year, &trnSch[x].arrivalTime.hours, &trnSch[x].arrivalTime.minutes,
				&trnSch[x].duration,
				&trnSch[x].mealList[0].mealName, &trnSch[x].mealList[0].mainFood, &trnSch[x].mealList[0].drinks, &trnSch[x].mealList[0].snacks, &trnSch[x].mealList[0].mealPrice,
				&trnSch[x].mealList[1].mealName, &trnSch[x].mealList[1].mainFood, &trnSch[x].mealList[1].drinks, &trnSch[x].mealList[1].snacks, &trnSch[x].mealList[1].mealPrice,
				&trnSch[x].mealList[2].mealName, &trnSch[x].mealList[2].mainFood, &trnSch[x].mealList[2].drinks, &trnSch[x].mealList[2].snacks, &trnSch[x].mealList[2].mealPrice,
				&trnSch[x].staff[0].staffID, &trnSch[x].staff[0].staffName,
				&trnSch[x].staff[1].staffID, &trnSch[x].staff[1].staffName,
				&trnSch[x].staff[2].staffID, &trnSch[x].staff[2].staffName,
				&trnSch[x].staff[3].staffID, &trnSch[x].staff[3].staffName,
				&trnSch[x].staff[4].staffID, &trnSch[x].staff[4].staffName,
				&trnSch[x].staff[5].staffID, &trnSch[x].staff[5].staffName,
				&trnSch[x].staff[6].staffID, &trnSch[x].staff[6].staffName,
				&trnSch[x].staff[7].staffID, &trnSch[x].staff[7].staffName,
				&trnSch[x].staff[8].staffID, &trnSch[x].staff[8].staffName,
				&trnSch[x].staff[9].staffID, &trnSch[x].staff[9].staffName,
				&trnSch[x].driver[0].driverID, &trnSch[x].driver[0].driverName,
				&trnSch[x].driver[1].driverID, &trnSch[x].driver[1].driverName,
				&trnSch[x].schTrnPrice,
				&trnSch[x].status) != EOF) {

				if (strcmp(schNo, trnSch[x].scheduleNo) == 0) {

					printf("Schedule No: %s\n", trnSch[x].scheduleNo);
					printf("Train ID: %s\n\n", trnSch[x].trainID);
					printf("Departure Station: %s\n", trnSch[x].departureStation);
					printf("Arrival Station: %s\n\n", trnSch[x].arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch[x].departureDate.day, trnSch[x].departureDate.month, trnSch[x].departureDate.year, trnSch[x].departureTime.hours, trnSch[x].departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch[x].arrivalDate.day, trnSch[x].arrivalDate.month, trnSch[x].arrivalDate.year, trnSch[x].arrivalTime.hours, trnSch[x].arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch[x].duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch[x].mealList[i].mealName, trnSch[x].mealList[i].mainFood, trnSch[x].mealList[i].drinks, trnSch[x].mealList[i].snacks, " ", trnSch[x].mealList[i].mealPrice);
					}

					//display staff list
					printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
					printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
					printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

					for (int j = 0; j < 10; j++) {
						printf("%-13d  %-25s  %-21s\n", j + 1, trnSch[x].staff[j].staffID, trnSch[x].staff[j].staffName);
					}

					//display driver list
					printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
					printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
					printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

					for (int k = 0; k < 2; k++) {
						printf("%-14d  %-24s  %-22s\n", k + 1, trnSch[x].driver[k].driverID, trnSch[x].driver[k].driverName);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch[x].schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch[x].status);
					cond = 1;
					schIndex = x;

					printf("Do you want to change information for this train schedule? ( Y = Yes ): ");
					rewind(stdin);
					scanf("%c", &ans);
					ans = toupper(ans);

				}
				x++;
			}

		}

		if (cond != 1) {
			cond = chkInvalid(cond);
		}
		else {
			if (ans == 'Y') {
				schedule = trnSch[schIndex];
			}
			else {
				tSchedulingUserMenu();
			}
			fclose(trainSch);
		}

	} while (cond == -1);

	FILE* chkTrnMode = fopen("newTrain.txt", "r");
	char trnID[7];
	TrainInfo train;

	if (!chkTrnMode) {
		printf("Error: Cannot open newTrain.txt!!\n");
		exit(-1);
	}
	else {
		system("cls");
		printf("=============================================\n");
		printf("  Edit Train Schedule Information for %s  \n", schedule.scheduleNo);
		printf("=============================================\n");
		printf("1. Train ID\n");
		printf("2. Date and Time\n");
		printf("3. Meal List\n");
		printf("4. Staff\n");
		printf("5. Driver\n");
		printf("6. Status\n");
		printf("7. Exit to previous page\n\n");

		do {
			printf("Enter your choice: ");
			scanf("%d", &choice);

			switch (choice) {
			case 1:
				trnSch[schIndex] = changeTrainID(&schedule);
				while (fscanf(chkTrnMode, "%[^|]|%d|%d|%[^\n]\n", &train.trainID, &train.trainCoach, &train.trainCapacity, &train.drivingMode) != EOF) {
					if (strcmp(train.trainID, trnSch[schIndex].trainID) == 0) {
						if (strcmp(train.drivingMode, "MANUAL") == 0) {
							trnSch[schIndex] = addDriver(&trnSch[schIndex]);
						}
						else //if (strcmp(train.drivingMode, "AUTO") == 0) {
						{
							for (int i = 0; i < 2; i++) {
								strcpy(trnSch[schIndex].driver[i].driverID, "NULL");
								strcpy(trnSch[schIndex].driver[i].driverName, "NULL");
							}
						}
					}
				}


				break;
			case 2:
				trnSch[schIndex] = changeDateTime(&schedule);
				trnSch[schIndex].duration = calDuration(schedule);
				break;
			case 3:
				trnSch[schIndex] = changeMealList(&schedule);
				break;
			case 4:
				trnSch[schIndex] = changeStaff(&schedule);
				break;
			case 5:
				while (fscanf(chkTrnMode, "%[^|]|%d|%d|%[^\n]\n", &train.trainID, &train.trainCoach, &train.trainCapacity, &train.drivingMode) != EOF) {
					if (strcmp(trnSch[schIndex].trainID, train.trainID) == 0) {
						if (strcmp(train.drivingMode, "MANUAL") == 0) {
							trnSch[schIndex] = changeDriver(&schedule);

						}
						else {
							printf("\nError: You are not available to edit driver list because of this train's driving mode is auto!\n\n");
						}
					}
				}

				break;
			case 6:
				trnSch[schIndex] = changeStatus(&schedule);
				break;
			case 7:
				tSchedulingStaffMenu();
				break;
			default:
				choice = chkInvalid(choice);
			}

		} while (choice == -1);

		//write changed data into file again

		FILE* changedSch = fopen("trainSchedule.txt", "w");
		if (!changedSch) {
			printf("Error: Cannot open trainSchedule.txt!!\n");
			exit(-1);
		}
		else {
			for (int i = 0; i < x; i++) {
				fprintf(changedSch, "%s|%s\n%s|%s\n%02d/%02d/%04d|%02d:%02d\n%02d/%02d/%04d|%02d:%02d\n%d\n%s|%s|%s|%s|%.2f\n%s|%s|%s|%s|%.2f\n%s|%s|%s|%s|%.2f\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%.2f\n%s\n\n",
					trnSch[i].scheduleNo, trnSch[i].trainID,
					trnSch[i].departureStation, trnSch[i].arrivalStation,
					trnSch[i].departureDate.day, trnSch[i].departureDate.month, trnSch[i].departureDate.year, trnSch[i].departureTime.hours, trnSch[i].departureTime.minutes,
					trnSch[i].arrivalDate.day, trnSch[i].arrivalDate.month, trnSch[i].arrivalDate.year, trnSch[i].arrivalTime.hours, trnSch[i].arrivalTime.minutes,
					trnSch[i].duration,
					trnSch[i].mealList[0].mealName, trnSch[i].mealList[0].mainFood, trnSch[i].mealList[0].drinks, trnSch[i].mealList[0].snacks, trnSch[i].mealList[0].mealPrice,
					trnSch[i].mealList[1].mealName, trnSch[i].mealList[1].mainFood, trnSch[i].mealList[1].drinks, trnSch[i].mealList[1].snacks, trnSch[i].mealList[1].mealPrice,
					trnSch[i].mealList[2].mealName, trnSch[i].mealList[2].mainFood, trnSch[i].mealList[2].drinks, trnSch[i].mealList[2].snacks, trnSch[i].mealList[2].mealPrice,
					trnSch[i].staff[0].staffID, trnSch[i].staff[0].staffName,
					trnSch[i].staff[1].staffID, trnSch[i].staff[1].staffName,
					trnSch[i].staff[2].staffID, trnSch[i].staff[2].staffName,
					trnSch[i].staff[3].staffID, trnSch[i].staff[3].staffName,
					trnSch[i].staff[4].staffID, trnSch[i].staff[4].staffName,
					trnSch[i].staff[5].staffID, trnSch[i].staff[5].staffName,
					trnSch[i].staff[6].staffID, trnSch[i].staff[6].staffName,
					trnSch[i].staff[7].staffID, trnSch[i].staff[7].staffName,
					trnSch[i].staff[8].staffID, trnSch[i].staff[8].staffName,
					trnSch[i].staff[9].staffID, trnSch[i].staff[9].staffName,
					trnSch[i].driver[0].driverID, trnSch[i].driver[0].driverName,
					trnSch[i].driver[1].driverID, trnSch[i].driver[1].driverName,
					trnSch[i].schTrnPrice,
					trnSch[i].status);
			}
		}
		fclose(changedSch);
		free(trnSch);
		fclose(chkTrnMode);

		printf("\nDo you want to continue edit train schedule information? ( Y = Yes ): ");
		rewind(stdin);
		scanf("%c", &ans1);

		if (toupper(ans1) == 'Y') {
			modifyTrainSchedule();
		}
		else {
			tSchedulingStaffMenu();
		}
	}


}


void tSchedulingStaffDisplay() {
	int choice;

	do {
		printf("What you want to display?\n");
		printf("1. Train List\n");
		printf("2. Staff List\n");
		printf("3. Driver List\n");
		printf("4. Meal List\n");
		printf("5. Seat List\n");
		printf("6. Exit to previous page\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			staffDisplayTrainList();
			break;
		case 2:
			system("cls");
			staffDisplayStaffList();
			break;
		case 3:
			system("cls");
			staffDisplayDriverList();
			break;
		case 4:
			system("cls");
			staffDisplayMealList();
			break;
		case 5:
			system("cls");
			staffDisplaySeatList();
			break;
		case 6:
			system("cls");
			tSchedulingStaffMenu();  //staff menu
			break;
		default:
			choice = -1;
			printf("\nNo this option! Please choose again!\n\n\n");
		}
	} while (choice == -1);

}

void deleteTrainSchedule() {
	TrainSchedule schedule;
	char scheduleNo[6], ans;
	TrainSchedule* scheduleList = (TrainSchedule*)malloc(5000 * sizeof(TrainSchedule));
	int count = 0, indexEdit, frmt;
	FILE* getTrnSch = fopen("trainSchedule.txt", "r");
	if (getTrnSch == NULL) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}

	while (fscanf(getTrnSch, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
		&schedule.scheduleNo, &schedule.trainID,
		&schedule.departureStation, &schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year, &schedule.departureTime.hours, &schedule.departureTime.minutes,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes,
		&schedule.duration,
		&schedule.mealList[0].mealName, &schedule.mealList[0].mainFood, &schedule.mealList[0].drinks, &schedule.mealList[0].snacks, &schedule.mealList[0].mealPrice,
		&schedule.mealList[1].mealName, &schedule.mealList[1].mainFood, &schedule.mealList[1].drinks, &schedule.mealList[1].snacks, &schedule.mealList[1].mealPrice,
		&schedule.mealList[2].mealName, &schedule.mealList[2].mainFood, &schedule.mealList[2].drinks, &schedule.mealList[2].snacks, &schedule.mealList[2].mealPrice,
		&schedule.staff[0].staffID, &schedule.staff[0].staffName,
		&schedule.staff[1].staffID, &schedule.staff[1].staffName,
		&schedule.staff[2].staffID, &schedule.staff[2].staffName,
		&schedule.staff[3].staffID, &schedule.staff[3].staffName,
		&schedule.staff[4].staffID, &schedule.staff[4].staffName,
		&schedule.staff[5].staffID, &schedule.staff[5].staffName,
		&schedule.staff[6].staffID, &schedule.staff[6].staffName,
		&schedule.staff[7].staffID, &schedule.staff[7].staffName,
		&schedule.staff[8].staffID, &schedule.staff[8].staffName,
		&schedule.staff[9].staffID, &schedule.staff[9].staffName,
		&schedule.driver[0].driverID, &schedule.driver[0].driverName,
		&schedule.driver[1].driverID, &schedule.driver[1].driverName,
		&schedule.schTrnPrice,
		&schedule.status) != EOF) {

		scheduleList[count] = schedule;
		count++;

		printf("Schedule No: %s\n", schedule.scheduleNo);
		printf("Train ID: %s\n\n", schedule.trainID);
		printf("Departure Station: %s\n", schedule.departureStation);
		printf("Arrival Station: %s\n\n", schedule.arrivalStation);
		printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year, schedule.departureTime.hours, schedule.departureTime.minutes);
		printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year, schedule.arrivalTime.hours, schedule.arrivalTime.minutes);
		printf("Duration: %d minutes\n\n", schedule.duration);

		//display meal list
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

		for (int i = 0; i < 3; i++) {
			printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", schedule.mealList[i].mealName, schedule.mealList[i].mainFood, schedule.mealList[i].drinks, schedule.mealList[i].snacks, " ", schedule.mealList[i].mealPrice);
		}

		//display staff list
		printf("\n%-13s  %-25s  %-21s\n", "============", "========================", "====================");
		printf("%-13s  %-25s  %-21s\n", "  STAFF NO  ", "        STAFF ID        ", "     STAFF NAME     ");
		printf("%-13s  %-25s  %-21s\n", "============", "========================", "====================");

		for (int j = 0; j < 10; j++) {
			printf("%-13d  %-25s  %-21s\n", j + 1, schedule.staff[j].staffID, schedule.staff[j].staffName);
		}

		//display driver list
		printf("\n%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");
		printf("%-14s  %-24s  %-22s\n", "  DRIVER NO  ", "       DRIVER ID       ", "     DRIVER NAME     ");
		printf("%-14s  %-24s  %-22s\n", "=============", "=======================", "=====================");

		for (int k = 0; k < 2; k++) {
			printf("%-14d  %-24s  %-22s\n", k + 1, schedule.driver[k].driverID, schedule.driver[k].driverName);
		}

		//display price
		printf("\nPrice: RM%.2f\n", schedule.schTrnPrice);

		//display status
		printf("\nStatus: %s\n\n\n", schedule.status);

	}
	fclose(getTrnSch);

	do {
		printf("\n\nWhich Schedule you want to delete?\n");
		printf("Enter Schedule No: ");
		rewind(stdin);
		scanf("%s", scheduleNo);
		lowerToUpper(scheduleNo, funcArrayLength(scheduleNo));

		frmt = chkScheduleFormat(scheduleNo);
		if (frmt != 1)
			frmt = chkInvalid(frmt);
	} while (frmt == -1);

	indexEdit = 0;
	for (int a = 0; a < count; a++) {
		if (strcmp(scheduleNo, scheduleList[a].scheduleNo) == 0) {
			indexEdit = a;
		}
	}
	for (int b = indexEdit; b < count-1; b++) {
		scheduleList[indexEdit] = scheduleList[indexEdit + 1];
	}
	count -= 1;


	//Delete seat list for this schedule
	int  seatIndex = 0, editInd;
	SeatDisplay* seatTable = (SeatDisplay*)malloc(5000 * sizeof(SeatDisplay));

	FILE* seat = fopen("seatList.txt", "r");
	if (!seat) {
		printf("Error: Cannot open seatList.txt!!\n");
		exit(-1);
	}
	else {
		while (fscanf(seat, "%[^\n]\n", seatTable[seatIndex].schNo) != EOF) {
			for (int y = 0; y < 119; y++) {
				fscanf(seat, "%[^|]|%c\n", &seatTable[seatIndex].seat[y].seatNo, &seatTable[seatIndex].seat[y].status);
			}
			fscanf(seat, "%[^|]|%c\n\n\n", &seatTable[seatIndex].seat[119].seatNo, &seatTable[seatIndex].seat[119].status);
			seatIndex++;
		}
		fclose(seat);
		for (int az = 0; az < seatIndex; az++) {
			if (strcmp(scheduleNo, seatTable[seatIndex].schNo) == 0) {
				editInd = az;
			}
		}
		editInd = 0;
		for (int b = editInd; b < seatIndex; b++) {
			seatTable[editInd] = seatTable[editInd + 1];
		}
		seatIndex -= 1;

		FILE* seat = fopen("seatList.txt", "w");
		if (!seat) {
			printf("Error: Cannot open seatList.txt!!\n");
			exit(-1);
		}
		else {
			for (int ay = 0; ay < seatIndex; ay++) {
				fprintf(seat, "%s\n", seatTable[ay].schNo);
				for (int y = 0; y < 119; y++) {
					fscanf(seat, "%s|%c\n", &seatTable[ay].seat[y].seatNo, &seatTable[ay].seat[y].status);
				}
				fscanf(seat, "%s|%c\n\n\n", &seatTable[ay].seat[119].seatNo, &seatTable[ay].seat[119].status);
			}

		}
		fclose(seat);
		free(seatTable);

	}

	FILE* wTrnSch = fopen("trainSchedule.txt", "w");
	if (wTrnSch == NULL) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		for (int c = 0; c < count; c++) {
			fprintf(wTrnSch, "%s|%s\n%s|%s\n%02d/%02d/%04d|%02d:%02d\n%02d/%02d/%04d|%02d:%02d\n%d\n%s|%s|%s|%s|%.2f\n%s|%s|%s|%s|%.2f\n%s|%s|%s|%s|%.2f\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%s|%s\n%.2f\n%s\n\n",
				scheduleList[c].scheduleNo, scheduleList[c].trainID,
				scheduleList[c].departureStation, scheduleList[c].arrivalStation,
				scheduleList[c].departureDate.day, scheduleList[c].departureDate.month, scheduleList[c].departureDate.year, scheduleList[c].departureTime.hours, scheduleList[c].departureTime.minutes,
				scheduleList[c].arrivalDate.day, scheduleList[c].arrivalDate.month, scheduleList[c].arrivalDate.year, scheduleList[c].arrivalTime.hours, scheduleList[c].arrivalTime.minutes,
				scheduleList[c].duration,
				scheduleList[c].mealList[0].mealName, scheduleList[c].mealList[0].mainFood, scheduleList[c].mealList[0].drinks, scheduleList[c].mealList[0].snacks, scheduleList[c].mealList[0].mealPrice,
				scheduleList[c].mealList[1].mealName, scheduleList[c].mealList[1].mainFood, scheduleList[c].mealList[1].drinks, scheduleList[c].mealList[1].snacks, scheduleList[c].mealList[1].mealPrice,
				scheduleList[c].mealList[2].mealName, scheduleList[c].mealList[2].mainFood, scheduleList[c].mealList[2].drinks, scheduleList[c].mealList[2].snacks, scheduleList[c].mealList[2].mealPrice,
				scheduleList[c].staff[0].staffID, scheduleList[c].staff[0].staffName,
				scheduleList[c].staff[1].staffID, scheduleList[c].staff[1].staffName,
				scheduleList[c].staff[2].staffID, scheduleList[c].staff[2].staffName,
				scheduleList[c].staff[3].staffID, scheduleList[c].staff[3].staffName,
				scheduleList[c].staff[4].staffID, scheduleList[c].staff[4].staffName,
				scheduleList[c].staff[5].staffID, scheduleList[c].staff[5].staffName,
				scheduleList[c].staff[6].staffID, scheduleList[c].staff[6].staffName,
				scheduleList[c].staff[7].staffID, scheduleList[c].staff[7].staffName,
				scheduleList[c].staff[8].staffID, scheduleList[c].staff[8].staffName,
				scheduleList[c].staff[9].staffID, scheduleList[c].staff[9].staffName,
				scheduleList[c].driver[0].driverID, scheduleList[c].driver[0].driverName,
				scheduleList[c].driver[1].driverID, scheduleList[c].driver[1].driverName,
				scheduleList[c].schTrnPrice,
				scheduleList[c].status);
		}
	}
	fclose(wTrnSch);
	free(scheduleList);
	printf("\nThe train schedule has successfully deleted!!\n\n");

	printf("\n\nDo you want to continue delete Train Schedule? ( Y = Yes ): ");
	rewind(stdin);
	scanf("%c", &ans);

	if (toupper(ans) == 'Y') {
		deleteTrainSchedule();
	}
	else {
		tSchedulingDelete();
	}
}

void tSchedulingDelete() {
	int choice;

	do {
		printf("What information you want to delete?\n");
		printf("1. Train Schedule information\n");
		printf("2. Exit to previous page\n\n");

		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			deleteTrainSchedule();
			break;
		case 2:
			system("cls");
			tSchedulingStaffMenu();
			break;
		default:
			choice = chkInvalid(choice);
		}
	} while (choice == -1);
}



void tSchedulingReport() {
	int choice;

	do {
		system("cls");
		printf("Which report you want to generate?\n");
		printf("1. Train Delayed\n");
		printf("2. Exit to previous page\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			delayedReport();
			break;
		case 2:
			system("cls");
			tSchedulingStaffMenu();
			break;
		default:
			choice = chkInvalid(choice);
		}
	} while (choice == -1);
}

void delayedReport() {
	Date start, end, dateNow;
	int delayed;
	char ans;

	system("cls");
	/* Calculate current Date */
	time_t current_time;
	struct tm* local_time;

	// Get the current time
	current_time = time(NULL);

	// Convert the current time to the local time
	local_time = localtime(&current_time);

	// Extract day, month, and year
	dateNow.day = local_time->tm_mday;
	dateNow.month = local_time->tm_mon + 1; // Months are 0-based, so add 1
	dateNow.year = local_time->tm_year + 1900; // Years since 1900


	printf("Enter the start date of the period in ( DD/MM/YYYY ): ");
	scanf("%d/%d/%d", &start.day, &start.month, &start.year);

	printf("\nEnter the end date of the period in ( DD/MM/YYYY ): ");
	scanf("%d/%d/%d", &end.day, &end.month, &end.year);

	FILE* report = fopen("trainSchedule.txt", "r");
	if (!report) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		TrainSchedule schedule;
		delayed = 0;
		while (fscanf(report, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
			&schedule.scheduleNo, &schedule.trainID,
			&schedule.departureStation, &schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year, &schedule.departureTime.hours, &schedule.departureTime.minutes,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes,
			&schedule.duration,
			&schedule.mealList[0].mealName, &schedule.mealList[0].mainFood, &schedule.mealList[0].drinks, &schedule.mealList[0].snacks, &schedule.mealList[0].mealPrice,
			&schedule.mealList[1].mealName, &schedule.mealList[1].mainFood, &schedule.mealList[1].drinks, &schedule.mealList[1].snacks, &schedule.mealList[1].mealPrice,
			&schedule.mealList[2].mealName, &schedule.mealList[2].mainFood, &schedule.mealList[2].drinks, &schedule.mealList[2].snacks, &schedule.mealList[2].mealPrice,
			&schedule.staff[0].staffID, &schedule.staff[0].staffName,
			&schedule.staff[1].staffID, &schedule.staff[1].staffName,
			&schedule.staff[2].staffID, &schedule.staff[2].staffName,
			&schedule.staff[3].staffID, &schedule.staff[3].staffName,
			&schedule.staff[4].staffID, &schedule.staff[4].staffName,
			&schedule.staff[5].staffID, &schedule.staff[5].staffName,
			&schedule.staff[6].staffID, &schedule.staff[6].staffName,
			&schedule.staff[7].staffID, &schedule.staff[7].staffName,
			&schedule.staff[8].staffID, &schedule.staff[8].staffName,
			&schedule.staff[9].staffID, &schedule.staff[9].staffName,
			&schedule.driver[0].driverID, &schedule.driver[0].driverName,
			&schedule.driver[1].driverID, &schedule.driver[1].driverName,
			&schedule.schTrnPrice,
			&schedule.status) != EOF) {
			if ((strcmp(schedule.status, "DELAYED") == 0) && (compareDates(start, schedule.departureDate) <= 0) && (compareDates(end, schedule.departureDate) >= 0)) {
				delayed++;
			}
		}

		fclose(report);

		//Generate Report
		system("cls");

		printf("-------------------- Report for Train Delayed --------------------\n\n");

		printf("Generated Date: %02d/%02d/%04d\n\n", dateNow.day, dateNow.month, dateNow.year);
		printf("From: %02d/%02d/%04d\n", start.day, start.month, start.year);
		printf("To: %02d/%02d/%04d\n\n", end.day, end.month, end.year);

		printf("Train Delayed Time(s): %d\n", delayed);

		if (delayed == 0) {
			printf("\n\n\nIt's perfect!! Please keep going!\n\n");
		}
		else {
			printf("\n\n\nIt's not a good performance for members. \nPlease avoid this 'delayed' circumstance happened!\n\n");
		}

		printf("------------------------------------------------------------------\n");

	}
	printf("\nDo you want to generate other report? ( Y = Yes ): ");
	rewind(stdin);
	scanf("%c", &ans);

	if (toupper(ans) == 'Y') {
		tSchedulingReport();
	}
	else {
		tSchedulingStaffMenu();
	}
}


//User
void tSchedulingUserMenu() {
	int chooseFunction;

	do {
		printf("User - Train Scheduling\n\n");
		printf("1. Search\n");
		printf("2. Display\n");
		printf("3. Exit\n\n");
		printf("Choose a function to continue: ");
		scanf("%d", &chooseFunction);

		switch (chooseFunction) {
		case 1:
			system("cls");
			userSearchTrain();
			break;
		case 2:
			system("cls");
			tSchedulingUserDisplay();
			break;
		case 3:
			system("cls");
			main();
			break;
		default:
			chooseFunction = chkInvalid(chooseFunction);
		}
	} while (chooseFunction == -1);
}


//User Search Functions
void userSearchTrain() {
	int opt;
	do {
		printf("What you want to search for?\n");
		printf("1. Train Information\n");
		printf("2. Train Schedule Information\n");
		printf("3. Exit to previous page\n");
		printf("\nChoice: ");
		scanf("%d", &opt);

		if (opt == 1) {
			system("cls");
			userSearchTrainInfo();
		}
		else if (opt == 2) {
			system("cls");
			userSearchTrainSchedule();
		}
		else if (opt == 3) {
			system("cls");
			tSchedulingUserMenu();
		}
		else {
			opt = chkInvalid(opt);
		}

	} while (opt == -1);
}

void userSearchTrainInfo() {
	int opt;
	do {
		printf("Which way you want to search by?\n");
		printf("1. Train ID\n");
		printf("2. Train Driving Mode\n");
		printf("3. Exit to previous page\n");
		printf("\nChoice: ");
		scanf("%d", &opt);

		if (opt == 1) {
			system("cls");
			userSearchTrainInfoByTrnID();
		}
		else if (opt == 2) {
			system("cls");
			userSearchTrainInfoByDrvMode();
		}
		else if (opt == 3) {
			system("cls");
			userSearchTrain();
		}
		else {
			opt = chkInvalid(opt);
		}

	} while (opt == -1);
}

void userSearchTrainInfoByTrnID() {
	char trainID[7];
	TrainInfo info;
	char ans;

	FILE* trnInfo = fopen("newTrain.txt", "r");
	if (!trnInfo) {
		printf("Error: Cannot open newTrain.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int frmt;
			int condt = 0;

			printf("--------------------------------------\n");
			printf("Search Train Information By [TRAIN ID]\n");
			printf("--------------------------------------\n\n");

			do {
				frmt = 1;


				printf("Enter Train ID: ");
				rewind(stdin);
				scanf("%[^\n]", &trainID);
				lowerToUpper(trainID, funcArrayLength(trainID));

				//check train id format
				frmt = chkTrainIdFormat(trainID);

				if (frmt == 0) {
					printf("Wrong train ID format!! Please enter again!\n\n");
				}
				else {
					fseek(trnInfo, SEEK_SET, 0);
					system("cls");
				}

			} while (frmt == 0);

			while (fscanf(trnInfo, "%[^|]|%d|%d|%[^\n]\n", &info.trainID, &info.trainCoach, &info.trainCapacity, &info.drivingMode) != EOF) {
				if (strcmp(info.trainID, trainID) == 0) {
					printf("\n-Here is the information for train [%s]-\n\n", info.trainID);
					printf("Train ID: %s\n", info.trainID);
					printf("Number of Train Coach: %d\n", info.trainCoach);
					printf("Train Capacity: %d\n", info.trainCapacity);
					printf("Train Driving Mode: %s\n\n", info.drivingMode);
					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train information for this train ID!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrain();
			}
		} while (toupper(ans) == 'Y');

		fclose(trnInfo);
	}

}

void userSearchTrainInfoByDrvMode() {
	char drvMode[7];
	TrainInfo info;
	char ans;

	FILE* trnInfo = fopen("newTrain.txt", "r");
	if (!trnInfo) {
		printf("Error: Cannot open newTrain.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int frmt;

			printf("------------------------------------------------\n");
			printf("Search Train Information By [TRAIN DRIVING MODE]\n");
			printf("------------------------------------------------\n\n");

			do {
				frmt = 1;

				printf("Enter Train Driving Mode ( MANUAL / AUTO): ");
				rewind(stdin);
				scanf("%s", &drvMode);
				lowerToUpper(drvMode, funcArrayLength(drvMode));

				//check input is manual or auto or else
				frmt = chkDrivingMode(drvMode);

				if (frmt == 0) {
					printf("Wrong input for Driving Mode!! Please enter again!\n\n");
				}
				else {
					system("cls");
				}

			} while (frmt == 0);
			fseek(trnInfo, SEEK_SET, 0);

			while (fscanf(trnInfo, "%[^|]|%d|%d|%[^\n]\n", &info.trainID, &info.trainCoach, &info.trainCapacity, &info.drivingMode) != EOF) {
				if (strcmp(info.drivingMode, drvMode) == 0) {
					printf("\n-Here is the information for train [%s]-\n\n", info.trainID);
					printf("Train ID: %s\n", info.trainID);
					printf("Number of Train Coach: %d\n", info.trainCoach);
					printf("Train Capacity: %d\n", info.trainCapacity);
					printf("Train Driving Mode: %s\n\n", info.drivingMode);
				}
			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrain();
			}
		} while (toupper(ans) == 'Y');

		fclose(trnInfo);
	}

}

void userSearchTrainID() {
	char trainID[7];
	TrainSchedule trnSch;
	char ans;

	FILE* trnID = fopen("trainSchedule.txt", "r");
	if (!trnID) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int frmt;
			int condt = 0;
			do {
				frmt = 1;

				printf("Enter train ID: ");
				rewind(stdin);
				scanf("%s", &trainID);
				lowerToUpper(trainID, funcArrayLength(trainID));

				//check train ID format
				frmt = chkTrainIdFormat(trainID);

				if (frmt == 0) {
					printf("Wrong train ID format!! Please enter again!\n\n");
				}
				else {
					fseek(trnID, SEEK_SET, 0);
					system("cls");
				}
			} while (frmt == 0);

			while (fscanf(trnID, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(trainID, trnSch.trainID) == 0) {
					printf("Schedule No: %s\n\n", trnSch.scheduleNo);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this train ID!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');


		fclose(trnID);
	}
}

void userSearchDptDate() {
	int day, month, year;
	TrainSchedule trnSch;
	char ans;

	FILE* date = fopen("trainSchedule.txt", "r");
	if (!date) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(date, SEEK_SET, 0);
			printf("Enter Departure Date in format (DD/MM/YYY): ");
			scanf("%d/%d/%d", &day, &month, &year);

			system("cls");

			while (fscanf(date, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if ((day == trnSch.departureDate.day) && (month == trnSch.departureDate.month) && (year == trnSch.departureDate.year)) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this departure date!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(date);

	}


}

void userSearchArrDate() {
	int day, month, year;
	TrainSchedule trnSch;
	char ans;

	FILE* date = fopen("trainSchedule.txt", "r");
	if (!date) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(date, SEEK_SET, 0);
			printf("Enter Arrival Date in format (DD/MM/YYY): ");
			scanf("%d/%d/%d", &day, &month, &year);

			system("cls");

			while (fscanf(date, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if ((day == trnSch.arrivalDate.day) && (month == trnSch.arrivalDate.month) && (year == trnSch.arrivalDate.year)) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this arrival date!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(date);

	}
}

void userSearchDptStation() {

	char dptStation[100];
	TrainSchedule trnSch;
	char ans;

	FILE* station = fopen("trainSchedule.txt", "r");
	if (!station) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(station, SEEK_SET, 0);
			printf("Enter Departure Station: ");
			rewind(stdin);
			scanf("%[^\n]", &dptStation);
			lowerToUpper(dptStation, funcArrayLength(dptStation));
			system("cls");

			while (fscanf(station, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(dptStation, trnSch.departureStation) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this departure station!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(station);

	}

}

void userSearchArrStation() {

	char arrStation[100];
	TrainSchedule trnSch;
	char ans;

	FILE* station = fopen("trainSchedule.txt", "r");
	if (!station) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;

			fseek(station, SEEK_SET, 0);
			printf("Enter Arrival Station: ");
			rewind(stdin);
			scanf("%[^\n]", &arrStation);
			lowerToUpper(arrStation, funcArrayLength(arrStation));
			system("cls");

			while (fscanf(station, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(arrStation, trnSch.arrivalStation) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this arrival station!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(station);

	}
}

void userSearchScheduleNo() {

	char schNo[6];
	TrainSchedule trnSch;
	char ans;

	FILE* scheduleNo = fopen("trainSchedule.txt", "r");
	if (!scheduleNo) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;
			int frmt;

			do {
				frmt = 1;

				printf("Enter Schedule No: ");
				rewind(stdin);
				scanf("%[^\n]", &schNo);

				//check Schedule no format
				lowerToUpper(schNo, funcArrayLength(schNo));
				frmt = chkScheduleFormat(schNo);
				if (frmt == 0) {
					printf("Wrong schedule no format!! Please enter again!\n\n");
				}
				else {
					fseek(scheduleNo, SEEK_SET, 0);
					system("cls");
				}
			} while (frmt == 0);

			while (fscanf(scheduleNo, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(schNo, trnSch.scheduleNo) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this schedule no!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(scheduleNo);

	}
}

void userSearchScheduleStatus() {

	char status[6];
	TrainSchedule trnSch;
	char ans;

	FILE* schStatus = fopen("trainSchedule.txt", "r");
	if (!schStatus) {
		printf("Error: Cannot open trainSchedule.txt!!\n");
		exit(-1);
	}
	else {
		do {
			int condt = 0;
			int inp;

			do {
				inp = 1;
				printf("Enter Status ( COMPLETED / PREPARING / DELAYED ): ");
				rewind(stdin);
				scanf("%s", &status);

				lowerToUpper(status, funcArrayLength(status));

				if (strcmp(status, "COMPLETED") == 0 || strcmp(status, "PREPARING") == 0 || strcmp(status, "DELAYED") == 0) {
					inp = 0;
					fseek(schStatus, SEEK_SET, 0);
					system("cls");
				}
				else {
					printf("Invalid Input! Please Enter Again!\n");
				}

			} while (inp != 0);

			while (fscanf(schStatus, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
				&trnSch.scheduleNo, &trnSch.trainID,
				&trnSch.departureStation, &trnSch.arrivalStation,
				&trnSch.departureDate.day, &trnSch.departureDate.month, &trnSch.departureDate.year, &trnSch.departureTime.hours, &trnSch.departureTime.minutes,
				&trnSch.arrivalDate.day, &trnSch.arrivalDate.month, &trnSch.arrivalDate.year, &trnSch.arrivalTime.hours, &trnSch.arrivalTime.minutes,
				&trnSch.duration,
				&trnSch.mealList[0].mealName, &trnSch.mealList[0].mainFood, &trnSch.mealList[0].drinks, &trnSch.mealList[0].snacks, &trnSch.mealList[0].mealPrice,
				&trnSch.mealList[1].mealName, &trnSch.mealList[1].mainFood, &trnSch.mealList[1].drinks, &trnSch.mealList[1].snacks, &trnSch.mealList[1].mealPrice,
				&trnSch.mealList[2].mealName, &trnSch.mealList[2].mainFood, &trnSch.mealList[2].drinks, &trnSch.mealList[2].snacks, &trnSch.mealList[2].mealPrice,
				&trnSch.staff[0].staffID, &trnSch.staff[0].staffName,
				&trnSch.staff[1].staffID, &trnSch.staff[1].staffName,
				&trnSch.staff[2].staffID, &trnSch.staff[2].staffName,
				&trnSch.staff[3].staffID, &trnSch.staff[3].staffName,
				&trnSch.staff[4].staffID, &trnSch.staff[4].staffName,
				&trnSch.staff[5].staffID, &trnSch.staff[5].staffName,
				&trnSch.staff[6].staffID, &trnSch.staff[6].staffName,
				&trnSch.staff[7].staffID, &trnSch.staff[7].staffName,
				&trnSch.staff[8].staffID, &trnSch.staff[8].staffName,
				&trnSch.staff[9].staffID, &trnSch.staff[9].staffName,
				&trnSch.driver[0].driverID, &trnSch.driver[0].driverName,
				&trnSch.driver[1].driverID, &trnSch.driver[1].driverName,
				&trnSch.schTrnPrice,
				&trnSch.status) != EOF) {
				if (strcmp(status, trnSch.status) == 0) {
					printf("Schedule No: %s\n", trnSch.scheduleNo);
					printf("Train ID: %s\n\n", trnSch.trainID);
					printf("Departure Station: %s\n", trnSch.departureStation);
					printf("Arrival Station: %s\n\n", trnSch.arrivalStation);
					printf("Departure Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.departureDate.day, trnSch.departureDate.month, trnSch.departureDate.year, trnSch.departureTime.hours, trnSch.departureTime.minutes);
					printf("Arrival Date and Time: %02d/%02d/%04d  %02d:%02d\n", trnSch.arrivalDate.day, trnSch.arrivalDate.month, trnSch.arrivalDate.year, trnSch.arrivalTime.hours, trnSch.arrivalTime.minutes);
					printf("Duration: %d minutes\n\n", trnSch.duration);

					//display meal list
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
					printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

					for (int i = 0; i < 3; i++) {
						printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", trnSch.mealList[i].mealName, trnSch.mealList[i].mainFood, trnSch.mealList[i].drinks, trnSch.mealList[i].snacks, " ", trnSch.mealList[i].mealPrice);
					}

					//display price
					printf("\nPrice: RM%.2f\n", trnSch.schTrnPrice);

					//display status
					printf("\nStatus: %s\n\n\n", trnSch.status);

					condt = 1;
				}
			}
			if (condt != 1) {

				printf("Sorry! No train schedule information for this schedule status!\n\n");

			}

			printf("Do you want to search again? ( Y = Yes): ");
			rewind(stdin);
			scanf("%c", &ans);
			printf("\n");

			if (toupper(ans) != 'Y') {
				userSearchTrainSchedule();
			}
		} while (toupper(ans) == 'Y');
		fclose(schStatus);

	}
}

void userSearchTrainSchedule() {
	int choice;

	do {
		system("cls");
		printf("Which way you want to search by?\n");
		printf("1. Train ID\n");
		printf("2. Departure Date\n");
		printf("3. Arrival Date\n");
		printf("4. Departure Station\n");
		printf("5. Arrival Station\n");
		printf("6. Schedule No\n");
		printf("7. Train Schedule Status\n");
		printf("8. Exit to previous page\n");
		printf("\nOption: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			userSearchTrainID();
			break;
		case 2:
			system("cls");
			userSearchDptDate();
			break;
		case 3:
			system("cls");
			userSearchArrDate();
			break;
		case 4:
			system("cls");
			userSearchDptStation();
			break;
		case 5:
			system("cls");
			userSearchArrStation();
			break;
		case 6:
			system("cls");
			userSearchScheduleNo();
			break;
		case 7:
			system("cls");
			userSearchScheduleStatus();
			break;
		case 8:
			system("cls");
			tSchedulingUserMenu();
			break;
		default:
			choice = chkInvalid(choice);
		}
	} while (choice == -1);
}

//Display Functions for User
void userDisplayMealList() {

	FILE* list = fopen("mealList.txt", "r");
	Meal mealList;
	char ans;

	if (!list) {
		printf("Error: Cannot open mealList.txt!!\n");
		exit(-1);
	}
	else {
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "  MEAL NAME  ", "        MAIN FOOD        ", "       DRINKS       ", "       SNACKS       ", "  PRICE  ");
		printf("%-14s  %-26s  %-21s  %-21s  %-10s\n", "=============", "=========================", "====================", "====================", "=========");

		for (int i = 0; i < 3; i++) {
		}

		while (fscanf(list, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &mealList.mealName, &mealList.mainFood, &mealList.drinks, &mealList.snacks, &mealList.mealPrice) != EOF) {

			printf("%-14s  %-26s  %-21s  %-21s  %2s%-.2f\n", mealList.mealName, mealList.mainFood, mealList.drinks, mealList.snacks, " ", mealList.mealPrice);

		}

		fclose(list);

		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingUserDisplay();
		}
		else {
			tSchedulingUserMenu();
		}
	}



}

void userDisplayTrainList() {
	FILE* train = fopen("newTrain.txt", "r");
	TrainInfo trnInfo;
	char ans;

	if (!train) {
		printf("Error: Cannot open file!\n");
		exit(-1);
	}
	else {

		printf("%-19s  %-18s  %-21s  %-s\n", "==================", "=================", "====================", "================");
		printf("%-19s  %-18s  %-21s  %-s\n", "     TRAIN ID     ", "   TRAIN COACH   ", "   TRAIN CAPACITY   ", "  DRIVING MODE  ");
		printf("%-19s  %-18s  %-21s  %-s\n", "==================", "=================", "====================", "================");

		while (fscanf(train, "%[^|]|%d|%d|%[^\n]\n", &trnInfo.trainID, &trnInfo.trainCoach, &trnInfo.trainCapacity, &trnInfo.drivingMode) != EOF) {

			printf("%-19s  %-18d  %-21d  %-s\n", trnInfo.trainID, trnInfo.trainCoach, trnInfo.trainCapacity, trnInfo.drivingMode);

		}

		fclose(train);

		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingUserDisplay();
		}
		else {
			tSchedulingUserMenu();
		}
	}

}

void userDisplaySeatList() {

	int  index = 0, frmt;
	char ans, inp[6];
	SeatDisplay seatTable;

	FILE* seat = fopen("seatList.txt", "r");
	if (!seat) {
		printf("Error: Cannot open seatList.txt!!\n");
		exit(-1);
	}
	else {
		do {
			frmt = 0;
			printf("Which train schedule's seat list you want to display?\n");
			printf("Enter the Schedule No: ");
			rewind(stdin);
			scanf("%s", &inp);
			lowerToUpper(inp, funcArrayLength(inp));
			frmt = chkScheduleFormat(inp);

			if (frmt != 1) {
				frmt = chkInvalid(frmt);
			}
		} while (frmt == -1);

		system("cls");
		fseek(seat, SEEK_SET, 0);
		while (fscanf(seat, "%[^\n]\n", seatTable.schNo) != EOF) {
			for (int y = 0; y < 120; y++) {
				fscanf(seat, "%[^|]|%c\n", &seatTable.seat[y].seatNo, &seatTable.seat[y].status);
			}
			if (strcmp(inp, seatTable.schNo) == 0) {
				printf("********************************* Seat List for [ %s ]**************************************\n\n", seatTable.schNo);

				for (int t = 0; t < 40; t += 4) {
					for (int u = 0; u < 3; u++) {
						for (int v = 0; v < 4; v++) {

							if (seatTable.seat[index].status == 'A')
								printf("[%s]", seatTable.seat[index].seatNo);
							else
								printf("{%s}", seatTable.seat[index].seatNo);

							if (v == 1)
								printf("--");
							index++;
						}
						printf("\t\t");
						index += 36;
					}
					printf("\n");
					index = t + 4;
				}
				printf("\n**********************************************************************************************\n\n");

				printf("[ ] = Available\t{ } = Booked\n");
			}

		}



		printf("\nDo you want to see other lists? ( Y = Yes / Other = Exit to menu page ): ");
		rewind(stdin);
		scanf("%c", &ans);

		if (toupper(ans) == 'Y') {
			printf("\n\n");
			tSchedulingUserDisplay();
		}
		else {
			tSchedulingUserMenu();
		}

		fclose(seat);
	}

}

void tSchedulingUserDisplay() {

	int choice;

	do {
		printf("What you want to display?\n");
		printf("1. Train List\n");
		printf("2. Meal List\n");
		printf("3. Seat List\n");
		printf("4. Exit to previous page\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			userDisplayTrainList();
			break;
		case 2:
			system("cls");
			userDisplayMealList();
			break;
		case 3:
			system("cls");
			userDisplaySeatList();
			break;
		case 4:
			system("cls");
			tSchedulingUserMenu();//user menu
			break;
		default:
			choice = -1;
			printf("\nNo this option! Please choose again!\n\n\n");
		}
	} while (choice == -1);

}

//Function to check ScheduleNo Format
int chkScheduleFormat(char scheduleNo[]) {

	if (funcArrayLength(scheduleNo) != 5) {
		return 0;
	}

	if (!isalpha(scheduleNo[0]) || scheduleNo[0] != 'S') {
		return 0;
	}

	for (int i = 1; i < 5; i++) {
		if (!isdigit(scheduleNo[i]))
			return 0;
	}

	return 1;
}

//Function to check TrainID Format
int chkTrainIdFormat(char trainID[]) {

	if (funcArrayLength(trainID) != 6) {
		return 0;
	}

	for (int i = 0; i < 3; i++) {
		if (!isalpha(trainID[i]) || (trainID[0] != 'T' && trainID[1] != 'R' && trainID[2] != 'N')) {
			return 0;
		}
	}


	for (int i = 3; i < 6; i++) {
		if (!isdigit(trainID[i]))
			return 0;
	}

	return 1;
}

//Function to check DriverID format
int chkDriverIdFormat(char driverID[]) {

	if (funcArrayLength(driverID) != 6) {
		return 0;
	}

	for (int i = 0; i < 3; i++) {
		if (!isalpha(driverID[i]) || (driverID[0] != 'T' && driverID[1] != 'R' && driverID[2] != 'D')) {
			return 0;
		}
	}


	for (int i = 3; i < 6; i++) {
		if (!isdigit(driverID[i]))
			return 0;
	}

	return 1;
}

// Function to calculate the number of days in a month
int daysInMonth(int month, int year) {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		// Check for leap year
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return 29;
		}
		else {
			return 28;
		}
	default:
		return -1; // Invalid month
	}
}


// Function to calculate the difference in days between two dates
int dateDifference(Date d1, Date d2) {
	int days1 = d1.day + (d1.month - 1) * daysInMonth(d1.month, d1.year) + d1.year * 365;
	int days2 = d2.day + (d2.month - 1) * daysInMonth(d2.month, d2.year) + d2.year * 365;

	return days2 - days1;
}


//Function to calculate duration in minutes
int calDuration(TrainSchedule trnSch) {

	int duration = 0;

	// Calculate duration in minutes
	int departureMinutes = trnSch.departureTime.hours * 60 + trnSch.departureTime.minutes;
	int arrivalMinutes = trnSch.arrivalTime.hours * 60 + trnSch.arrivalTime.minutes;

	// Calculate date difference (assuming dateDifference function works correctly)
	int dateDiff = dateDifference(trnSch.departureDate, trnSch.arrivalDate);

	if (arrivalMinutes < departureMinutes) {
		duration = (24 * 60 - departureMinutes) + arrivalMinutes;
		duration += (dateDiff - 1) * 24 * 60;
	}
	else {
		duration = arrivalMinutes - departureMinutes;
		duration += dateDiff * 24 * 60;
	}

	return duration;

}

//Function to check ScheduleNo Format
int chkDrivingMode(char drvMode[]) {

	if (strcmp(drvMode, "MANUAL") == 0) {
		return 1;
	}
	else if (strcmp(drvMode, "AUTO") == 0) {
		return 1;
	}
	else {
		return 0;
	}

}

//Function to display error message when get invalid input
int chkInvalid(int rtr) {

	printf("\nInvalid Input! Please Enter Again!\n\n");
	rtr = -1;

	return rtr;

}

