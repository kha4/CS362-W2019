/*******************************************************************
 * Kevin Ha
 * CS362
 * Card Test 3
*******************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	printf("\nCard Test 3: Adventurer\n");

	//create gameState and initialize game
	struct gameState A, test;
	int kCards[10] = {adventurer, mine, smithy, village, minion, cutpurse, baron, outpost, feast, embargo};
	initializeGame(2, kCards, 3, &A);

	//set up gameState for testing
	A.whoseTurn = 0;
	A.discardCount[0] = 0;
	A.playedCardCount = 0;
	A.handCount[0] = 3;
	A.hand[0][0] = adventurer;
	A.hand[0][1] = mine;
	A.hand[0][2] = copper;
	A.deckCount[0] = 5;
	A.deck[0][0] = baron;
	A.deck[0][1] = gold;
	A.deck[0][2] = copper;
	A.deck[0][3] = smithy;
	A.deck[0][4] = silver;
	A.hand[1][0] = copper;
	A.handCount[1] = 1;
	A.deck[1][0] = mine;
	A.deckCount[1] = 1;
	memcpy(&test, &A, sizeof(struct gameState));

	//play adventurer
	cardEffect(adventurer, 0, 0, 0, &A, 0, 0);

	//test if adventurer is put into played pile
	printf("Checking if Adventurer was played: ");
	assertTrue(A.playedCardCount == test.playedCardCount + 1 && A.playedCards[0] == adventurer);

	
	//test if other player's hand changed
	printf("Checking no other player's hands were affected: ");
	assertTrue(A.hand[1][0] == test.hand[1][0] && A.handCount[1] == test.handCount[1]);


	//test if other player's deck changed
	printf("Checking no other player's decks were affected: ");
	assertTrue(A.deck[1][0] == test.deck[1][0] && A.deckCount[1] == test.deckCount[1]);

	
	//test if correct treasure cards added properly
	printf("Checking if 2 treasures were added to hand:  ");
	assertTrue(A.handCount[0] == test.handCount[0] + 1 && A.hand[0][2] == silver && A.hand[0][3] == copper);
	

	//make sure other drawn cards are discarded
	printf("Checking if other revealed cards are discarded ");
	assertTrue(A.discardCount[0] == test.discardCount[0] + 1 && A.discard[0][0] == smithy);
	

	//Test with only 1 treasure to draw, goes into infinite loop here because code doesn't cover this
	//Need to add fix before we can run these tests
	
	/*printf("Checking if 1 treasure was added to hand if only 1 is left in deck: ");
	A.hand[0][4] = adventurer;
	A.handCount[0]++;
	cardEffect(adventurer, 0, 0, 0, &A, 4, 0);
	assertTrue(A.handCount[0] == 6 && A.hand[0][4] == gold);


	//Test with no treasures to draw
	printf("Checking if no treasures added if no treasures left in deck: ");
	A.hand[0][5] = adventurer;
	A.handCount[0]++;
	cardEffect(adventurer, 0, 0, 0, &A, 5, 0);
	assertTrue(A.handCount[0] == 5);
	*/

	return 0;


}
