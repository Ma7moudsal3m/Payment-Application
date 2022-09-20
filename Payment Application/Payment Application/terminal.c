#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include "card.h"
#include "terminal.h"
//extern ST_cardData_t cardData;
ST_terminalData_t termData;
//Implement getTransactionDate function

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{	
	uint8_t  dummyarray[11] = {0};

	strcpy(termData->transactionDate, dummyarray);
	time_t time_1; // using time_t =long long 
	time_t time_2; // using time_t =long long 
	struct tm* time_3 = NULL;
	time(&time_1);
	time(&time_2);
	time_3 = localtime(&time_1);

	char buffer[11];
	//   printf("The history is : %d/%d/%d\n", time_3->tm_mday, (1 + time_3->tm_mon),
	//          (1900 + time_3->tm_year));
	//   printf("The time is : %d:%d:%d\n", time_3->tm_hour, time_3->tm_min,
	//          time_3->tm_sec);
	if ((time_3->tm_mday) < 10)
	{
		strcat(termData->transactionDate, "0");
		strcat(termData->transactionDate, _itoa((int)(time_3->tm_mday), buffer, 10));
	}
	else
	{
		strcat(termData->transactionDate, _itoa((int)(time_3->tm_mday), buffer, 10));
	}
	strcat(termData->transactionDate, "/");

	if ((1 + time_3->tm_mon) < 10)
	{
		strcat(termData->transactionDate, "0");
		strcat(termData->transactionDate, _itoa((int)(1 + time_3->tm_mon), buffer, 10));
	}
	else
	{
		strcat(termData->transactionDate, _itoa((int)(1 + time_3->tm_mon), buffer, 10));
	}
	strcat(termData->transactionDate, "/");
	strcat(termData->transactionDate, _itoa((int)(1900 + time_3->tm_year), buffer, 10));

	printf("%s", termData->transactionDate);

	return TERMINAL_OK;
};

//Implement isCardExpried function

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	
	static char tempexp[100];
	static char temptrans[100];
	strcpy(tempexp, cardData->cardExpirationDate);
	strcpy(temptrans, termData->transactionDate);


	if (atoi(temptrans + 8) > atoi(tempexp + 3)) { // comp year & atoi is convert string to integer
		printf(" EXPIRED_CARD\n");
		return EXPIRED_CARD;
	}
	else {
		if (atoi(temptrans + 8) < atoi(tempexp + 3)) { // comp year
			printf("\n--> Ok\n--> Card expiry Date  is Valid \n");
			return TERMINAL_OK;
		}
		else {
			if (atoi(temptrans + 3) > atoi(tempexp)) { // comp month
				printf(" EXPIRED_CARD\n");
				return EXPIRED_CARD;
			}
			else {
				printf("\n--> Ok\n--> Card expiry Date  is Valid\n");
				return TERMINAL_OK;
			}
		}
	}

};

//Implement setMaxAmount function

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = (float)15000;

	if (termData->maxTransAmount > (float)0)
	{
		printf("--> MAX_AMOUNT you can received is %.2f\n", termData->maxTransAmount);
		return TERMINAL_OK;
	}
	else
	{
		printf("--> INVALID_MAX_AMOUNT\n");
		return INVALID_MAX_AMOUNT;
	}
};

//Implement gatTransactionAmount function

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	termData->transAmount = (float)0;
	
	printf("Please Enter TransactionAmount\n");
    scanf_s("%f", &(termData->transAmount));

	if (termData->transAmount > (float)0)
	{
		printf("--> TransactionAmount is %.2f\n", termData->transAmount);
		return TERMINAL_OK;
	}
	else
	{
		printf("--> INVALID_AMOUNT\n");
		return INVALID_AMOUNT;
	}
};

//Implement isBelowMaxAmount function

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount <= termData->maxTransAmount)
	{
		printf("--> Required Amount is %.2f\n", termData->transAmount);
		return TERMINAL_OK;
	}
	else
	{
		printf("--> Can't require this amount\n");
		return EXCEED_MAX_AMOUNT;
	}

};
