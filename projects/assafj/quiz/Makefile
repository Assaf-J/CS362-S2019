
CFLAGS= -Wall -fpic -coverage -lm -std=c99 -coverage

tester: testme.c
	gcc -o testme testme.c -g $(CFLAGS)
	./testme 
	gcov testme.c -fb



all: tester

clean:
	rm  testme  *.gcov *.gcda *.gcno 
