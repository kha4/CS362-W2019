/***************************************************************************
 * Kevin Ha
 * CS362
 * Unit Test 2
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
	
	printf("\nUnit Test 2: Update Coins\n");

	//create gamestate
	struct gameState coinState;
	int a, b, c;
	coinState.handCount[1] = 7;
	coinState.coins = 0;

	printf("Checking copper coins: ");
	for(a = 0; a < 7; a++)
	{
		coinState.hand[1][a] = copper; //add a hand with 7 copper
	}

	updateCoins(1, &coinState, 0); //call updateCoins

	assertTrue(coinState.coins == 7); //make sure up updateCoins changed gameState correctly


	//similar to above but with silver
	printf("Checking silver coins: ");
	for(b = 0; b < 7; b++)
        {
                coinState.hand[1][b] = silver;
        }

        updateCoins(1, &coinState, 0);

        assertTrue(coinState.coins == 14);


	//similar to above but with gold
	printf("Checking gold coins: ");
	for(c = 0; c < 7; c++)
        {
                coinState.hand[1][c] = gold;
        }

        updateCoins(1, &coinState, 0);

        assertTrue(coinState.coins == 21);


	//checking updateCoins works properly with a mix of different treasure cards
	printf("Checking mix of coins: ");
	coinState.hand[1][0] = copper;
	coinState.hand[1][1] = copper;
	coinState.hand[1][2] = silver;
        coinState.hand[1][3] = silver;
	coinState.hand[1][4] = gold;
        coinState.hand[1][5] = gold;
	coinState.hand[1][6] = silver;

	updateCoins(1, &coinState, 0);

	assertTrue(coinState.coins == 14);


	//makes sure updateCoins processes bonuses correctly
	printf("Checking bonus coins: ");
	updateCoins(1, &coinState, 6);
	assertTrue(coinState.coins == 20);

	//test to see if 0 treasure in hand will work correctly
	printf("Checking no coins in hand: ");
	coinState.handCount[1] = 1;
	coinState.hand[1][0] = smithy;
	updateCoins(1, &coinState, 0);
	assertTrue(coinState.coins == 0);

}
