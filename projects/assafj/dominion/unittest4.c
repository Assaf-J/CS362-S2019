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


	printf("\n>>>>>Testing Steward Card<<<<<\n\n");
	struct gameState G, testG;
	int seed = 1000;
	int newCards = 3;
	int discard = 1;
	int newCoins = 2;
	int trashedCards = 2;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	if(G.handCount[1] == 0);
	if (G.handCount[1] == 0)
	{

		printf("Testing if choice 1 results in 2 new cards");
		testG.hand[1][0] = steward;
		testG.handCount[1] = 1;


		printf("\nCurrent Hand Before Card: %d , Expected Hand Before Card: %d\n", testG.handCount[1], G.handCount[1]+1);
		stewardCard(1, 1, &testG, 0, 0, 0);
		printf("Current Hand: %d , Expected Hand: %d\n", testG.handCount[1], G.handCount[1] + 2);
		ASSERT(testG.handCount[1] == G.handCount[1] + newCards-discard);

		printf("Testing played adventure card is discarded\n");
		printf("Current Discard: %d , Expected Discard %d\n", testG.playedCardCount, G.playedCardCount + discard);
		ASSERT(testG.playedCardCount == G.playedCardCount + discard);
	

		printf("Testing if choice 2 results in 2 new coins\n");
		memcpy(&testG, &G, sizeof(struct gameState));
		printf("\nCurrent Coins Before Card: %d , Expected Coins Before Card: %d\n", testG.coins, G.coins);
		stewardCard(2, 1, &testG, 0, 0, 0);
		printf("Current Coins: %d , Expected Coins: %d\n", testG.coins, G.coins+newCoins);
		ASSERT(testG.coins == G.coins + newCoins);

		printf("Testing if choice 2 results in 2 discarded cards");
		memcpy(&testG, &G, sizeof(struct gameState));
		testG.hand[1][0] = steward;
		testG.hand[1][1] = copper;
		testG.hand[1][2] = silver;
		testG.handCount[1] = 3;

		printf("Current Hand Before Card: %d , Expected Hand Before Card: %d\n", testG.handCount[1], G.handCount[1] + 3);
		stewardCard(3, 1, &testG,1, 2, 0);
		printf("Current Hand: %d , Expected Hand: %d\n", testG.handCount[1], G.handCount[1]+3-trashedCards);
		ASSERT(testG.handCount[1] == G.handCount[1] + 3 - trashedCards);


		printf(">>>>Testing complete  <<<<<\n\n");

	}
	else
	{
		printf("Failure to initialize game, HandCount != 0");
	}
	return 0;

}