/*********************************************************************
 * Kevin Ha
 * CS362
 * Random Test - Adventurer
***********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	srand(time(NULL));

	//print title of test
	printf("\n-------------------------------------------------------------------");
	printf("\nRandom Test: Adventurer\n");
	printf("-------------------------------------------------------------------\n");

	//create game state and variables needed
	struct gameState A;
	int kCards[10];
	int numTests = 10000;
	int testsPassed = 0;
	
	//loop depending on the number of tests
	int a;
	for(a = 0; a < numTests; a++)
	{
		//create a random seed for game initialization
		int seed = rand() % 10000 + numTests;

		int i;
		int randCards[10];
		int kCardNum;
		int dupF;
		kCardNum = 1;
		randCards[0] = adventurer; //first kingdom card is adventurer
		
		//randomly choose the rest of the kingdom cards
		while(kCardNum < 10)
		{
			dupF = 0;
			randCards[kCardNum] = rand() % 20 + 7;
			for(i = 0; i < kCardNum; i++)
			{
				if(randCards[kCardNum] == randCards[i])
				{
					dupF = 1;
				}
			}
			if(dupF == 0)
			{
				kCards[kCardNum] = randCards[kCardNum];
				kCardNum++;
				
			}
		}

		//create the game using the kingdom cards and seed
		initializeGame(2, kCards, seed, &A);

		
		int deckC = rand() % 499 + 2; //get random deck count
		A.whoseTurn = 0;
		A.discardCount[0] = 0;
		A.playedCardCount = 0;
		A.handCount[0] = 1;
		A.hand[0][0] = adventurer;

		int handC = rand() % 10 + 1; //get random hand count
		int randH = rand() % 27; //get random card for other player's hand
		A.handCount[0] = handC;
		A.hand[1][0] = randH;
		A.handCount[1] = 1;
		A.deckCount[1] = 0;
		A.deckCount[0] = deckC;
		A.coins = 0;		

		//randomly choose cards for the deck
		int b;
		int card;
		int kCard;
		for(b = 0; b < A.deckCount[0]; b++)
		{
			card = rand() % 17 + 1;
			if(card == 5)
			{
				A.deck[0][b] = gold;
			}
			else if(card == 10)
			{	
				A.deck[0][b] = silver;
			}
			else if(card == 15)
			{
				A.deck[0][b] = copper;
			}
			else if(card == 1)
                        {
                                A.deck[0][b] = estate;
                        }
                        else if(card == 2)
                        {
                                A.deck[0][b] = duchy;
                        }
                        else if(card == 3)
                        {
                                A.deck[0][b] = province;
                        }
			else
			{
				kCard = rand() % 10;
				A.deck[0][b] = kCards[kCard];
			}
		}

		//randomly choose cards for the hand
		int h;
		for(h = 1; h < A.handCount[0]; h++)
		{
			card = rand() % 17 + 1;
                        if(card == 5)
                        {
                                A.hand[0][h] = gold;
                        }
                        else if(card == 10)
                        {
                                A.hand[0][h] = silver;
                        }
                        else if(card == 15)
                        {
                                A.hand[0][h] = copper;
                        }
			else if(card == 1)
                        {
                                A.hand[0][h] = estate;
                        }
                        else if(card == 2)
                        {
                                A.hand[0][h] = duchy;
                        }
                        else if(card == 3)
                        {
                               A.hand[0][h] = province;
                        }
                        else
                        {
                                kCard = rand() % 10;
                                A.hand[0][h] = kCards[kCard];
                        }
		}

		//implement two dedicated treasures in the deck so infinite loop doesn't occure
		int treasureA = rand() % deckC;
		int treasureB;
		int dp = 0;
		while(dp == 0)
		{
			treasureB = rand() % deckC;
			if(treasureA != treasureB)
			{
				dp = 1;
			}
		}
		//choose random treasures to put in deck
		int randA = rand() % 3 + 4;
		int randB = rand() % 3 + 4;
		A.deck[0][treasureA] = randA;
		A.deck[0][treasureB] = randB;

		//update coin count in hand
		int t;
		for(t = 0; t < A.handCount[0]; t++)
                {
                        if(A.hand[0][t] == gold || A.hand[0][t] == silver || A.hand[0][t] == copper)
                        {
                                A.coins++;
                        }
                }

		//copy gameState to another
		struct gameState test;
		memcpy(&test, &A, sizeof(struct gameState));
		cardEffect(adventurer, 0, 0, 0, &A, 0, 0); //call adventurer

		//update coin count after adventurer was called
		A.coins = 0;		
		int c;
		for(c = 0; c < A.handCount[0]; c++)
		{
			if(A.hand[0][c] == gold || A.hand[0][c] == silver || A.hand[0][c] == copper)
			{
				A.coins++;
			}
		}

		//print test cases
		printf("Test Case #%d: Pre Hand Count - %d, Post Hand Count - %d, Treasure in Hand - %d, Overall - ", a+1, handC, A.handCount[0], A.coins);

		int pFlag = 1;

		//make sure number of treasure cards were drawn
		if(A.coins != test.coins + 2 || A.handCount[0] != test.handCount[0] + 1)
		{
			printf("FAILED (INCORRECT NUMBER OF TREASURE CARDS DRAWN)\n");
			pFlag = 0;
		}

		//make sure adventure was played
		if(A.playedCardCount != (test.playedCardCount + 1) || A.playedCards[0] != adventurer)
		{
			printf("FAILED (ADVENTURER WAS NOT PLAYED)\n");
			pFlag = 0;
		}
		
		//make sure the other player's hand was not affected
		if(A.handCount[1] != test.handCount[1] || A.hand[1][0] != test.hand[1][0])
		{
			printf("FAILED (OTHER PLAYER'S HAND AFFECTED)\n");
			pFlag = 0;
		}
		
		//make sure other player's deck was not affected
		if(A.deckCount[1] != test.deckCount[1])
		{
			printf("FAILED (OTHER PLAYER'S DECK AFFECTED)\n");
			pFlag = 0;
		}

		//make sure no treasures were discarded while adventurer was being played
		int d;
		int treasureDis = 0;
		for(d = 0; d < A.discardCount[0]; d++)
		{
			if(A.discard[0][d] == gold || A.discard[0][d] == silver || A.discard[0][d] == copper)
			{
				treasureDis++;
			}

		}
		if(treasureDis != 0)
		{
			printf("FAILED (DISCARDED TREASURE\n");
			pFlag = 0;
		}
		
		//print passed if all assertions passed
		if(pFlag == 1)
		{
			printf("PASSED\n");
			testsPassed++;
		}
	}

	//print number of test passed
	printf("\nADVENTURER\n");
	printf("\nNUMBER OF TESTS: %d\n", numTests);
	printf("TESTS PASSED: %d\n\n", testsPassed);

	return 0;
}

