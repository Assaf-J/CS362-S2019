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

	printf("\n>>>>>Testing Smithy Card<<<<<\n\n");
	struct gameState G, testG;
	int seed = 1000;
	int newCards = 3;
	int discard = 1;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Current Hand Before Card: %d , Expected Hand Before Card %d\n", testG.handCount[1], G.handCount[1]);
	
	if (G.handCount[1] == 0)
	{
		
		//smithyCard(0, &testG, 1);
		cardIsSmithy(0, 1, &testG, 0);
		printf("Testing Additional Card Count\n");
		printf("Current Hand: %d , Expected Hand %d\n", testG.handCount[1], G.handCount[1] + newCards-discard);
		ASSERT(testG.handCount[1] == G.handCount[1] + newCards - discard);

		printf("Testing Correct cards came from player's deck\n");
		printf("Current Deck: %d , Expected Deck %d\n", testG.deckCount[1], G.deckCount[1] - newCards);
		ASSERT(testG.deckCount[1] == G.deckCount[1] - newCards+discard);

		printf("Testing played card is discarded\n");
		printf("Current Discard: %d , Expected Discard %d\n", testG.playedCardCount, G.playedCardCount + discard);
		ASSERT(testG.playedCardCount == G.playedCardCount + discard);
		

		printf(">>>>>  Testing complete  <<<<<\n\n");
	}
	else
	{
		printf("Failure to initialize game, HandCount != 0");
	}
	return 0;

}