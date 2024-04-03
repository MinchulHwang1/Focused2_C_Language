/*
* FILE : f2.cpp
* PROJECT : Focused 2
* PROGRAMMER : Minchul Hwang
* FIRST VERSION : 2023-01-16
* Description : This project originates from focused 1.
				From focused 1, the function has a condition that can be changed.
				The user's input can be received indefinitely, and if a . is entered at any position, 
				the input is terminated and the data received up to the previous time is output.
				Dynamic allocation is included in the information received and the information stored in the structure.
* The functions in this file are used to struct - createNewNode(), fillFlightInfo(), printFlightInfo(), struct - deleteAllNode(), and clearNewLine()
*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define kDestinationString 30
#define kDateSting 30
#define kContinue 1
#define kTable 72
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS


typedef struct FlightInfo {
	char destination[kDestinationString];
	char date[kDateSting];
	struct FlightInfo* next;
} node;

node* createNewNode(node* newHead);
int fillFlightInfo(node* pFlight);
void printFlightInfo(node* arrFlight);
node* deleteAllNode(node* head);
void clearLine(char* string);

int main() {


	node* flightInformation = NULL;
	
	flightInformation = createNewNode(flightInformation);

	printFlightInfo(flightInformation);

	flightInformation = deleteAllNode(flightInformation);

	return 0;
}


/*
* Function : struct - createNewNode()
* Description : This function is a function that creates a new structure node.
*				Nodes can be created indefinitely, as many times as the user wishes.
* Parameters : node* newHead : This is a head pointer created whenever a new node is created.
* Returns : newHead - Pointer to the first node created among the created nodes.
*/
node* createNewNode(node* newHead) {
	while (kContinue) {
		node* allocFlightInfo = NULL;
		node* ptr = NULL;
		int checkPoint = 0;											//checking value which insert is '.'
		allocFlightInfo = (node*)malloc(sizeof(node));				//create new node and allocation of memory

		if (allocFlightInfo == NULL) {
			printf("No allocated memory\n");
			return newHead;
		}

		checkPoint = fillFlightInfo(allocFlightInfo);
		
		//Node check
		if (newHead == NULL)										
		{															
			newHead = allocFlightInfo;
		}
		else
		{															
			ptr = newHead;
			while (ptr->next != NULL) {
				ptr = ptr->next;
			}
			ptr->next = allocFlightInfo;
		}

		if (checkPoint == 1) {					//break when '.' has been inserted
			break;
		}	
	}

	return newHead;
}


/*
* Function : fillFlightInfo()
* Description : This function receives data from the user and stores them in the created node structure.
* Parameters : node* pFlight - Node pointer created by createNewNode
* Returns : None
*/
int fillFlightInfo(node* pFlight) {

	printf("Please Input destination : ");
	fgets(pFlight->destination, sizeof(pFlight->destination), stdin);
	clearLine(pFlight->destination);
	
	if (strcmp(pFlight->destination, ".") == NULL) {
		pFlight->next = NULL;
		return 1;
	}
	
	printf("Please Input Flight date : ");
	fgets(pFlight->date, sizeof(pFlight->date), stdin);
	clearLine(pFlight->date);
	
	if (strcmp(pFlight->date, ".") == NULL) {
		pFlight->next = NULL;
		return 1;
	}

	pFlight->next = NULL;				//empty next structure
	return 0;
}


/*
* Function : printFlightInfo()
* Description : This function outputs the data stored in the structure.
* Parameters : FlightInfo arrFlight[] : A structure that stores data values ​​entered by the user.
* Returns : None
*/
void printFlightInfo(node* arrFlight) {
	int i = 0;
	char table[kTable] = {};

	table[0] = ' ';
	printf("\n");
	printf("\n");

	for (i = 1; i < kTable; i++)
		table[i] = '-';
	for (i = 0; i < kTable; i++)
		printf("%c", table[i]);
	printf("\n");

	printf("%c%44s", '|', "Flight Schedule");
	printf("%28c\n", '|');

	for (i = 0; i < kTable; i++)
		printf("%c", table[i]);
	printf("\n");

	printf("%c%25s%11c", '|', "* Destination *", '|');
	printf("%21s%15c\n", "* Date *", '|');

	for (i = 0; i < kTable; i++)
		printf("%c", table[i]);
	printf("\n");


	while (arrFlight->next != NULL) {

		printf("|%-35s", arrFlight->destination);
		printf("|%-35s|\n", arrFlight->date);
		arrFlight = arrFlight->next;
	}

	for (i = 0; i < kTable; i++)
		printf("%c", table[i]);
	printf("\n");
}


/*
* Function : clearNewLine()
* Description : If the received data is blank or contains \n, it is removed.
*				In focused1, I cut \n right away from the accepted data, but in this assignment, it was impossible, so I got it from practice.
* Parameters : char* str - the pointer has string from user
* Returns : None
*/
void clearLine(char* string){			
	char* searchNewLine = strchr(string, '\n');
	if (searchNewLine != NULL)
	{
		*searchNewLine = '\0';
	}
}


/*
* Function : struct - deleteAllNode()
* Description : This function deletes all created node structures.
* Parameters : node* head - Address of the first node in the created node structure
* Returns : NULL
*/
node* deleteAllNode(node* head) {
	node* curNode = NULL;
	node* ptr = head;

	while (ptr != NULL) {
		curNode = ptr;
		ptr = ptr->next;
		free(curNode);
	}
	return NULL;
}