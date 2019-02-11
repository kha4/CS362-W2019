/***************************************************************************
 * Kevin Ha
 * CS362
 * Card Test 4
***************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	printf("\nCard Test 4: Smithy\n");

	//create gameState and initialize game
	struct gameState S, test;
	int kCards[10] = {smithy, village, baron, salvager, embargo, feast, mine, gardens, outpost, minion};
	initializeGame(2, kCards, 5, &S);

	//set up gameState for tests
	S.handCount[0] = 1;
	S.hand[0][0] = smithy;
	S.deckCount[0] = 4;
	S.deck[0][0] = mine;
	S.deck[0][1] = copper;
	S.deck[0][2] = gold;
	S.deck[0][3] = feast;
	S.deck[1][0] = silver;
	S.deckCount[1] = 1;
	S.hand[1][0] = silver;
	S.handCount[1] = 1;
	S.playedCardCount = 0;
	memcpy(&test, &S, sizeof(struct gameState));

	cardEffect(smithy, 0, 0, 0, &S, 0, 0);

	//test if Smithy was played
	printf("Checking if Smithy was played: ");
	assertTrue(S.playedCardCount == test.playedCardCount + 1 && S.playedCards[0] == smithy);
	

	//test to see if right amount of cards added
	printf("Checking hand count: ");
	assertTrue(S.handCount[0] == test.handCount[0] + 2);


	//test to see if added cards are correct
	printf("Checking if cards in hand are correct: ");
	assertTrue(S.hand[0][0] == copper && S.hand[0][1] == feast && S.hand[0][2] == gold);

	//test to see drawn cards are not from other player
	printf("Checking if cards came from player's own deck: ");
	assertTrue(S.hand[0][0] != silver && S.hand[0][1] != silver && S.hand[0][2] != silver);


	//test to see if other player was affected
	printf("Checking if other player's hand was affected: ");
	assertTrue(S.hand[1][0] == test.hand[1][0] && S.handCount[1] == test.handCount[1]);


	//test to see if Smithy discarded from hand
	printf("Checking if Smithy was discarded from hand: ");
	assertTrue(S.playedCards[0] == smithy);


	return 0;

}
