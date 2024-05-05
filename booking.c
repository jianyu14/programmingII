#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>
#pragma warning(disable:4996)

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
}Member;

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
	char invoiceNo[10], invSchNo[6], membID[7];
	int ticketQtt;
	double totalAmount;
	Date paymentDate;
	Ticket ticBook[120];
}Invoice;

typedef struct {
	char seatNo[4], status;
}Seat;

typedef struct {
	char schNo[6];
	Seat seat[120];
}SeatDisplay;

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

void userMenuBK(Member*);
void newBooking(Member*);
void editPreBooking(Member*);
void viewPreBooking(Member*);
void bookBySch(Member*);
void bookByStation(Member*);
int payByCreditCard(double invAmt);
void storeToBooking(Invoice*);
void currentDate(Invoice*);
void bookingTicket(TrainSchedule*, Member*);
void printMeal(TrainSchedule*);
void printInvoice(TrainSchedule*, Member*, Invoice*);
int invalid(int rtr);
int funcArrayLength(char arr[]);
void lowerToUpper(char arr[], int length);
Invoice editMeal(Invoice*, int ticInd);
Invoice changeSeat(Invoice*, int ticInd);
Invoice cancelTicket(Invoice*, int ticInd);
void displayEditTicket(Invoice*, int ticInd);
void displaySeat(SeatDisplay* seatTable);
int compareDates(Date date1, Date date2);
void staffMenuBK();
void viewTrnBookingStatus();
void generateReportBK();
void topMealR();
void trainOccupancyRate();

void userMenuBK(Member* member) {

	int inp = 0;
	char ans;

	system("cls");
	printf("\n\n************ User Menu ************\n");
	printf("1. New Booking\n");
	printf("2. Edit Previous Booking\n");
	printf("3. View Previous Booking\n");
	printf("4. Return to Previous Page\n");
	printf("***********************************\n");

	do {
		printf("Select your choice by enter an integer => ");
		scanf("%d", &inp);

		switch (inp) {

		case 1:
			newBooking(member);
			break;

		case 2:
			editPreBooking(member);
			break;

		case 3:
			viewPreBooking(member);
			break;

		case 4:
			printf("Do you sure you want to return to previous page? [ Y = YES || other character = NO ] => ");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
			if (ans == 'Y')
				memberMain();
			else {
				userMenuBK(member);
			}
			break;

		default:
			inp = invalid(inp);
		}
	} while (inp == -1);
}
int invalid(int rtr) {
	printf("\nInvalid Input! Please Enter Again!\n");
	rtr = -1;
	return rtr;
}
void newBooking(Member* member) {
	int inp = 0;
	char ans;

	system("cls");
	printf("\n\n************ Booking Menu ************\n");
	printf("1. Booking by Schedule No\n");
	printf("2. Booking by Select Station\n");
	printf("3. Return to Previous Page\n");
	printf("**************************************\n");

	do {
		printf("Select your choice by enter an integer => ");
		scanf("%d", &inp);

		switch (inp) {

		case 1:
			bookBySch(member);
			break;

		case 2:
			bookByStation(member);
			break;

		case 3:
			printf("Do you sure you want to return to previous page? [ Y = YES || other character = NO ] => ");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
			if (ans == 'Y')
				userMenuBK(member);
			else {
				newBooking(member);
			}
			break;
		default:
			inp = invalid(inp);

		}
	} while (inp == -1);
}
void editPreBooking(Member* member) {

	int inp, h = 0, cond = 0, indexEdited, ticIndex;
	char ans, ans1, tkID[10];
	Invoice preBooking;

	Invoice* bookingSet = (Invoice*)malloc(1000 * sizeof(Invoice));
	if (bookingSet == NULL) {
		printf("Failed to allocate memory to booked structure!\n");
	}

	do {
		printf("\n\nEnter the Ticket ID that you wish to edit the details =>");
		rewind(stdin);
		scanf("%s", tkID);
		lowerToUpper(tkID, funcArrayLength(tkID));

		FILE* bkFile = fopen("bookingTic.txt", "r");
		if (bkFile == NULL) {
			printf("Error of open bookingTic.txt! \n");
			exit(-1);
		}
		else {
			while (fscanf(bkFile, "%[^|]|%[^|]|%[^|]|%d|%lf|%d/%d/%d\n",
				bookingSet[h].invoiceNo, bookingSet[h].invSchNo, bookingSet[h].membID, &bookingSet[h].ticketQtt, &bookingSet[h].totalAmount,
				&bookingSet[h].paymentDate.day, &bookingSet[h].paymentDate.month, &bookingSet[h].paymentDate.year) != EOF) {

				for (int j = 0; j < bookingSet[h].ticketQtt;j++) {
					fscanf(bkFile, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^\n]\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n",
						bookingSet[h].ticBook[j].ticketID, bookingSet[h].ticBook[j].psgName, bookingSet[h].ticBook[j].psgIC, bookingSet[h].ticBook[j].seatNo,
						&bookingSet[h].ticBook[j].coach, bookingSet[h].ticBook[j].remarks,
						bookingSet[h].ticBook[j].selectedMeal.mealName, bookingSet[h].ticBook[j].selectedMeal.mainFood,
						bookingSet[h].ticBook[j].selectedMeal.drinks, bookingSet[h].ticBook[j].selectedMeal.snacks, &bookingSet[h].ticBook[j].selectedMeal.mealPrice);

					if (strcmp(tkID, bookingSet[h].ticBook[j].ticketID) == 0) {

						printf("\n\n");
						printf("Ticket ID : %s\n", bookingSet[h].ticBook[j].ticketID);
						printf("Passenger Name : %s\n", bookingSet[h].ticBook[j].psgName);
						printf("Seat No : %s\n", bookingSet[h].ticBook[j].seatNo);
						printf("Meal Name : %s\n", bookingSet[h].ticBook[j].selectedMeal.mealName);
						printf("Remarks : %s\n\n", bookingSet[h].ticBook[j].remarks);
						cond = 1;
						ticIndex = j;
						indexEdited = h;

						printf("Do you sure want to edit this ticket? [ Y = YES || other character = NO ] => ");
						rewind(stdin);
						scanf("%c", &ans1);
						ans1 = toupper(ans1);
					}
				}
				h++;
			}

			if (cond != 1) {
				cond = invalid(cond);
			}
			else {
				if (ans1 == 'Y') {
					preBooking = bookingSet[indexEdited];
				}
				else
					userMenuBK(member);
			}
			fclose(bkFile);
		}
	} while (cond == -1);

	system("cls");
	printf("\n\n************ Edit Booking Menu ************\n");
	printf("1. Edit Meal\n");
	printf("2. Change Seat\n");
	printf("3. Cancel Ticket\n");
	printf("4. Return To Previous Page\n");
	printf("*********************************************\n");

	do {
		printf("Select your choice by enter an integer => ");
		scanf("%d", &inp);

		switch (inp) {

		case 1:
			bookingSet[indexEdited] = editMeal(&preBooking, ticIndex);
			break;

		case 2:
			bookingSet[indexEdited] = changeSeat(&preBooking, ticIndex);
			break;

		case 3:
			bookingSet[indexEdited] = cancelTicket(&preBooking, ticIndex);
			break;

		case 4:
			printf("Do you sure you want to return to previous page? [ Y = YES || other character = NO ] => ");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
			if (ans == 'Y')
				userMenuBK(member);
			else {
				editPreBooking(member);
			}
			break;
		default:
			inp = invalid(inp);

		}
	} while (inp == -1);

	if (bookingSet[indexEdited].ticketQtt == 0) {

		for (int af = indexEdited;af < h;af++) {
			bookingSet[af] = bookingSet[af + 1];
		}

		h -= 1;
	}

	// write the data that already edit into file

	FILE* bkFileW = fopen("bookingTic.txt", "w");
	if (bkFileW == NULL) {
		printf("Error of open bookingTic.txt! \n");
		exit(-1);
	}
	else {

		for (int k = 0;k < h;k++) {

			fprintf(bkFileW, "%s|%s|%s|%d|%.2f|%d/%d/%d\n",
				bookingSet[k].invoiceNo, bookingSet[k].invSchNo, bookingSet[k].membID, bookingSet[k].ticketQtt, bookingSet[k].totalAmount,
				bookingSet[k].paymentDate.day, bookingSet[k].paymentDate.month, bookingSet[k].paymentDate.year);

			for (int l = 0; l < bookingSet[k].ticketQtt;l++) {
				fprintf(bkFileW, "%s|%s|%s|%s|%c|%s\n%s|%s|%s|%s|%.2f\n",
					bookingSet[k].ticBook[l].ticketID, bookingSet[k].ticBook[l].psgName, bookingSet[k].ticBook[l].psgIC, bookingSet[k].ticBook[l].seatNo,
					bookingSet[k].ticBook[l].coach, bookingSet[k].ticBook[l].remarks,
					bookingSet[k].ticBook[l].selectedMeal.mealName, bookingSet[k].ticBook[l].selectedMeal.mainFood,
					bookingSet[k].ticBook[l].selectedMeal.drinks, bookingSet[k].ticBook[l].selectedMeal.snacks, bookingSet[k].ticBook[l].selectedMeal.mealPrice);
			}

		}

	}
	fclose(bkFileW);
	free(bookingSet);

	printf("Do you want to continue edit your ticket? [ Y = YES || other character = NO ] =>");
	rewind(stdin);
	scanf("%c", &ans1);
	ans1 = toupper(ans1);

	if (ans1 == 'Y') {
		editPreBooking(member);
	}
	else
		userMenuBK(member);
}
void viewPreBooking(Member* member) {

	system("cls");
	int h = 0, cond = 0;
	char vBKID[10], userInp;
	Invoice booked;
	Invoice* bookingSet = (Invoice*)malloc(5000 * sizeof(Invoice));
	if (bookingSet == NULL) {
		printf("Failed to allocate memory to booked structure!\n");
	}

	FILE* viewBK = fopen("bookingTic.txt", "r");
	if (viewBK == NULL) {
		printf("Error of open bookingTic.txt!\n");
		exit(-1);
	}
	else {

		while (fscanf(viewBK, "%[^|]|%[^|]|%[^|]|%d|%lf|%d/%d/%d\n",
			booked.invoiceNo, booked.invSchNo, booked.membID, &booked.ticketQtt, &booked.totalAmount,
			&booked.paymentDate.day, &booked.paymentDate.month, &booked.paymentDate.year) != EOF) {

			for (int j = 0; j < booked.ticketQtt;j++) {
				fscanf(viewBK, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^\n]\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n",
					booked.ticBook[j].ticketID, booked.ticBook[j].psgName, booked.ticBook[j].psgIC, booked.ticBook[j].seatNo,
					&booked.ticBook[j].coach, booked.ticBook[j].remarks,
					booked.ticBook[j].selectedMeal.mealName, booked.ticBook[j].selectedMeal.mainFood,
					booked.ticBook[j].selectedMeal.drinks, booked.ticBook[j].selectedMeal.snacks, &booked.ticBook[j].selectedMeal.mealPrice);
			}
			if (strcmp(member->memberID, booked.membID) == 0) {
				bookingSet[h] = booked;
				h++;
			}
		}
		fclose(viewBK);
		if (h == 0) {
			printf("\n\n******************************* Sorry. You haven't make any booking. *******************************\n\n");
		}
		else {

			printf("\n\n--------------------------------------- Previous Booking List ---------------------------------------\n\n");
			printf("%-13s%-12s%-17s%-15s%-10s\n", "Booking ID", "Schedule", "Ticket Quantity", "Payment Date", "Amount Pay");
			printf("%-13s%-12s%-17s%-15s%-10s\n", "**********", "********", "***************", "************", "**********");
			for (int p = 0;p < h;p++) {
				printf("%-13s%-12s%-17d%02d/%02d/%-11dRM%-.2lf\n", bookingSet[p].invoiceNo, bookingSet[p].invSchNo, bookingSet[p].ticketQtt,
					bookingSet[p].paymentDate.day, bookingSet[p].paymentDate.month, bookingSet[p].paymentDate.year, bookingSet[p].totalAmount);
			}
			printf("\n\n-----------------------------------------------------------------------------------------------------\n\n");
			do {
				printf("Enter the Booking ID that you wish to view =>");
				rewind(stdin);
				scanf("%s", vBKID);
				lowerToUpper(vBKID, funcArrayLength(vBKID));

				for (int q = 0;q < h;q++) {
					if (strcmp(vBKID, bookingSet[q].invoiceNo) == 0) {
						printf("Booking ID : %s\n", bookingSet[q].invoiceNo);
						printf("Schedule No : %s\n", bookingSet[q].invSchNo);
						printf("Number of Ticket : %d\n", bookingSet[q].ticketQtt);
						printf("Payment Date: %02d/%02d/%d\n", bookingSet[q].paymentDate.day, bookingSet[q].paymentDate.month, bookingSet[q].paymentDate.year);
						printf("Amount Pay : RM%.2lf\n", bookingSet[q].totalAmount);
						cond = 2;
						for (int r = 0;r < bookingSet[q].ticketQtt;r++) {
							printf("\n\nFor Ticket [%d] :\n", r + 1);
							printf("Ticket ID : %s\n", bookingSet[q].ticBook[r].ticketID);
							printf("Passenegr Name : %s\n", bookingSet[q].ticBook[r].psgName);
							printf("Passenger IC : %s\n", bookingSet[q].ticBook[r].psgIC);
							printf("Seat Number : %s\n", bookingSet[q].ticBook[r].seatNo);
							printf("Coach : %c\n\n", bookingSet[q].ticBook[r].coach);
							printf("Meal Name: %s\n", bookingSet[q].ticBook[r].selectedMeal.mealName);
							printf("Main Food : %s\n", bookingSet[q].ticBook[r].selectedMeal.mainFood);
							printf("Drink : %s\n", bookingSet[q].ticBook[r].selectedMeal.drinks);
							printf("Snack : %s\n\n", bookingSet[q].ticBook[r].selectedMeal.snacks);
							printf("Remarks : %s\n", bookingSet[q].ticBook[r].remarks);
						}
					}
				}
				if (cond != 2)
					cond = invalid(cond);
			} while (cond == -1);

			printf("\n\nDo you want to view other booking? [ Y = YES || other cahracter = NO ] => ");
			rewind(stdin);
			scanf("%c", &userInp);
			userInp = toupper(userInp);

			if (userInp == 'Y')
				viewPreBooking(member);
			else
				userMenuBK(member);

		}
	}
}
void bookBySch(Member* member) {

	TrainSchedule schedule;
	int cond = -1;
	char schNo[6], ans1;


	FILE* trnSch = fopen("trainSchedule.txt", "r");
	if (trnSch == NULL) {
		printf("\nError open file trainSchedule.txt! \n");
		exit(-1);
	}

	do {
		printf("\nEnter the Schedule No =>");
		scanf("%s", schNo);
		lowerToUpper(schNo, funcArrayLength(schNo));
		rewind(stdin);

		while ((cond != 0) && (fscanf(trnSch, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
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
			&schedule.status) != EOF)) {

			if (strcmp(schNo, schedule.scheduleNo) == 0) {

				printf("\n\nSchedule ID : %s\n", schedule.scheduleNo);
				printf("Train ID : %s\n", schedule.trainID);
				printf("Price for One Seat : RM%.2f\n\n", schedule.schTrnPrice);
				printf("Departure Station : %s\n", schedule.departureStation);
				printf("Departure Date :%02d/%02d/%02d\n", schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year);
				printf("Departure Time : %02d:%02d\n\n", schedule.departureTime.hours, schedule.departureTime.minutes);
				printf("Arrival Station : %s\n", schedule.arrivalStation);
				printf("Arrival Date : %02d/%02d/%02d\n", schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year);
				printf("Arrival Time : %02d:%02d\n\n", schedule.arrivalTime.hours, schedule.arrivalTime.minutes);

				printf("Do you want to book this train? [ Y = Yes | N = No ] => ");
				rewind(stdin);
				scanf("%c", &ans1);

				cond = 0;
			}

		}
		if (cond == -1) {
			cond = invalid(cond);
			fseek(trnSch, 0, SEEK_SET);
		}
	} while (cond == -1);
	fclose(trnSch);

	if (toupper(ans1) == 'Y') {
		bookingTicket(&schedule, member);
	}
	else {
		newBooking(member);
	}
}
void bookByStation(Member* member) {

	char deptStation[30], arrStation[30], schNo[6], ans1;
	int cond = -1, countSCH = 1;
	TrainSchedule schedule;

	FILE* trnSch = fopen("trainSchedule.txt", "r");
	if (trnSch == NULL) {
		printf("\nError open file trainSchedule.txt! \n");
		exit(-1);
	}

	do {
		printf("\nEnter your departure station =>");
		rewind(stdin);
		scanf("%[^\n]", deptStation);
		lowerToUpper(deptStation, funcArrayLength(deptStation));

		printf("\nEnter your arrival station =>");
		rewind(stdin);
		scanf("%[^\n]", arrStation);
		lowerToUpper(arrStation, funcArrayLength(arrStation));

		while ((fscanf(trnSch, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
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
			&schedule.status) != EOF)) {

			if ((strcmp(deptStation, schedule.departureStation) == 0) && (strcmp(arrStation, schedule.arrivalStation) == 0)) {

				printf("\n\n\nSchedule [%d] :", countSCH);
				printf("\n\nSchedule ID : %s\n", schedule.scheduleNo);
				printf("Train ID : %s\n", schedule.trainID);
				printf("Price for One Seat : RM%.2f\n\n", schedule.schTrnPrice);
				printf("Departure Station : %s\n", schedule.departureStation);
				printf("Departure Date :%02d/%02d/%02d\n", schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year);
				printf("Departure Time : %02d:%02d\n\n", schedule.departureTime.hours, schedule.departureTime.minutes);
				printf("Arrival Station : %s\n", schedule.arrivalStation);
				printf("Arrival Date : %02d/%02d/%02d\n", schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year);
				printf("Arrival Time : %02d:%02d\n\n", schedule.arrivalTime.hours, schedule.arrivalTime.minutes);
				countSCH++;
				cond = 0;
			}
		}

		if (cond == -1) {
			cond = invalid(cond);
			fseek(trnSch, 0, SEEK_SET);
		}
		else {

			do {
				printf("Enter the Schedule No that you want to book => ");
				rewind(stdin);
				scanf("%s", schNo);
				lowerToUpper(schNo, funcArrayLength(schNo));
				cond = -1;
				fseek(trnSch, 0, SEEK_SET);

				while ((cond != 0) && (fscanf(trnSch, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
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
					&schedule.status) != EOF)) {

					if (strcmp(schNo, schedule.scheduleNo) == 0) {

						printf("\n\nSchedule ID : %s\n", schedule.scheduleNo);
						printf("Train ID : %s\n", schedule.trainID);
						printf("Price for One Seat : RM%.2f\n\n", schedule.schTrnPrice);
						printf("Departure Station : %s\n", schedule.departureStation);
						printf("Departure Date :%02d/%02d/%02d\n", schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year);
						printf("Departure Time : %02d:%02d\n\n", schedule.departureTime.hours, schedule.departureTime.minutes);
						printf("Arrival Station : %s\n", schedule.arrivalStation);
						printf("Arrival Date : %02d/%02d/%02d\n", schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year);
						printf("Arrival Time : %02d:%02d\n\n", schedule.arrivalTime.hours, schedule.arrivalTime.minutes);

						printf("Do you want to book this train? [ Y = Yes | N = No ] => ");
						rewind(stdin);
						scanf("%c", &ans1);
						cond = 0;
					}
				}
				if (cond == -1) {
					cond = invalid(cond);
				}
			} while (cond == -1);

		}
	} while (cond == -1);
	fclose(trnSch);

	if (toupper(ans1) == 'Y') {
		bookingTicket(&schedule, member);
	}
	else {
		newBooking(member);
	}

}
int payByCreditCard(double invAmt) {
	char cc[20];
	double payAmt;

	// Input validation loop
	do {
		printf("\nEnter your credit card number => ");
		rewind(stdin);
		scanf("%s", cc);

		printf("Enter the amount that you want to pay => ");
		scanf("%lf", &payAmt);

		if (atof(cc) < 0 || payAmt < 0) {
			printf("*** Invalid input. Credit card number and payment amount must be positive.\n\n");
		}
		else if (payAmt != invAmt) {
			printf("*** Payment amount does not match invoice amount.\n\n");
		}

	} while (atof(cc) < 0 || payAmt < 0 || payAmt != invAmt);

	// Calculate checksum using Luhn algorithm
	int sum = 0;
	int digit_count = 0;
	for (int i = strlen(cc) - 1; i >= 0; i--) {
		int digit = cc[i] - '0'; // Convert character to integer
		digit_count++;

		if (digit_count % 2 == 0) {
			digit *= 2;
			if (digit > 9) {
				digit -= 9;
			}
		}

		sum += digit;
	}

	// Check if the card is valid
	if (sum % 10 == 0) {
		int first_digit = cc[0] - '0';
		if ((first_digit == 3 && (cc[1] == '4' || cc[1] == '7'))) { // Check for AMEX
			printf("AMEX - Successfully Paid!\n");
		}
		else if ((first_digit == 4)) { // Check for VISA
			printf("VISA - Successfully Paid!\n");
		}
		else if ((first_digit == 5)) { // Check for MASTERCARD
			printf("MASTERCARD - Successfully Paid!\n");
		}
		else {
			printf("Payment Failed - Unknown Card Type\n");
			return 0;
		}
		return 1; // Successful payment
	}
	else {
		printf("Payment Failed - Invalid Card Number\n");
		return 0; // Failed payment
	}
}
void storeToBooking(Invoice* invoice) {

	FILE* BK = fopen("bookingTic.txt", "a");
	if (BK == NULL) {
		printf("Error for open bookingTic.txt!\n");
		exit(-1);
	}
	else {
		currentDate(invoice);
		fprintf(BK, "%s|%s|%s|%d|%lf|%d/%d/%d\n",
			invoice->invoiceNo, invoice->invSchNo, invoice->membID, invoice->ticketQtt, invoice->totalAmount,
			invoice->paymentDate.day, invoice->paymentDate.month, invoice->paymentDate.year);

		for (int g = 0;g < invoice->ticketQtt;g++) {
			fprintf(BK, "%s|%s|%s|%s|%c|%s\n%s|%s|%s|%s|%.2f\n",
				invoice->ticBook[g].ticketID, invoice->ticBook[g].psgName, invoice->ticBook[g].psgIC, invoice->ticBook[g].seatNo,
				invoice->ticBook[g].coach, invoice->ticBook[g].remarks,
				invoice->ticBook[g].selectedMeal.mealName, invoice->ticBook[g].selectedMeal.mainFood,
				invoice->ticBook[g].selectedMeal.drinks, invoice->ticBook[g].selectedMeal.snacks, invoice->ticBook[g].selectedMeal.mealPrice);
		}
	}
	fclose(BK);

}
void bookingTicket(TrainSchedule* schedule, Member* member) {

	system("cls");

	Invoice invoices;
	SeatDisplay seatTB[1000];
	char selectMeal[7], ans, userInp;
	double totalBK = 0;
	int countIV = 0, countBK = 0, lastTicID, indexSch, condition = 1, condi = 1;

	Invoice* booked = (Invoice*)malloc(1000 * sizeof(Invoice));
	if (booked == NULL) {
		printf("Failed to allocate memory to booked structure!\n");
	}

	FILE* seatFile = fopen("seatList.txt", "r");
	if (seatFile == NULL) {
		printf("Error of open seatList.txt!\n");
		exit(-1);
	}
	else {
		do {
			strcpy(invoices.invSchNo, schedule->scheduleNo);
			printf("\nEnter the seat quantity => ");
			scanf("%d", &invoices.ticketQtt);

			if (isdigit(invoices.ticketQtt) != 0)
				condi = invalid(condi);
		} while (condi == -1);

		for (int i = 0; i < invoices.ticketQtt; i++) {

			int cond = 0, condt = 0, countt = 0;
			fseek(seatFile, SEEK_SET, 0);
			while ((fscanf(seatFile, "%[^\n]\n", seatTB[countt].schNo) != EOF)) {
				for (int z = 0;z < 119;z++) {
					fscanf(seatFile, "%[^|]|%c\n", seatTB[countt].seat[z].seatNo, &seatTB[countt].seat[z].status);
				}
				fscanf(seatFile, "%[^|]|%c\n\n\n", seatTB[countt].seat[119].seatNo, &seatTB[countt].seat[119].status);
				if (strcmp(schedule->scheduleNo, seatTB[countt].schNo) == 0) {
					indexSch = countt;
				}
				countt++;
			}
			fclose(seatFile);
			displaySeat(&seatTB[indexSch]);

			do {
				printf("\n\nFor [%d] seat :\n\n", i + 1);
				printf("Enter seat number => ");
				rewind(stdin);
				scanf("%s", invoices.ticBook[i].seatNo);
				lowerToUpper(invoices.ticBook[i].seatNo, funcArrayLength(invoices.ticBook[i].seatNo));

				for (int ab = 0;ab < 120;ab++) {

					if (strcmp(seatTB[indexSch].seat[ab].seatNo, invoices.ticBook[i].seatNo) == 0) {
						if (seatTB[indexSch].seat[ab].status == 'A') {
							seatTB[indexSch].seat[ab].status = 'B';
							condt = 1;
						}
					}
				}
				if (condt != 1) {
					condt = invalid(condt);
				}
			} while (condt == -1);

			FILE* seatFile = fopen("seatList.txt", "w");
			if (seatFile == NULL) {
				printf("Error of open seatList.txt!\n");
				exit(-1);
			}
			else {
				for (int ac = 0;ac < countt;ac++) {
					fprintf(seatFile, "%s\n", seatTB[ac].schNo);
					for (int ad = 0;ad < 119;ad++) {
						fprintf(seatFile, "%s|%c\n", seatTB[ac].seat[ad].seatNo, seatTB[ac].seat[ad].status);
					}
					fprintf(seatFile, "%s|%c\n\n\n", seatTB[ac].seat[119].seatNo, seatTB[ac].seat[119].status);

				}
			}
			fclose(seatFile);


			printf("\nEnter passenger name => ");
			rewind(stdin);
			scanf("%[^\n]", invoices.ticBook[i].psgName);
			lowerToUpper(invoices.ticBook[i].psgName, funcArrayLength(invoices.ticBook[i].psgName));

			do {
				condition = 0;
				printf("\nEnter passenger IC number [ XXXXXX-XX-XXXX ]=>");
				rewind(stdin);
				scanf("%s", invoices.ticBook[i].psgIC);
				if (funcArrayLength(invoices.ticBook[i].psgIC) != 14)
					condition = invalid(condition);
			} while (condition == -1);

			printMeal(schedule);

			do {
				printf("\nSelect a meal by enter the meal name ");
				printf("\n------ [ NULL ] for don't want the meal ------ ");
				printf("\nMeal Name => ");
				rewind(stdin);
				scanf("%[^\n]", selectMeal);
				lowerToUpper(selectMeal, funcArrayLength(selectMeal));

				if (strcmp(selectMeal, "NULL") == 0) {
					strcpy(invoices.ticBook[i].selectedMeal.mealName, "NULL");
					strcpy(invoices.ticBook[i].selectedMeal.mainFood, "NULL");
					strcpy(invoices.ticBook[i].selectedMeal.drinks, "NULL");
					strcpy(invoices.ticBook[i].selectedMeal.snacks, "NULL");
					invoices.ticBook[i].selectedMeal.mealPrice = 0;
					cond = 2;
				}
				else {
					for (int b = 0; b < 3;b++) {
						if (strcmp(selectMeal, schedule->mealList[b].mealName) == 0) {
							invoices.ticBook[i].selectedMeal = schedule->mealList[b];
							cond = 2;
						}
					}
					if (cond != 2) {
						cond = invalid(cond);
					}
				}
			} while (cond != 2);

			printf("Have any remarks ? => ");
			rewind(stdin);
			scanf("%[^\n]", invoices.ticBook[i].remarks);


		}

		//assign ticket id and invoice no for this booking
		// read from booking.txt file to calculate how many ticket exist already

		FILE* bkTic = fopen("bookingTic.txt", "r");
		if (bkTic == NULL) {
			printf("\n\nError of open booking.txt file!\n");
			exit(-1);
		}
		else {
			while (fscanf(bkTic, "%[^|]|%[^|]|%[^|]|%d|%lf|%d/%d/%d\n",
				booked[countIV].invoiceNo, booked[countIV].invSchNo, booked[countIV].membID, &booked[countIV].ticketQtt, &booked[countIV].totalAmount,
				&booked[countIV].paymentDate.day, &booked[countIV].paymentDate.month, &booked[countIV].paymentDate.year) != EOF) {

				for (countBK = 0; countBK < booked[countIV].ticketQtt;countBK++) {
					fscanf(bkTic, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^\n]\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n",
						booked[countIV].ticBook[countBK].ticketID, booked[countIV].ticBook[countBK].psgName, booked[countIV].ticBook[countBK].psgIC, booked[countIV].ticBook[countBK].seatNo,
						&booked[countIV].ticBook[countBK].coach, booked[countIV].ticBook[countBK].remarks,
						booked[countIV].ticBook[countBK].selectedMeal.mealName, booked[countIV].ticBook[countBK].selectedMeal.mainFood,
						booked[countIV].ticBook[countBK].selectedMeal.drinks, booked[countIV].ticBook[countBK].selectedMeal.snacks, &booked[countIV].ticBook[countBK].selectedMeal.mealPrice);
				}
				countIV++;
			}

			sprintf(invoices.invoiceNo, "IV-%06d", atoi(booked[countIV - 1].invoiceNo + 3) + 1); // assign invoice number
			strcpy(invoices.membID, member->memberID); // assign member id
			lastTicID = atoi(booked[countIV - 1].ticBook[countBK - 1].ticketID + 3);

			//assign ticket id and coach
			for (int e = 0;e < invoices.ticketQtt;e++) {

				sprintf(invoices.ticBook[e].ticketID, "TK-%06d", lastTicID + e + 1);
				countBK++;

				//assign coach
				invoices.ticBook[e].coach = invoices.ticBook[e].seatNo[0];

			}
			fclose(bkTic);
			free(booked);

			system("cls");

			printInvoice(schedule, member, &invoices);

			printf("Do you confirm your booking? [ Y = YES || other character = NO ] => ");
			rewind(stdin);
			scanf("%c", &ans);

			if (toupper(ans) == 'Y') {
				if (payByCreditCard(invoices.totalAmount) != 0) {
					storeToBooking(&invoices);
				}
				else {
					printf("\n\n******************** Failed to make payment. Please proceed again! ********************\n");
					printf("******************************* Press Enter To Continue *******************************\n\n");
					rewind(stdin);
					scanf("%[^\n]", &ans);
					newBooking(member);
				}
			}
			else {
				newBooking(member);
			}
		}
	}
	printf("\n\nDo you want to continue booking ticket? [ Y = YES || other cahracter = NO ] => ");
	rewind(stdin);
	scanf("%c", &userInp);
	userInp = toupper(userInp);

	if (userInp == 'Y')
		newBooking(member);
	else
		userMenuBK(member);
}
void printMeal(TrainSchedule* schedule) {

	printf("\n\n****************************** Available Meal ******************************\n\n");
	printf("%-14s%-25s%-25s%-25s%-8s\n", "Meal Name", "Main Food", "Beverage", "Snack", "Price");
	printf("%-14s%-25s%-25s%-25s%-8s\n", "*********", "*********", "********", "*****", "*****");

	for (int a = 0;a < 3;a++) {
		printf("%-14s%-25s%-25s%-25s%-8.2f\n", schedule->mealList[a].mealName, schedule->mealList[a].mainFood, schedule->mealList[a].drinks, schedule->mealList[a].snacks, schedule->mealList[a].mealPrice);
	}

	printf("\n\n# Only available meal for this train schedule will be displayed.\n");
	printf("# For full meal list please visit our website --- www.ThaikulaTrainCompany.com.my ---. \n\n");
}
void printInvoice(TrainSchedule* schedule, Member* member, Invoice* invoices) {

	double subtotalBK;
	invoices->totalAmount = 0;

	printf("\n\n============================================== Invoice ==============================================\n\n");
	printf("Invoice NO. : %s\n", invoices->invoiceNo);
	printf("Schedule NO. : %s \t Train ID: %s\n", invoices->invSchNo, schedule->trainID);
	printf("Member ID : %s \t Member Name: %s\n", invoices->membID, member->memberName);
	printf("Number of Seat : %d\n\n", invoices->ticketQtt);
	printf("%-11s%-25s%-18s%-8s%-7s%-13s%-10s\n", "Ticket ID", "Name", "Passenger IC", "Seat", "Coach", "Meal Name", "Subtotal");
	printf("%-11s%-25s%-18s%-8s%-7s%-13s%-10s\n", "*********", "****", "************", "****", "*****", "*********", "********");

	for (int f = 0; f < invoices->ticketQtt;f++) {
		subtotalBK = invoices->ticBook[f].selectedMeal.mealPrice + schedule->schTrnPrice;
		invoices->totalAmount = invoices->totalAmount + subtotalBK;
		printf("%-11s%-25s%-18s%-8s%-7c%-13sRM%.2f\n", invoices->ticBook[f].ticketID, invoices->ticBook[f].psgName, invoices->ticBook[f].psgIC, invoices->ticBook[f].seatNo, invoices->ticBook[f].coach, invoices->ticBook[f].selectedMeal.mealName, subtotalBK);
	}

	printf("\n\n%79s : RM%.2f", "Total", invoices->totalAmount);
	printf("\n\n\nRemarks:\n");

	for (int g = 0;g < invoices->ticketQtt;g++) {

		printf("[ %s ] : %s \n", invoices->ticBook[g].ticketID, invoices->ticBook[g].remarks);

	}

	printf("\n\n=======================================================================================================\n\n\n");
}
Invoice editMeal(Invoice* preBK, int ticInd) {

	TrainSchedule schedule;
	char inpChangeM, newMeal[7];
	int cond;
	double refundAddAmt, diffP;
	system("cls");
	displayEditTicket(preBK, ticInd);
	printf("Do you sure you want to change your meal? [ Y = YES || other character = NO ] => ");
	rewind(stdin);
	scanf("%c", &inpChangeM);
	inpChangeM = toupper(inpChangeM);

	if (inpChangeM == 'Y') {

		FILE* trSch = fopen("trainSchedule.txt", "r");
		if (trSch == NULL) {
			printf("\nError of open trainSchedule.txt!\n");
			exit(-1);
		}
		else {
			do {
				cond = 1;
				while ((cond != 0) && (fscanf(trSch, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
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
					&schedule.status) != EOF)) {

					if (strcmp(preBK->invSchNo, schedule.scheduleNo) == 0) {
						printMeal(&schedule);
						cond = 0;
					}
				}
				printf("Enter new meal name => ");
				rewind(stdin);
				scanf("%[^\n]", newMeal);
				lowerToUpper(newMeal, funcArrayLength(newMeal));

				for (int o = 0;o < 3;o++) {

					if (strcmp(newMeal, schedule.mealList[o].mealName) == 0) {

						if (schedule.mealList[o].mealPrice > preBK->ticBook[ticInd].selectedMeal.mealPrice) {

							refundAddAmt = schedule.mealList[o].mealPrice - preBK->ticBook[ticInd].selectedMeal.mealPrice;
							refundAddAmt = round(refundAddAmt * 100) / 100; // Round to two decimal places

							printf("\n\nDifferent between the previous meal price and the new meal price is => RM%.2lf", refundAddAmt);

							if (payByCreditCard(refundAddAmt) != 1) {
								refundAddAmt = invalid(refundAddAmt);
							}
							else {
								diffP = preBK->totalAmount + (round(schedule.mealList[o].mealPrice - preBK->ticBook[ticInd].selectedMeal.mealPrice) * 100 / 100);
							}

						}
						else {
							printf("\nThe difference of the price already credit into your bank!\n");
							refundAddAmt = 1;
							diffP = preBK->totalAmount - preBK->ticBook[ticInd].selectedMeal.mealPrice + schedule.mealList[o].mealPrice;
						}
						if (refundAddAmt != -1) {
							strcpy(preBK->ticBook[ticInd].selectedMeal.mealName, schedule.mealList[o].mealName);
							strcpy(preBK->ticBook[ticInd].selectedMeal.mainFood, schedule.mealList[o].mainFood);
							strcpy(preBK->ticBook[ticInd].selectedMeal.drinks, schedule.mealList[o].drinks);
							strcpy(preBK->ticBook[ticInd].selectedMeal.snacks, schedule.mealList[o].snacks);
							preBK->ticBook[ticInd].selectedMeal.mealPrice = schedule.mealList[o].mealPrice;
							preBK->totalAmount = diffP;
						}
						cond = 1;
					}
				}
				if (cond != 1)
					cond = invalid(cond);

			} while (cond == -1);
		}
		fclose(trSch);
		if (refundAddAmt != -1)
			printf("\n\n*********************** Successfully update your Ticket Details. ***********************\n");
	}
	return *preBK;

}
Invoice changeSeat(Invoice* preBK, int ticInd) {

	SeatDisplay* seatSet = (SeatDisplay*)malloc(1000 * sizeof(SeatDisplay));
	char inpChangeS, newSeat[4], rSchID[6];
	int cond = 0, seatIndex = 0, indexEdited, count = 0, originalSeat;

	displayEditTicket(preBK, ticInd);
	printf("Do you sure you want to change your seat? [ Y = YES || other character = NO ] => ");
	rewind(stdin);
	scanf("%c", &inpChangeS);
	inpChangeS = toupper(inpChangeS);

	if (inpChangeS == 'Y') {

		FILE* changeS = fopen("seatList.txt", "r");
		if (changeS == NULL) {
			printf("Error for open seatList.txt!\n");
			exit(-1);
		}
		else {
			while (fscanf(changeS, "%[^\n]\n", seatSet[seatIndex].schNo) != EOF) {

				for (int s = 0;s < 120;s++) {
					if (s != 119)
						fscanf(changeS, "%[^|]|%c\n", seatSet[seatIndex].seat[s].seatNo, &seatSet[seatIndex].seat[s].status);
					else
						fscanf(changeS, "%[^|]|%c\n\n\n", seatSet[seatIndex].seat[s].seatNo, &seatSet[seatIndex].seat[s].status);
				}
				if (strcmp(seatSet[seatIndex].schNo, preBK->invSchNo) == 0) {
					indexEdited = seatIndex;
				}
				count++;
				seatIndex++;
			}
			fclose(changeS);

			do {
				displaySeat(&seatSet[indexEdited]);
				printf("\n\nEnter new seat number [ XXX = return to previous page ]=> ");
				rewind(stdin);
				scanf("%s", newSeat);
				lowerToUpper(newSeat, funcArrayLength(newSeat));

				if (strcmp(newSeat, "XXX") != 0) {

					for (int ag = 0;ag < 120;ag++) {
						if (strcmp(preBK->ticBook[ticInd].seatNo, seatSet[indexEdited].seat[ag].seatNo) == 0) {
							originalSeat = ag;
						}
					}

					for (int v = 0;v < 120;v++) {
						if (strcmp(newSeat, seatSet[indexEdited].seat[v].seatNo) == 0) {
							if (seatSet[indexEdited].seat[v].status == 'A') {
								strcpy(preBK->ticBook[ticInd].seatNo, newSeat);
								preBK->ticBook[ticInd].coach = preBK->ticBook[ticInd].seatNo[0];
								printf("\n\n*********************** Successfully update your Ticket Details. ***********************\n");
								seatSet[indexEdited].seat[v].status = 'B';
								seatSet[indexEdited].seat[originalSeat].status = 'A';

							}
							else {
								printf("\nThis seat is already booked! Please choose again! \n");
								cond = -1;
							}
						}
					}
				}

			} while (cond == -1 && (strcmp(newSeat, "XXX") != 0));

			FILE* changeS = fopen("seatList.txt", "w");
			if (changeS == NULL) {
				printf("Error for open seatList.txt!\n");
				exit(-1);
			}
			else {
				for (int w = 0;w < count;w++) {

					fprintf(changeS, "%s\n", seatSet[w].schNo);
					for (int x = 0; x < 120;x++) {
						if (x != 119)
							fprintf(changeS, "%s|%c\n", seatSet[w].seat[x].seatNo, seatSet[w].seat[x].status);
						else
							fprintf(changeS, "%s|%c\n\n\n", seatSet[w].seat[x].seatNo, seatSet[w].seat[x].status);
					}
				}
			}

			fclose(changeS);
			free(seatSet);
		}
		return *preBK;
	}
}
Invoice cancelTicket(Invoice* preBK, int ticInd) {

	char inpCancel;
	int count = 0, seatIndex = 0, indexEdited;
	SeatDisplay* seatSet = (SeatDisplay*)malloc(1000 * sizeof(SeatDisplay));
	displayEditTicket(preBK, ticInd);
	printf("Do you sure you want to cancel? [ Y = YES || other character = NO ] => ");
	rewind(stdin);
	scanf("%c", &inpCancel);
	inpCancel = toupper(inpCancel);

	if (inpCancel == 'Y') {

		for (int n = ticInd; n < preBK->ticketQtt - 1;n++) {
			preBK->ticBook[n] = preBK->ticBook[n + 1];
		}
		preBK->ticketQtt = preBK->ticketQtt - 1;

		FILE* changeS = fopen("seatList.txt", "r");
		if (changeS == NULL) {
			printf("Error for open seatList.txt!\n");
			exit(-1);
		}
		else {
			while (fscanf(changeS, "%[^\n]\n", seatSet[seatIndex].schNo) != EOF) {

				for (int s = 0;s < 120;s++) {
					if (s != 119)
						fscanf(changeS, "%[^|]|%c\n", seatSet[seatIndex].seat[s].seatNo, &seatSet[seatIndex].seat[s].status);
					else
						fscanf(changeS, "%[^|]|%c\n\n\n", seatSet[seatIndex].seat[s].seatNo, &seatSet[seatIndex].seat[s].status);
				}
				if (strcmp(seatSet[seatIndex].schNo, preBK->invSchNo) == 0) {
					indexEdited = seatIndex;
				}
				count++;
				seatIndex++;
			}
			fclose(changeS);

			for (int ah = 0;ah < count;ah++) {
				for (int ai = 0;ai < 120;ai++) {
					if (strcmp(preBK->ticBook[ticInd].seatNo, seatSet[ah].seat[ai].seatNo) == 0) {
						seatSet[ah].seat[ai].status = 'A';
					}
				}

			}

			FILE* changeS = fopen("seatList.txt", "w");
			if (changeS == NULL) {
				printf("Error for open seatList.txt!\n");
				exit(-1);
			}
			else {
				for (int w = 0;w < count;w++) {

					fprintf(changeS, "%s\n", seatSet[w].schNo);
					for (int x = 0; x < 120;x++) {
						if (x != 119)
							fprintf(changeS, "%s|%c\n", seatSet[w].seat[x].seatNo, seatSet[w].seat[x].status);
						else
							fprintf(changeS, "%s|%c\n\n\n", seatSet[w].seat[x].seatNo, seatSet[w].seat[x].status);
					}
				}
			}
			fclose(changeS);
			free(seatSet);

			printf("\n\n*********************** Successfully update your Ticket Details. ***********************\n");
		}
	}
	return *preBK;
}
void displayEditTicket(Invoice* preBK, int ticInd) {

	printf("\n\n");
	printf("----------------------- Here is the Ticket you wish to Cancel / Edit -----------------------\n\n");
	printf("Ticket ID : %s\n", preBK->ticBook[ticInd].ticketID);
	printf("Passenger Name : %s\n", preBK->ticBook[ticInd].psgName);
	printf("Seat No : %s\n", preBK->ticBook[ticInd].seatNo);
	printf("Meal Name : %s\n", preBK->ticBook[ticInd].selectedMeal.mealName);
	printf("Remarks : %s\n\n", preBK->ticBook[ticInd].remarks);
	printf("--------------------------------------------------------------------------------------------\n\n");

}
void staffMenuBK() {
	int inp = 0;
	char ans;

	system("cls");
	printf("\n\n************ Staff Menu ************\n");
	printf("1. View Train Booking Status\n");
	printf("2. Generate Report\n");
	printf("3. Return To Previous Page\n");
	printf("************************************\n");

	do {
		printf("Select your choice by enter an integer => ");
		scanf("%d", &inp);

		switch (inp) {

		case 1:
			viewTrnBookingStatus();
			break;

		case 2:
			generateReportBK();
			break;

		case 3:
			printf("Do you sure you want to return to previous page? [ Y = YES || other character = NO ] => ");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
			if (ans == 'Y')
				main();
			else {
				staffMenuBK();
			}
			break;

		default:
			inp = invalid(inp);

		}
	} while (inp == -1);

}
void viewTrnBookingStatus() {

	SeatDisplay seatT;
	char schID[6], userInp;
	int cond = 0;
	system("cls");

	FILE* vBkStatus = fopen("seatList.txt", "r");
	if (vBkStatus == NULL) {
		printf("Error of open seatList.txt!\n");
		exit(-1);
	}
	else {
		do {
			printf("\n\nEnter Schedule Number to view it booking status [ XXX = Exit this page ]=> ");
			rewind(stdin);
			scanf("%s", schID);
			lowerToUpper(schID, funcArrayLength(schID));

			while ((cond != 1) && (fscanf(vBkStatus, "%[^\n]\n", seatT.schNo) != EOF)) {
				for (int y = 0;y < 120;y++) {
					fscanf(vBkStatus, "%[^|]|%c\n", seatT.seat[y].seatNo, &seatT.seat[y].status);
				}
				if (strcmp(schID, seatT.schNo) == 0)
					cond = 1;
			}
			if (strcmp(schID, "XXX") != 0)
				displaySeat(&seatT);
		} while (cond != 1 && (strcmp(schID, "XXX") != 0));

		printf("\n\nDo you want to view other booking? [ Y = YES || other cahracter = NO ] => ");
		rewind(stdin);
		scanf("%c", &userInp);
		userInp = toupper(userInp);

		if (userInp == 'Y')
			viewTrnBookingStatus();
		else
			staffMenuBK();
	}
	fclose(vBkStatus);
}
void generateReportBK() {
	int inp = 0;
	char ans;

	system("cls");
	printf("\n\n************ Generate Report ************\n");
	printf("1. Top Meals Ordered by Customer\n");
	printf("2. Occupancy Rate of the Train\n");
	printf("3. Return To Previous Page\n");
	printf("*******************************************\n");

	do {
		printf("Select your choice by enter an integer => ");
		scanf("%d", &inp);

		switch (inp) {

		case 1:
			topMealR();
			break;

		case 2:
			trainOccupancyRate();
			break;

		case 3:
			printf("Do you sure you want to return to previous page? [ Y = YES || other character = NO ] => ");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
			if (ans == 'Y')
				staffMenuBK();
			else {
				generateReportBK();
			}
			break;

		default:
			inp = invalid(inp);
		}
	} while (inp == -1);
}
void topMealR() {

	system("cls");
	int countMeal = 0, countT = 0;
	char topMeal[7], userInp;
	Date dateNow, sdt, edt;
	Invoice bookMeal;
	struct NumMeal {
		int countOfMeal;
		Meal mealL;
	}mealList[1000];

	/* Calulate current Date */
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

	printf("From what date [dd/mm/yyyy] => ");
	rewind(stdin);
	scanf("%d/%d/%d", &sdt.day, &sdt.month, &sdt.year);
	printf("To what date [dd/mm/yyyy] => ");
	rewind(stdin);
	scanf("%d/%d/%d", &edt.day, &edt.month, &edt.year);


	FILE* mealL = fopen("mealList.txt", "r");
	if (mealL == NULL) {
		printf("Error of open mealList.txt!\n");
		exit(-1);
	}
	else {
		while (fscanf(mealL, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n",
			mealList[countMeal].mealL.mealName, mealList[countMeal].mealL.mainFood, mealList[countMeal].mealL.drinks,
			mealList[countMeal].mealL.snacks, &mealList[countMeal].mealL.mealPrice) != EOF) {

			mealList[countMeal].countOfMeal = 0;
			countMeal++;
		}
		fclose(mealL);

		FILE* bkMeal = fopen("bookingTic.txt", "r");
		if (bkMeal == NULL) {
			printf("Error of open booking.txt!\n");
			exit(-1);
		}
		else {
			while (fscanf(bkMeal, "%[^|]|%[^|]|%[^|]|%d|%lf|%d/%d/%d\n",
				bookMeal.invoiceNo, bookMeal.invSchNo, bookMeal.membID, &bookMeal.ticketQtt, &bookMeal.totalAmount,
				&bookMeal.paymentDate.day, &bookMeal.paymentDate.month, &bookMeal.paymentDate.year) != EOF) {

				for (int ae = 0; ae < bookMeal.ticketQtt;ae++) {
					fscanf(bkMeal, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^\n]\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n",
						bookMeal.ticBook[ae].ticketID, bookMeal.ticBook[ae].psgName, bookMeal.ticBook[ae].psgIC, bookMeal.ticBook[ae].seatNo,
						&bookMeal.ticBook[ae].coach, bookMeal.ticBook[ae].remarks,
						bookMeal.ticBook[ae].selectedMeal.mealName, bookMeal.ticBook[ae].selectedMeal.mainFood,
						bookMeal.ticBook[ae].selectedMeal.drinks, bookMeal.ticBook[ae].selectedMeal.snacks, &bookMeal.ticBook[ae].selectedMeal.mealPrice);

					for (int af = 0;af < countMeal; af++) {
						if ((compareDates(sdt, bookMeal.paymentDate) <= 0) && (compareDates(edt, bookMeal.paymentDate) >= 0) && (strcmp(bookMeal.ticBook[ae].selectedMeal.mealName, mealList[af].mealL.mealName) == 0)) {
							mealList[af].countOfMeal++;
						}
					}

				}

			}
			fclose(bkMeal);

			printf("\n\n----------------------------------- Top Popular Meals -----------------------------------\n\n");
			printf("Date : %02d/%02d/%d\n", dateNow.day, dateNow.month, dateNow.year);
			printf("From : %02d/%02d/%d \t To: %02d/%02d/%d\n\n", sdt.day, sdt.month, sdt.year, edt.day, edt.month, edt.year);
			printf("%-15s%-13s\n", "Meal Name", "Count Of Meal");
			printf("%-15s%-13s\n", "*********", "*************");
			for (int af = 0;af < countMeal;af++) {
				printf("%-15s%-13d\n", mealList[af].mealL.mealName, mealList[af].countOfMeal);

				if (mealList[af].countOfMeal > countT) {
					strcpy(topMeal, mealList[af].mealL.mealName);
					countT = mealList[af].countOfMeal;
				}

			}
			printf("\n\nThe most popular meal is => %s", topMeal);
			printf("\n\n------------------------------------------------------------------------------------------\n\n");
		}
	}
	printf("\n\nDo you want to continue generate report? [ Y = YES || other cahracter = NO ] => ");
	rewind(stdin);
	scanf("%c", &userInp);
	userInp = toupper(userInp);

	if (userInp == 'Y')
		topMealR();
	else
		staffMenuBK();
}
void trainOccupancyRate() {

	system("cls");
	int countS = 0, countT = 0;
	char userInp;
	double occupancyR;
	Date dateNow, sdt, edt;
	Invoice bookTick;
	struct NumSch {
		int countOfSch;
		TrainSchedule schedule;
	};

	struct NumSch* schList = (struct NumSch*)malloc(5000 * sizeof(struct NumSch));
	if (schList == NULL) {
		printf("Failed to allocate memory to booked structure!\n");
	}

	/* Calulate current Date */
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

	printf("From what date [dd/mm/yyyy] => ");
	rewind(stdin);
	scanf("%d/%d/%d", &sdt.day, &sdt.month, &sdt.year);
	printf("To what date [dd/mm/yyyy] => ");
	rewind(stdin);
	scanf("%d/%d/%d", &edt.day, &edt.month, &edt.year);


	FILE* schL = fopen("trainSchedule.txt", "r");
	if (schL == NULL) {
		printf("Error of open trainSchedule.txt!\n");
		exit(-1);
	}
	else {
		while (fscanf(schL, "%[^|]|%[^\n]\n%[^|]|%[^\n]\n%d/%d/%d|%d:%d\n%d/%d/%d|%d:%d\n%d\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%[^|]|%[^\n]\n%lf\n%[^\n]\n\n",
			&schList[countS].schedule.scheduleNo, &schList[countS].schedule.trainID,
			&schList[countS].schedule.departureStation, &schList[countS].schedule.arrivalStation,
			&schList[countS].schedule.departureDate.day, &schList[countS].schedule.departureDate.month, &schList[countS].schedule.departureDate.year, &schList[countS].schedule.departureTime.hours, &schList[countS].schedule.departureTime.minutes,
			&schList[countS].schedule.arrivalDate.day, &schList[countS].schedule.arrivalDate.month, &schList[countS].schedule.arrivalDate.year, &schList[countS].schedule.arrivalTime.hours, &schList[countS].schedule.arrivalTime.minutes,
			&schList[countS].schedule.duration,
			&schList[countS].schedule.mealList[0].mealName, &schList[countS].schedule.mealList[0].mainFood, &schList[countS].schedule.mealList[0].drinks, &schList[countS].schedule.mealList[0].snacks, &schList[countS].schedule.mealList[0].mealPrice,
			&schList[countS].schedule.mealList[1].mealName, &schList[countS].schedule.mealList[1].mainFood, &schList[countS].schedule.mealList[1].drinks, &schList[countS].schedule.mealList[1].snacks, &schList[countS].schedule.mealList[1].mealPrice,
			&schList[countS].schedule.mealList[2].mealName, &schList[countS].schedule.mealList[2].mainFood, &schList[countS].schedule.mealList[2].drinks, &schList[countS].schedule.mealList[2].snacks, &schList[countS].schedule.mealList[2].mealPrice,
			&schList[countS].schedule.staff[0].staffID, &schList[countS].schedule.staff[0].staffName,
			&schList[countS].schedule.staff[1].staffID, &schList[countS].schedule.staff[1].staffName,
			&schList[countS].schedule.staff[2].staffID, &schList[countS].schedule.staff[2].staffName,
			&schList[countS].schedule.staff[3].staffID, &schList[countS].schedule.staff[3].staffName,
			&schList[countS].schedule.staff[4].staffID, &schList[countS].schedule.staff[4].staffName,
			&schList[countS].schedule.staff[5].staffID, &schList[countS].schedule.staff[5].staffName,
			&schList[countS].schedule.staff[6].staffID, &schList[countS].schedule.staff[6].staffName,
			&schList[countS].schedule.staff[7].staffID, &schList[countS].schedule.staff[7].staffName,
			&schList[countS].schedule.staff[8].staffID, &schList[countS].schedule.staff[8].staffName,
			&schList[countS].schedule.staff[9].staffID, &schList[countS].schedule.staff[9].staffName,
			&schList[countS].schedule.driver[0].driverID, &schList[countS].schedule.driver[0].driverName,
			&schList[countS].schedule.driver[1].driverID, &schList[countS].schedule.driver[1].driverName,
			&schList[countS].schedule.schTrnPrice,
			&schList[countS].schedule.status) != EOF) {

			schList[countS].countOfSch = 0;
			countS++;
		}
		fclose(schL);

		FILE* bkT = fopen("bookingTic.txt", "r");
		if (bkT == NULL) {
			printf("Error of open booking.txt!\n");
			exit(-1);
		}
		else {
			while (fscanf(bkT, "%[^|]|%[^|]|%[^|]|%d|%lf|%d/%d/%d\n",
				bookTick.invoiceNo, bookTick.invSchNo, bookTick.membID, &bookTick.ticketQtt, &bookTick.totalAmount,
				&bookTick.paymentDate.day, &bookTick.paymentDate.month, &bookTick.paymentDate.year) != EOF) {

				for (int ae = 0; ae < bookTick.ticketQtt;ae++) {
					fscanf(bkT, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^\n]\n%[^|]|%[^|]|%[^|]|%[^|]|%lf\n",
						bookTick.ticBook[ae].ticketID, bookTick.ticBook[ae].psgName, bookTick.ticBook[ae].psgIC, bookTick.ticBook[ae].seatNo,
						&bookTick.ticBook[ae].coach, bookTick.ticBook[ae].remarks,
						bookTick.ticBook[ae].selectedMeal.mealName, bookTick.ticBook[ae].selectedMeal.mainFood,
						bookTick.ticBook[ae].selectedMeal.drinks, bookTick.ticBook[ae].selectedMeal.snacks, &bookTick.ticBook[ae].selectedMeal.mealPrice);

					for (int af = 0;af < countS; af++) {
						if ((compareDates(sdt, bookTick.paymentDate) <= 0) && (compareDates(edt, bookTick.paymentDate) >= 0) && (strcmp(bookTick.invSchNo, schList[af].schedule.scheduleNo) == 0)) {
							schList[af].countOfSch++;
						}
					}

				}

			}
			fclose(bkT);

			printf("\n\n----------------------------------- Train Occupancy Rate -----------------------------------\n\n");
			printf("Date : %02d/%02d/%d\n", dateNow.day, dateNow.month, dateNow.year);
			printf("From : %02d/%02d/%d \t To: %02d/%02d/%d\n\n", sdt.day, sdt.month, sdt.year, edt.day, edt.month, edt.year);
			printf("%-18s%-10s%-20s%-20s%-16s\n", "Schedule No", "Train ID", "Departure Sation", "Arrival Station", "Occupancy Rate");
			printf("%-18s%-10s%-20s%-20s%-16s\n", "***********", "********", "****************", "***************", "**************");
			for (int af = 0;af < countS;af++) {
				occupancyR = (double)schList[af].countOfSch / 120;
				printf("%-18s%-10s%-20s%-20s%.2lf%%\n", schList[af].schedule.scheduleNo, schList[af].schedule.trainID,
					schList[af].schedule.departureStation, schList[af].schedule.arrivalStation, occupancyR * 100);

			}
			printf("\n\n--------------------------------------------------------------------------------------------\n\n");
		}
	}
	free(schL);
	printf("\n\nDo you want to continue generate report? [ Y = YES || other cahracter = NO ] => ");
	rewind(stdin);
	scanf("%c", &userInp);
	userInp = toupper(userInp);

	if (userInp == 'Y')
		trainOccupancyRate();
	else
		staffMenuBK();

}
void displaySeat(SeatDisplay* seatTable) {

	int cond = 0, index = 0;

	printf("\n\n************************************** Seat List **************************************\n\n");
	for (int t = 0;t < 40;t += 4) {
		for (int u = 0;u < 3;u++) {
			for (int v = 0;v < 4;v++) {

				if (seatTable->seat[index].status == 'A')
					printf("[%s]", seatTable->seat[index].seatNo);
				else
					printf("{%s}", seatTable->seat[index].seatNo);

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
	printf("\n\n***************************************************************************************\n\n");
	printf("[ ] = Available\t{ } = Booked\n");
}

/* Get the current system date */
void currentDate(Invoice* invoice) {

	time_t current_time;
	struct tm* local_time;

	// Get the current time
	current_time = time(NULL);

	// Convert the current time to the local time
	local_time = localtime(&current_time);

	// Extract day, month, and year
	invoice->paymentDate.day = local_time->tm_mday;
	invoice->paymentDate.month = local_time->tm_mon + 1; // Months are 0-based, so add 1
	invoice->paymentDate.year = local_time->tm_year + 1900; // Years since 1900

}

int compareDates(Date date1, Date date2) {
	if (date1.year < date2.year) {
		return -1; // date1 is earlier
	}
	else if (date1.year > date2.year) {
		return 1; // date2 is earlier
	}
	else {
		// Years are equal, compare months
		if (date1.month < date2.month) {
			return -1; // date1 is earlier
		}
		else if (date1.month > date2.month) {
			return 1; // date2 is earlier
		}
		else {
			// Months are equal, compare days
			if (date1.day < date2.day) {
				return -1; // date1 is earlier
			}
			else if (date1.day > date2.day) {
				return 1; // date2 is earlier
			}
			else {
				return 0; // Both dates are equal
			}
		}
	}
}

/* Calculate length of string or array */
int funcArrayLength(char arr[]) {

	int length = 0;

	for (int i = 0;arr[i] != '\0';++i) {
		length++;
	}
	return length;
}

/* Change user input from lowercase to uppercase */
void lowerToUpper(char arr[], int length) {

	for (int i = 0;i < length;i++) {

		arr[i] = toupper(arr[i]);

	}

}
