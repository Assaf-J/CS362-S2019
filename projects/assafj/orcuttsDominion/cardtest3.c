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

	printf("\n>>>>>Testing Cutpurse Card<<<<<\n\n");
	struct gameState G, testG;
	int seed = 1000;
	int newCoins = 2;
	int discard = 1;

	int numPlayers = 2;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	//add cutpurse to player 0 hand
	testG.hand[0][0] = cutpurse;
	testG.handCount[0] = 1;

	//add copper to player 1 hand
	testG.hand[1][0] = copper;
	testG.handCount[1] = 1;

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(cutpurse, 0, 0, 0, &testG, 0, 0);

	

	printf("Test if cutpurse adds two to the total coins\n");
	printf("Expected Coins = %d, Actual Coins = %d\n", G.coins + newCoins, testG.coins);
	ASSERT(testG.coins == G.coins + newCoins);

	printf("Test if other player has one less card in hand\n");
	ASSERT(testG.handCount[1] == G.handCount[1] +1-discard);

	printf("Test if discarded card is a copper card\n");
	ASSERT(testG.playedCards[0] == copper);

	printf("Test if Cutpurse is altering number of players in game state\n");
	cardEffect(cutpurse, 0, 0, 0, &testG, 0, 0);
	printf("Current Players: %d , Expected Players: %d\n", testG.numPlayers, G.numPlayers);
	ASSERT(testG.numPlayers == G.numPlayers);

	printf("Test if cutpurse is altering whoseTurn in gameplay\n");
	ASSERT(testG.whoseTurn == G.whoseTurn);

	printf("Test whether discarded card is cutpurse\n");
	ASSERT(testG.playedCards[1] == cutpurse);

	printf("Test cutpurse does not alter number of actions\n");
	ASSERT(testG.numActions == G.numActions);

	printf("Test if cutpurse alters the number of buys");
	ASSERT(testG.numBuys == G.numBuys);

	printf("Test if victory card piles are altered\n");
	int victoryCards = 24;
	ASSERT(testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province] == victoryCards);



}