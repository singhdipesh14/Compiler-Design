run: main.o
	gcc -o parse main.o

main.o: main.c rdParser.h hash.h tables.h structs.h utils.h constants.h removePreprocess.h removeExcess.h getNextToken.h
	gcc -c main.c
