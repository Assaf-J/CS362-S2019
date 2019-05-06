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

	printf("\n>>>>>Testing Embargo Card<<<<<\n\n");
	struct gameState G, testG;
	int seed = 1000;
	int newCoins = 2;
	int token = 1;
	
	int numPlayers = 2;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	//add cutpurse to player 0 hand
	testG.hand[0][0] = embargo;
	testG.handCount[0] = 1;

	//add copper to player 1 hand

	cardEffect(embargo, 0, 0, 0, &testG, 0, 0);



	printf("Test if embargo adds two to the total coins\n");
	ASSERT(testG.coins == G.coins + newCoins);

	printf("Test if embargo is adding token to supply pile\n");
	ASSERT(testG.embargoTokens[0] == G.embargoTokens[0] + token);

	printf("Test if embargo is altering number of players in game state\n");
	cardEffect(cutpurse, 0, 0, 0, &testG, 0, 0);
	printf("Current Players: %d , Expected Players: %d\n", testG.numPlayers, G.numPlayers);
	ASSERT(testG.numPlayers == G.numPlayers);

	printf("Test if embargo is altering whoseTurn in gameplay\n");
	ASSERT(testG.whoseTurn == G.whoseTurn);

	printf("Test whether discarded card is embargo\n");
	ASSERT(testG.playedCards[0] == embargo);

	printf("Test embargo does not alter number of actions\n");
	ASSERT(testG.numActions == G.numActions);
	
	printf("Test if embargo alters the number of buys");
	ASSERT(testG.numBuys == G.numBuys);

	printf("Test if victory card piles are altered\n");
	int victoryCards = 24;
	ASSERT(testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province] == victoryCards);



}