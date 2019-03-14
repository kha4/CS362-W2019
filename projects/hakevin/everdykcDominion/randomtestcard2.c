/**************************************************************************
 * Kevin Ha
 * CS362
 * Random Test Card 2 - Smithy
***************************************************************************/

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
        printf("\nRandom Test: Smithy\n");
	printf("----------------------------------------------------------------\n");

	//set up game state for game initialization
	struct gameState S;
	int kCards[10];
	int numTests = 10000;
	int testsPassed = 0;

	int a;
	for(a = 0; a < numTests; a++)
	{
		//set up random seed
		int seed = rand() % 10000 + numTests;
		
		int i;
		int randCards[10];
		int kCardNum;
		int dupF;
		kCardNum = 1;
		randCards[0] = smithy;
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

		int deckC = rand() % 497 + 3;//get random deck count
		S.whoseTurn = 0;
                S.discardCount[0] = 0;
                S.playedCardCount = 0;
                
		int handC = rand() % 10 + 1; //get random hand count
		int randH = rand() % 27; //get random hand card for other player
		int handP = rand() % handC; //have smithy be in a random spot in the hand
		S.handCount[0] = handC;
		S.hand[1][0] = randH;
		S.handCount[1] = 1;
		S.deckCount[0] = deckC;

		//choose random cards for the deck
		int b;
                int card;
                int kCard;
                for(b = 0; b < S.deckCount[0]; b++)
                {
                        card = rand() % 27 + 1;
                        if(card == 5)
                        {
                                S.deck[0][b] = gold;
                        }
                        else if(card == 10)
                        {
                                S.deck[0][b] = silver;
                        }
                        else if(card == 15)
                        {
                                S.deck[0][b] = copper;
                        }
                        else
                        {
                                kCard = rand() % 10;
                                S.deck[0][b] = kCards[kCard];
                        }
                }

		//choose random cards for the player's hand
		int c;
		for(c = 0; c < S.handCount[0]; c++)
		{
			card = rand() % 27 + 1;
                        if(card == 5)
                        {
                               	S.hand[0][c] = gold;
                        }
                        else if(card == 10)
                        {
                                S.hand[0][c] = silver;
                        }
                        else if(card == 15)
                        {
                               	S.hand[0][c] = copper;
                        }
                        else
                        {
                                kCard = rand() % 10;
                                S.deck[0][c] = kCards[kCard];
                        }
		}
		S.hand[0][handP] = smithy;

		//copy gameState and call Smithy
		struct gameState test;
		memcpy(&test, &S, sizeof(struct gameState));
		cardEffect(smithy, 0, 0, 0, &S, handP, 0);

		printf("Test Case #%d: Pre-Smithy hand count - %d, Post-Smithy hand count - %d, Overall - ", a, test.handCount[0], S.handCount[0]);

		int pFlag = 1;

		//make sure number of cards drawn is correct
		if(S.handCount[0] != test.handCount[0] + 2)
		{
			printf("FAILED (INCORRECT NUMBER OF CARDS DRAWN)\n");
			pFlag = 0;
		}

		//make sure Smithy was played
		if(S.playedCardCount != test.playedCardCount + 1 || S.playedCards[0] != smithy)
		{
			printf("FAILED (SMITHY NOT IN PLAYED PILE)\n");
			pFlag = 0;
		}

		//make sure cards were drawn from player's own deck and not another deck/pile
		if(S.deckCount[0] != test.deckCount[0] - 3)
		{
			printf("FAILED (CARDS NOT DRAWN FROM CORRECT DECK)\n");
			pFlag = 0;
		}

		//make sure other player's hand was not affected
		if(S.hand[1][0] != test.hand[1][0])
		{
			printf("FAILED (OTHER PLAYER'S HAND AFFECTED)\n");
			pFlag = 0;
		}

		//print passed if all were passed
		if(pFlag == 1)
		{
			printf("PASSED\n");
			testsPassed++;
		}
		
	}

	//print number of test cases passed
	printf("\nNUMBER OF TESTS: %d\n", numTests);
        printf("TESTS PASSED: %d\n\n", testsPassed);

        return 0;
}

