#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "card.h"

ST_cardData_t cardData;

//Implement getCardHolderName function

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	static uint8_t  dummyarray[25] = {0};
	strcpy(cardData->cardHolderName, dummyarray);

	printf("Please Enter cardHolderName :\n ");
	uint8_t cardHolderName[25];
	scanf("%24s", &(cardHolderName));//not there are another way by useing scanf_s but must use "_" after every name :)0
	// printf("\n%s", cardHolderName);

	if (strlen(cardHolderName) >= 20 && strlen(cardHolderName) <= 24)
	{
		strcat(cardData->cardHolderName, cardHolderName);
		printf("--> Name is %s\n", cardData->cardHolderName);
		return CARD_OK;
	}
	else
	{
		printf("--> WRONG_NAME\n");
		return WRONG_NAME;
	}
};

//Implement getCardExpiryDate function

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    printf("please enter card expiry date MM/YY"
		":\n");

	char Y[3];
	char M[3];
	char dum[2];
	scanf("%2s%1s%2s", &M, &dum, &Y);
	//   scanf("%1s", &dum); 
	//   scanf("%3s", &Y);
	int inty = atoi(Y);

	if (M[0] >= '0' && M[0] <= '1' && inty >= 22 && inty <= 30) {
		if ((M[0] == '1' && (M[1] > '0' && M[1] <= '2')) ||
			(M[0] == '0' && (M[1] >= '1' && M[1] <= '9')) ||
			(M[1] == '0' && (M[0] >= '1' && M[1] <= '2'))) {
			strcat(cardData->cardExpirationDate, M);
			strcat(cardData->cardExpirationDate, dum);
			strcat(cardData->cardExpirationDate, Y);
			printf("your expiry date is : %s%s%s\n", M, dum, Y);//for test
			return CARD_OK;
		}
		else 
		{
			printf("--> WRONG_EXP_DATE\n");
			return WRONG_EXP_DATE;
		}

	}
	else
	{
		printf("--> WRONG_EXP_DATE\n");
		return WRONG_EXP_DATE;
	}

};


//Implement getCardPAN function

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t  dummyarray [20] = {0};
	strcpy(cardData->primaryAccountNumber, dummyarray);

	printf("Please Enter Primary_account_number\n");
	uint8_t primaryAccountNumber[20];
	scanf("%19s", &primaryAccountNumber);
	if (strlen(primaryAccountNumber) >= 16 && strlen(primaryAccountNumber) < 19)
	{

		if ((primaryAccountNumber[0] == '5' && primaryAccountNumber[1] == '4' && primaryAccountNumber[2] == '8' && primaryAccountNumber[3] == '2')||
		   (primaryAccountNumber[0] == '5' && primaryAccountNumber[1] == '3' && primaryAccountNumber[2] == '5' && primaryAccountNumber[3] == '9' )||
		   (primaryAccountNumber[0] == '5' && primaryAccountNumber[1] == '4' && primaryAccountNumber[2] == '1' && primaryAccountNumber[3] == '1' )||
		   (primaryAccountNumber[0] == '5' && primaryAccountNumber[1] == '3' && primaryAccountNumber[2] == '3' && primaryAccountNumber[3] == '9'))
		{
			strcat(cardData->primaryAccountNumber, primaryAccountNumber);
			printf("--> This is MasterCard\n");
			printf("--> PrimaryAccountNumber %s\n",primaryAccountNumber);
		}
		else
		{
			strcat(cardData->primaryAccountNumber, primaryAccountNumber);
			printf("--> This is Visa or Meza\n");
			printf("--> PrimaryAccountNumber %s\n", primaryAccountNumber);
		}
		return CARD_OK;

	}
	else
	{
		printf("--> WRONG_PAN\n");
		return WRONG_PAN;
	}
};