#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define ASSERT(expr) \
    if (!(expr)) \
       printf("FAIL\n");\
	else \
		printf("PASS\n");

int main() {

	printf("\n>>>>>Testing Adventurer Card<<<<<\n\n");
	struct gameState G, testG;
	int seed = 1000;
	int newCards = 2;
	int temphand[MAX_HAND];
	int discard = 1;
	int numPlayers = 2;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(numPlayers, k, seed, &G);
	int failures = 0;

	for (int i = 0; i < 2000; i++) 
	{
		testG.deckCount[0] = floor(rand() * MAX_DECK);
		testG.discardCount[0] = floor(rand() * MAX_DECK);
		testG.handCount[0] = floor(rand() * MAX_HAND);

		for (int j = 0; j < testG.deckCount[0]; j++) {
			testG.deck[0][j] = floor(Random() * 26);
		}

		memcpy(&testG, &G, sizeof(struct gameState));

		cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);

		if ((testG.numPlayers != G.numPlayers))
		{
			failures++;
		}

		if ((testG.whoseTurn != G.whoseTurn))
		{
			failures++;
		}

		if ((testG.playedCards[0] != adventurer))
		{
			failures++;
		}


		if ((testG.numActions != G.numActions))
		{
			failures++;
		}


		if ((testG.coins != G.coins))
		{
			failures++;

		}
		if ((testG.numBuys != G.numBuys))
		{
			failures++;
		}


		int victoryCards = 24;
		if ((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province] != victoryCards))
		{
			failures++;

		}


		if ((testG.handCount[0] != G.handCount[0] + 1 + newCards - discard))
		{
			printf("Current Hand: %d , Expected Hand %d\n", testG.handCount[0], G.handCount[0] + 1 + newCards - discard);
		}

		int treasures = 0;
		for (int i = 0; i < testG.handCount[1]; i++)
		{
			if (handCard(i, &testG) == copper) {
				treasures++;
			}
			if (handCard(i, &testG) == silver) {
				treasures++;
			}
			if (handCard(i, &testG) == gold) {
				treasures++;
			}




			if ((treasures != 2))
			{
				failures++;
			}

			
		}

	}
	
	printf(">>>>>  Testing complete  <<<<<\n\n");
	printf("2000 tests ran on adventure card\n");
	printf("Number of failures: %d\n", failures);
}

