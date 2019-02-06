CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme:
	gcc -o testme -g testme.c $(CFLAGS)
	./testme

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out
