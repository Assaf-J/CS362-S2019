
CFLAGS= -Wall -fpic -coverage -lm -std=c99 -coverage

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestresults: randomtestcard1.c dominion.o rngs.o
	echo "randomtestcard1.c:" >> randomtestresults.out
	gcc -o randomtestcard1 dominion.o rngs.o randomtestcard1.c $(CFLAGS)
	./randomtestcard1 >>randomtestresults.out
	
	echo "randomtestcard2.c:" >> randomtestresults.out
	gcc -o randomtestcard2 dominion.o rngs.o randomtestcard2.c $(CFLAGS)
	./randomtestcard2 >>randomtestresults.out

	echo "randomtestadventurer.c:" >> randomtestresults.out
	gcc -o randomtestadventurer dominion.o rngs.o randomtestadventurer.c $(CFLAGS)
	./randomtestadventurer >>randomtestresults.out


	gcov dominion.c -fb>> randomtestresults.out

all: randomtestresults player 

clean:
	rm  tests.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
