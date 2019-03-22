FLAGS := -std=c99

all: prog

prog: main.o geometry.o
	gcc -Wall main.o geometry.o -o main -lm $(FLAGS)
main.o: main.c
	gcc -Wall -c main.c -o main.o -lm $(FLAGS)
geometry.o: geometry.c
	gcc -Wall -c geometry.c -o geometry.o $(FLAGS)

clean:
	rm -f *.o
	main
