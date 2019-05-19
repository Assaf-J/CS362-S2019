#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {

	printf("\n>>>>>Testing Steward Card<<<<<\n\n");
	struct gameState G, testG;
	int seed = 1000;
	int newCards = 3;
	int discard = 1;
	int newCoins = 2;
	int trashedCards = 2;
	int failures = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, seed, &G);
	
	for (int i = 0; i < 2000; i++)
	{
		testG.deckCount[1] = floor(rand() * MAX_DECK);
		testG.discardCount[1] = floor(rand() * MAX_DECK);
		testG.handCount[1] = floor(rand() * MAX_HAND);

		for (int j = 0; j < testG.deckCount[1]; j++) {
			testG.deck[1][j] = floor(Random() * 26);
		}
		memcpy(&testG, &G, sizeof(struct gameState));
		testG.hand[1][0] = steward;
	
		stewardCard(1, 1, &testG, 0, 0, 0);
		
		if(testG.handCount[1] != G.handCount[1] + newCards - discard)
		{
			failures++;
		}
		if (testG.playedCardCount != G.playedCardCount + discard)
		{
			failures++;

		}
		memcpy(&testG, &G, sizeof(struct gameState));
		
		stewardCard(2, 1, &testG, 0, 0, 0);
	
		if (testG.coins != G.coins + newCoins)
		{
			failures++;

		}
		
		for (int j = 0; j < testG.deckCount[1]; j++) {
			testG.deck[1][j] = floor(Random() * 26);
		}
		memcpy(&testG, &G, sizeof(struct gameState));
		

		
		stewardCard(3, 1, &testG, 1, 2, 0);
		
		if (testG.handCount[1] != G.handCount[1] + 3 - trashedCards)
		{
			failures++;

		}

	

	}

	printf(">>>>>  Testing complete  <<<<<\n\n");
	printf("2000 tests ran on steward card\n");
	printf("Number of failures: %d\n", failures);

	return 0;

}

