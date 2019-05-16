FLAGS := -std=c99

all: prog

prog: main.o geometry.o processing.o input.o
	gcc -Wall main.o geometry.o input.o processing.o -o main -lm $(FLAGS)
main.o: main.c
	gcc -Wall -c main.c -o main.o -lm $(FLAGS)
geometry.o: geometry.c
	gcc -Wall -c geometry.c -o geometry.o $(FLAGS)
input.o: input.c
	gcc -Wall -c input.c -o input.o -lm $(FLAGS)
processing.o: processing.c
	gcc -Wall -c processing.c -o processing.o -lm $(FLAGS)

clean:
	rm -f *.o
	main
