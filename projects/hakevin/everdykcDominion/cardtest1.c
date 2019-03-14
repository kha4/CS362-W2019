/*************************************************************
 * Kevin Ha
 * CS362
 * Card Test 1
************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	printf("\nCard Test 1: Great Hall\n");

	//create gameState and initialize game
	struct gameState GH, test;
	int kCards[10] = {great_hall, adventurer, smithy, mine, gardens, feast, village, salvager, cutpurse, minion};
	initializeGame(2, kCards, 5, &GH);
	GH.whoseTurn = 0;

	printf("Checking if Great Hall was played: ");
	GH.discardCount[0] = 0;
	GH.playedCardCount = 0;
	GH.hand[0][0] = great_hall;
	GH.handCount[0] = 1;
	GH.handCount[1] = 5;
	memcpy(&test, &GH, sizeof(struct gameState));

	//play great hall card
	cardEffect(great_hall, 0, 0, 0, &GH, 0, 0);

	assertTrue(GH.playedCardCount == 1 && GH.playedCards[0] == great_hall); //test to see if great hall is added to played card pile


	//test to make sure player adds one card to hand but also discards great hall
	//also test to make sure gameState of the other player's hand is not changed
	printf("Checking draw card effect: ");
	assertTrue(GH.handCount[0] == test.handCount[0] && GH.handCount[1] == test.handCount[1]);


	//test for an added action
	printf("Checking Action +1 effect: ");
	assertTrue(GH.numActions == test.numActions + 1);


	return 0;
}
