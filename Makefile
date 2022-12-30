myset: myset.o parse.o set.o
	gcc -std=c90 -Wall -ansi -pedantic -o dist/myset dist/myset.o dist/parse.o dist/set.o

myset.o: myset.c parse.h set.h
	gcc -std=c90 -Wall -ansi -pedantic -c -o dist/myset.o myset.c

parse.o: parse.c parse.h set.h
	gcc -std=c90 -Wall -ansi -pedantic -c -o dist/parse.o parse.c

set.o: set.h set.c
	gcc -std=c90 -Wall -ansi -pedantic -c -o dist/set.o set.c