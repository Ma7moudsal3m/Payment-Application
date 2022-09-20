#pragma once 
#ifndef APP_H
#define APP_H
#include "card.h"
#include "terminal.h"
#include "server.h"

extern ST_cardData_t cardData;
extern ST_terminalData_t termData;
extern ST_transaction_t transData[255];
extern ST_accountsDB_t accountRefrence[255];

//void appStart(void);
void appStart(void) {

	if (getCardHolderName(&cardData) != 0)
		return;

	if (getCardExpiryDate(&cardData) != 0) {
		return;
	}

	if (getCardPAN(&cardData) != 0) {
		return;
	}

	getTransactionDate(&termData);

	while (isCardExpired(&cardData, &termData) != 0)
		isCardExpired(&cardData, &termData);

	while (setMaxAmount(&termData) != 0)
		setMaxAmount(&termData);

	while (getTransactionAmount(&termData) != 0)
		getTransactionAmount(&termData);

	while (isBelowMaxAmount(&termData) != 0)
		getTransactionAmount(&termData);

	if (is_validaccount = isValidAccount(&cardData, ((&accountRefrence)[0])))
	{
		return;
	}
	if (block_state = isBlockedAccount((&accountRefrence)[0]))
	{
		return;
	}
	if (is_validaccount = isAmountAvailable(&termData, ((&accountRefrence)[0])))
	{
		return;
	}

	int mainholder = recieveTransactionData(&transData);
	if (mainholder == INTERNAL_SERVER_ERROR) {
		puts("max trans. limit exceeed ... terminating program.\n");
		exit(EXIT_FAILURE);
	}
	return;
}

#endif // !1