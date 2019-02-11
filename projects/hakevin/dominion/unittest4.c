/***********************************************************************
 * Kevin Ha
 * CS362
 * Unit Test 4
************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	printf("\nUnit Test 4: Buy Cards\n");

	//create gameState
	struct gameState buyState;
	
	//set up gameState for tests
	buyState.whoseTurn = 0;
	buyState.numBuys = 3;
	buyState.coins = 5;
	buyState.supplyCount[feast] = 1;
	buyState.supplyCount[adventurer] = 1;	
	buyState.supplyCount[smithy] = 0;
	buyState.supplyCount[mine] = 1;

	printf("Checking buy cards with enough coins for purchase: ");
	assertTrue(buyCard(feast, &buyState) == 0);//make sure it returns the correct value, this only tests for crash

	printf("Checking supply count decreased with purchase: ");
	assertTrue(buyState.supplyCount[feast] == 0);//test gameState for decrease in supply with purchase

	printf("Checking coin count decreased with purchase: ");
	assertTrue(buyState.coins == 1);//test gamestate for decrease in player coins with purchase

	printf("Checking if bought card ends up in discard pile: ");
	assertTrue(buyState.discardCount[0] == 1);//makes sure card bought ends up in player discard pile

	//tests what happens when insufficient coins used when purchasing and making sure coins stays the same
	printf("Checking buy cards with not enough coins for purchase: ");
	buyState.coins = 1;
	assertTrue(buyCard(adventurer, &buyState) == -1 && buyState.coins == 1); 
	

	//test what happens when sufficient coins but no card supply left, coins/discard remain the same
	printf("Checking buy cards with no card supply: ");
	buyState.coins = 10;
	assertTrue(buyCard(smithy, &buyState) == -1 && buyState.coins == 10 && buyState.discardCount[0] == 1);


	//test what happens when player tries to buy without buys left, coins/discard remain the same
	printf("Checking buy cards with no player buys left: ");
	buyState.numBuys = 0;
	assertTrue(buyCard(mine, &buyState) == -1 && buyState.coins == 10 && buyState.discardCount[0] == 1);


	return 0;
}
