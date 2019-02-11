/******************************************************************
 * Kevin Ha
 * CS326
 * Card Test 2
**********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	printf("\nCard Test 2: Salvager\n");
	
	//create gamestate and initialize game
	struct gameState S, test;
        int kCards[10] = {great_hall, adventurer, smithy, mine, gardens, feast, village, salvager, cutpurse, minion};
	initializeGame(2, kCards, 5, &S);
        S.whoseTurn = 0;

        //ready gameState for tests
        S.discardCount[0] = 0;
        S.playedCardCount = 0;
	S.hand[1][0] = copper;
	S.handCount[1] = 1;
        S.hand[0][0] = salvager;
	S.hand[0][1] = mine;
        S.handCount[0] = 2;
	S.coins = 5;
	S.numBuys = 1;
	memcpy(&test, &S, sizeof(struct gameState));
	
	//play salvager
	cardEffect(salvager, 1, 0, 0, &S, 0, 0);

	//test if salvager is moved to played pile
	printf("Checking if Salvager was played: ");
        assertTrue((S.playedCardCount == test.playedCardCount + 1) && (S.playedCards[0] = salvager));
       

	//test if another buy is added for player
	printf("Checking +1 Buy effect: ");
	assertTrue(S.numBuys == test.numBuys + 1);

	//test if salvager and trashed card is no longer in the hand and salvager goes to played card pile
	printf("Checking if choice card was trashed: ");
	assertTrue(S.handCount[0] == 0 && S.playedCardCount == 1);


	//test if gameState for coins changes based on trashed card
	printf("Checking coins gained based on trashed card: ");
	assertTrue(S.coins == test.coins + 5);

	//test to see if other player's hand was affected
	printf("Checking if no other players affected: ");
	assertTrue(S.hand[1][0] == test.hand[1][0] && S.handCount[1] == test.handCount[1]);


	return 0;


}
