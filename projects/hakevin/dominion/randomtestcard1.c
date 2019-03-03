/*****************************************************************************
 * Kevin Ha
 * CS362
 * Random Test Card 1 - Salvager
****************************************************************************/

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

        printf("\n----------------------------------------------------------------");
        printf("\nRandom Test: Salvager\n");
        printf("----------------------------------------------------------------\n");

	//creat game state
        struct gameState S;
        int kCards[10];
        int numTests = 10000;
        int testsPassed = 0;

	int a;
        for(a = 0; a < numTests; a++)
        {
		//create seed for game initialization
                int seed = rand() % 10000 + numTests;

                int i;
                int randCards[10];
                int kCardNum;
                int dupF;
                kCardNum = 1;
                randCards[0] = salvager;
		kCards[0] = randCards[0];

		//choose random kingdom cards for the game
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

		initializeGame(2, kCards, seed, &S);

		S.whoseTurn = 0;
		S.discardCount[0] = 0;
		S.playedCardCount = 0;

		int handC = rand() % 9 + 2; //choose hand count
		int randDiscard = rand() % (handC - 1) + 1; //choose which card to trash
		int randH = rand() % 27; //choose card in other player's hand
		S.hand[0][0] = salvager;
		S.handCount[0] = handC;
                S.handCount[1] = randH;
                S.deckCount[0] = 0;
		S.numBuys = 1;
		int randCoins = rand() % 21; //choose a random number of coins to test
		S.coins = randCoins;
	
		//choose random cards in the player's hand
		int b;
		int kCard;
		int card;
                for(b = 1; b < S.handCount[0]; b++)
                {
                        card = rand() % 17 + 1;
                        if(card == 5)
                        {
                                S.hand[0][b] = gold;
                        }
                        else if(card == 10)
                        {
                                S.hand[0][b] = silver;
                        }
                        else if(card == 15)
                        {
                                S.hand[0][b] = copper;
                        }
			else if(card == 1)
                        {
                                S.hand[0][b] = estate;
                        }
                        else if(card == 2)
                        {
                                S.hand[0][b] = duchy;
                        }
                        else if(card == 3)
                        {
                                S.hand[0][b] = province;
                        }
                        else
                        {
                                kCard = rand() % 10;
                                S.hand[0][b] = kCards[kCard];
                        }

                }

		//copy gameState and call Salvager
		struct gameState test;
		memcpy(&test, &S, sizeof(struct gameState));
		cardEffect(salvager, randDiscard, 0, 0, &S, 0, 0);

		int coinsGained;
		coinsGained = S.coins - test.coins;

		printf("Test Case #%d: Number of Buys - %d, Coins Gained - %d, Overall - ", a+1, S.numBuys, coinsGained);

		int pFlag = 1;

		//make sure salvager is played
		if(S.playedCardCount != test.playedCardCount + 1 || S.playedCards[0] != salvager)
		{
			printf("FAILED (SALVAGER NOT IN PLAYED PILE)\n");
			pFlag = 0;
		}

		//make sure the +1 buy effect worked
		if(S.numBuys != test.numBuys + 1)
		{
			printf("FAILED (NUMBER OF BUYS INCORRECT)\n");
			pFlag = 0;
		}

		//make sure the number of coins gains is correct
		if(S.coins != (test.coins + getCost(test.hand[0][randDiscard])))
		{
			printf("FAILED (NUMBER OF COINS GAINED INCORRECT)\n");
			pFlag = 0;
		}

		//make sure other player's hand is not affected
		if(S.hand[1][0] != test.hand[1][0])
		{
			printf("FAILED (OTHER PLAYER'S HAND AFFECTED)\n");
			pFlag = 0;
		}

		//print passed if everything was passed
		if(pFlag == 1)
		{
			printf("PASSED\n");
			testsPassed++;
		}
	}	

	//print number of tests passed
	printf("\nSALVAGER\n");
	printf("\nNUMBER OF TESTS: %d\n", numTests);
	printf("TESTS PASSED: %d\n\n", testsPassed);

	return 0;

}
