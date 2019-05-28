#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
void randSmithyHand(struct gameState*);

int main() {




	printf("\n>>>>>Testing Smithy Card Run<<<<<\n\n");
	struct gameState G, testG;
	int seed = 1000;
	int newCards = 3;
	int discard = 1;
	int numPlayers = rand() % 4;
	int failures = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(numPlayers, k, seed, &G);

	for (int i = 0; i < 2000; i++)
	{
		testG.deckCount[1] = floor(rand() * MAX_DECK);
		testG.discardCount[1] = floor(rand() * MAX_DECK);
		testG.handCount[1] = floor(rand() * MAX_HAND);

		for (int j = 0; j < testG.deckCount[1]; j++) {
			testG.deck[1][j] = floor(Random() * 26);
		}

		memcpy(&testG, &G, sizeof(struct gameState));
		testG.hand[1][0] = smithy;
		cardIsSmithy(0, 1, &testG, 0);

		//smithyCard(0, &testG, 1);

		if (testG.handCount[1] != G.handCount[1] + newCards - discard)
		{
			failures++;
		}



		if (testG.deckCount[1] != G.deckCount[1] - newCards)
		{
			failures++;
		}
		if (testG.playedCardCount != G.playedCardCount + discard)
		{
			failures++;
		}

		if (testG.numPlayers != G.numPlayers)
		{
			failures++;
		}


		if (testG.whoseTurn != G.whoseTurn)
		{
			failures++;
		}
		if(testG.playedCards[0] != smithy)
		{
			failures++;
		}

		if (testG.coins != G.coins)
		{
			failures++;
		}

		
		if (testG.numActions != G.numActions)
		{
			failures++;
		}

		
		if(testG.numBuys != G.numBuys)
		{
			failures++;
		}
		
		int victoryCards = 24;
		if(testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province] == victoryCards);

	}


	printf(">>>>>  Testing complete  <<<<<\n\n");
	printf("2000 tests ran on adventure card\n");
	printf("Number of failures: %d\n", failures);
}
