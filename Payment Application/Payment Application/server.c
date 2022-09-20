#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "card.h"
#include "terminal.h"
#include "server.h"


ST_transaction_t transData[255] = {{0}};
ST_accountsDB_t accountRefrence[255] =
{
  {2000.0F,RUNNING,"4479148232264003"},{100000.0F,BLOCKED,"4479148232262478"},{1000.0F,RUNNING,"4479148232262270"},
  {12000.0F,BLOCKED,"4479148232264854"},{10000.0F,RUNNING,"4479148232262122"},{100000.0F,RUNNING,"4479148232266743"},
  {100.0F,BLOCKED,"5359000207190238"},{10020.0F,RUNNING,"5359000207191020"},{100400.0F,BLOCKED,"5359000207196532"},
  {100012.0F,RUNNING,"5359000207195187"},{102200.0F,BLOCKED,"5359000207194438"},{1040200.0F,RUNNING,"5359000207190618"},
  {100400.0F,RUNNING,"5411756677417734"},{102200.0F,BLOCKED,"5411756677411380"},{100890.0F,RUNNING,"5411756677418013"},
  {100022.0F,BLOCKED,"5411756677410614"},{10330.0F,RUNNING,"5411756677416884"},{121000.0F,RUNNING,"5411756677417510"},
  {100770.0F,BLOCKED,"4514093608850620"},{109900.0F,RUNNING,"4514093608852204"},{1033400.0F,BLOCKED,"4514093608858664"},
  {101200.0F,RUNNING,"4514093608855215"},{4451000.0F,BLOCKED,"4514093608855603"},{1779000.0F,RUNNING,"4514093608858342"},
  {101100.0F,RUNNING,"5170770054623138"},{1002210.0F,BLOCKED,"5170770054623047"},{1023400.0F,RUNNING,"5170770054628434"},
  {1212000.0F,BLOCKED,"5170770054623807"},{1123000.0F,RUNNING,"5170770054626347"},{1345000.0F,RUNNING,"5170770054622437"},
  {137000.0F,BLOCKED,"4465470000240114"},{12000.0F,RUNNING,"4465470000248307"},{45000.0F,BLOCKED,"4465470000244660"},
  {8000.0F,RUNNING,"4465470000247101"},{9000.0F,BLOCKED,"4465470000240528"},{3000.0F,RUNNING,"4465470000244785"}
};

int x = -1;
char Card_pan[20];
int counter;

//Implement recieveTransactionData function

EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{

	(transData + counter)->cardHolderData = cardData;
	(transData + counter)->terminalData = termData;
	saveHolder = saveTransaction(transData);
	if (saveHolder == SAVING_FAILED) {
		puts("INTERNAL_SERVER_ERROR\n");
		return INTERNAL_SERVER_ERROR;
	}
	else {

		puts("APPROVED\n");
		(accountRefrence +x)->balance-= (transData + counter)->terminalData.transAmount;
		printf("new balance : %0.2f\n", (accountRefrence + x)->balance);
		printf(" last  sequence number is: %d\n", (transData + counter)->transactionSequenceNumber);
	}

	return ((transData + counter)->transState);
	counter++;

};


//Implement isValidAccount function

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    strcpy(Card_pan, cardData->primaryAccountNumber);
	for (int z = 0; z < 255; z++)
	{
		if (!strcmp(Card_pan, (accountRefrence+z)->primaryAccountNumber))
		{
			x = z;
			printf("account num is : %d\n", x);
			break;
		}
	}
	if (x == -1)
	{
		printf("--> ACCOUNT_NOT_FOUND\n");
		return ACCOUNT_NOT_FOUND;
	}
	else
	{
		printf("--> ACCOUNT FOUND\n");
		return SERVER_OK;
	}

};

//Implement isBlockedAccount function

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	//ST_accountsDB_t *ptr = accountRefrence;
	printf("  account state: %d \n PAN: %s \n",(accountRefrence+x)->state,(accountRefrence+x)->primaryAccountNumber);


	if (accountRefrence[x].state == RUNNING) {
		puts("SERVER_OK");
		return SERVER_OK;
	}
	else {
		puts("BLOCKED_ACCOUNT");
		/*puts("DECLINED_STOLEN_CARD");*/
		return BLOCKED_ACCOUNT;
	}
	
};

//Implement isAmountAvailable function

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence[x].balance < termData->transAmount)
	{
		printf("LOW_BALANCE\n");
		return LOW_BALANCE;
    }
	else
	{
		printf("SERVER_OK\n");
		return SERVER_OK;
	}
};

//Implement saveTransaction function

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (counter == 255)
	{
		puts("INTERNAL_SERVER_ERROR\n");
		return SAVING_FAILED;
	}

	if (is_validaccount != 0) {
		transData[counter].transState = DECLINED_STOLEN_CARD;
		puts("DECLINED_STOLEN_CARD\n");
	}
	else if (block_state != 0) {
		transData[counter].transState = FRAUD_CARD;
		puts("FRAUD_CARD\n");
	}
	else if (is_okamount != 0) {
		transData[counter].transState = DECLINED_INSUFFECIENT_FUND;
		puts("DECLINED_INSUFFECIENT_FUND\n");
	}
	else
	{
		transData[counter].transState = APPROVED;
		transData[counter].transactionSequenceNumber = counter + 1;
		puts("transaction ok\n");
		return SERVER_OK;
	}
};

//Implement getTransaction function

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	int requested_trans= -11;
	for (int y = 0; y < 255; ++y) {
		if ((transData + y)->transactionSequenceNumber == transactionSequenceNumber) {
			requested_trans = y;
			break;
		}
	}
	if (requested_trans == -11) {
		puts("transation not found\n");
		return TRANSACTION_NOT_FOUND;
	}

	printf(" made by :   %24s\n", (transData + requested_trans )->cardHolderData.cardHolderName );
	printf ("PAN : %19s\n", (transData + requested_trans )->cardHolderData.primaryAccountNumber );
	printf ("card expiry: %5s\n", (transData + requested_trans )->cardHolderData.cardExpirationDate);
	printf ("date of this transaction : %10s\n", (transData + requested_trans )->terminalData.transactionDate);
	printf ("transmited amount  : %0.2f\n", (transData + requested_trans )->terminalData.transAmount);
	printf ("max allowed  was : %0.2f\n", (transData + requested_trans )->terminalData.maxTransAmount);
	printf ("trans state code  : %d\n _nonzero code means non approved trans._\n", (transData + requested_trans )->transState);

	return SERVER_OK;

};





