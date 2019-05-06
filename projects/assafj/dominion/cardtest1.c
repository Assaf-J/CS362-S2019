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

	int numPlayers = 2;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.hand[0][0] = smithy;
	testG.handCount[0] = 1;


	printf("Test if Smithy is altering number of players in game state\n");
	cardEffect(smithy, 0, 0, 0, &testG, 0, 0);
	printf("Current Players: %d , Expected Players: %d\n", testG.numPlayers, G.numPlayers);
	ASSERT(testG.numPlayers == G.numPlayers);

	printf("Test if Smithy is altering whoseTurn in gameplay\n");
	ASSERT(testG.whoseTurn == G.whoseTurn);

	printf("Test whether discarded card is smithy\n");
	ASSERT(testG.playedCards[0] == smithy);

	printf("Test whether smithy alters coins\n");
	ASSERT(testG.coins == G.coins);

	printf("Test smithy does not alter number of actions\n");
	ASSERT(testG.numActions == G.numActions);

	printf("Test if smithy alters the number of buys");
	ASSERT(testG.numBuys == G.numBuys);

	printf("Test if victory card piles are altered\n");
	int victoryCards = 24;
	ASSERT(testG.supplyCount[estate]+ testG.supplyCount[duchy] + testG.supplyCount[province]==victoryCards);



}