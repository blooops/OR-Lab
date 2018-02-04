all: main
	
main: main.o
	gcc -o main main.o -std=c99

main.o: main.c util.h lpp.h
	gcc -c -o main.o main.c -std=c99

clear:
	rm *.o main
