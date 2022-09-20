#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
#include "app.h"


int main()
{

	char endapp = 'o'; // 'o' not 0 :)
	while (endapp!='c') {
		printf("choose an operation \n a)new trans. \n b)view trans. \n c)close\n");
		scanf_s(" %c", &endapp);//must put sapce before %c
		switch (endapp) {
		case 'a':
			endapp = 'o';
			appStart();
			break;
		case 'b':
			printf("please enter trans. sequence num. : \n ");
			int tempseq;
			scanf("%d", &tempseq);
			getTransaction(tempseq, &transData);
			break;

		}

	}


	
		return 0;
}

