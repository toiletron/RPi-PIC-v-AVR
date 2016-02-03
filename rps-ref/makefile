all: rps-ref

rps-ref: main.o
	gcc main.o -lwiringPi -o rps-ref
	
main.o: main.c
	gcc -Wall -c main.c	

clean:
	rm *o rps-ref
