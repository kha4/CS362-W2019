/*********************************************************************
 * Kevin Ha
 * CS362
 * Unit Test 3
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
	printf("\nUnit Test 3: Supply Count\n");

	//create gameState
	struct gameState supplyState;
	
	int kCards[10] = {baron, village, smithy, minion, adventurer, outpost, salvager, feast, mine, gardens};

	//initialize the game
	initializeGame(2, kCards, 5, &supplyState);


	printf("Checking supply count of kingdom card after game initialization: ");
	int a = supplyCount(adventurer, &supplyState);
	assertTrue(a == 10); //supplyCount returns count of cards left in the supply, game begins with 10


	printf("Checking supply count of treasure card after game initialization: ");
	int b = supplyCount(gold, &supplyState);//supply count should return 30 when game begins for treasure
	assertTrue(b == 30);


	printf("Checking supply count of card not chosen for the game: ");
	int c = supplyCount(steward, &supplyState); //returns -1 since card doesn't exit
	assertTrue(c == -1);


	printf("Checking supply count after changing number of supply: ");
	supplyState.supplyCount[adventurer] = 2; //test to see if supplyCount works when gameState changes
	int d = supplyCount(adventurer, &supplyState);
	assertTrue(d == 2);


	return 0;
}
