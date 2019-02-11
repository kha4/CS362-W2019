/**************************************************************
 * Kevin Ha
 * CS362
 * Unit Test 1
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
	printf("\nUnit Test 1: Whose Turn\n");
	
	//create gameState
	struct gameState p1Turn, test1;
	struct gameState p2Turn, test2;

	int kCards[10] = {baron, village, smithy, minion, adventurer, outpost, salvager, feast, mine, gardens};

	printf("Checking whose turn during Player 1 turn: ");
	initializeGame(2, kCards, 3, &p1Turn);
	p1Turn.whoseTurn = 0;
	memcpy(&test1, &p1Turn, sizeof(struct gameState));

	int j = whoseTurn(&p1Turn);
	assertTrue(j == p1Turn.whoseTurn); //make sure whoseTurn returns correct player

	printf("Checking any changes in game state: ");
	assertTrue(p1Turn.numPlayers == test1.numPlayers && p1Turn.coins == test1.coins) //can test any gameState aspect here, only 2 are shown


	printf("Checking whose turn during Player 2 turn: ");
	initializeGame(2, kCards, 1, &p2Turn);
	p2Turn.whoseTurn = 1;
	memcpy(&test2, &p2Turn, sizeof(struct gameState)); //make sure whoseTurn returns correct player

	int b = whoseTurn(&p2Turn);
	assertTrue(b == p2Turn.whoseTurn)

	printf("Checking any changes in game state: ");
	assertTrue(p2Turn.numPlayers == test2.numPlayers && p2Turn.coins == test2.coins) //can test any gameState aspect here, only 2 are shown

	return 0;
}
