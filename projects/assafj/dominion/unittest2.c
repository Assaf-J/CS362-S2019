
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define MAX_HAND 500


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
	
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Current Hand Before Card: %d , Expected Hand Before Card %d\n", testG.handCount[1], G.handCount[1]);
	
	if (G.handCount[1] == 0)
	{	
		testG.hand[1][0] = adventurer;
		testG.handCount[1] = 1;
		adventurerCard(0, 1, &testG, temphand, 0,0);

		printf("Current Hand: %d , Expected Hand %d\n", testG.handCount[1], G.handCount[1] +1+ newCards-discard);
		

		ASSERT(testG.handCount[1] == G.handCount[1] + newCards- discard);

		int treasures = 0;
		for (int i= 0; i < testG.handCount[1]; i++)
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


		}
		printf("Current Treasure Cards: %d, Expected Treasure Cards: %d\n", treasures, newCards);
		ASSERT(treasures==2);

		printf(">>>>>  Testing complete  <<<<<\n\n");
	}
	else
	{
		printf("Failure to initialize game, HandCount != 0");
	}
	return 0;


}