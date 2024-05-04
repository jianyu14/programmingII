#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
int getValidChoice(int lowerBound, int upperBound);
void main(){

  printf("LOGO");
  
  
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
