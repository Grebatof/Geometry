FLAGS := -std=c99
FLAG := -std=c11
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./build
OBJ_TEST_DIR := ./build/test
TEST_DIR := ./test
.PHONY: clean install uninstall all run

all: $(BIN_DIR)/main $(BIN_DIR)/testing

$(BIN_DIR)/main:  $(OBJ_DIR)/main.o  $(OBJ_DIR)/geometry.o  $(OBJ_DIR)/input.o $(OBJ_DIR)/processing.o
	gcc -Wall -Wextra  $(OBJ_DIR)/main.o  $(OBJ_DIR)/geometry.o  $(OBJ_DIR)/input.o $(OBJ_DIR)/processing.o -o $(BIN_DIR)/main -lm $(FLAGS)


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/main.c -o  $(OBJ_DIR)/main.o -lm $(FLAGS)


$(OBJ_DIR)/processing.o: $(SRC_DIR)/processing.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/processing.c -o  $(OBJ_DIR)/processing.o -lm $(FLAGS)


$(OBJ_DIR)/geometry.o: $(SRC_DIR)/geometry.c
		gcc -Wall -Wextra -c  $(SRC_DIR)/geometry.c -o  $(OBJ_DIR)/geometry.o -lm $(FLAGS)


$(OBJ_DIR)/input.o: $(SRC_DIR)/input.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/input.c -o  $(OBJ_DIR)/input.o -lm $(FLAGS)

#gcc ./test/*.c ./src/geometry.c -lm -std=c11

$(BIN_DIR)/testing: $(OBJ_TEST_DIR)/main.o $(OBJ_TEST_DIR)/input.o $(OBJ_TEST_DIR)/processing.o $(OBJ_TEST_DIR)/geometry.o $(OBJ_DIR)/geometry.o $(OBJ_DIR)/input.o $(OBJ_DIR)/processing.o
	gcc $(OBJ_TEST_DIR)/main.o  $(OBJ_TEST_DIR)/geometry.o  $(OBJ_TEST_DIR)/input.o $(OBJ_TEST_DIR)/processing.o $(OBJ_DIR)/geometry.o $(OBJ_DIR)/processing.o $(OBJ_DIR)/input.o -o $(BIN_DIR)/testing -lm $(FLAG)


$(OBJ_TEST_DIR)/processing.o: $(TEST_DIR)/processing.c
	gcc -c $(TEST_DIR)/processing.c -o  $(OBJ_TEST_DIR)/processing.o $(FLAG)


$(OBJ_TEST_DIR)/main.o: $(TEST_DIR)/main.c
	gcc -c $(TEST_DIR)/main.c -o  $(OBJ_TEST_DIR)/main.o $(FLAG)


$(OBJ_TEST_DIR)/geometry.o: $(TEST_DIR)/geometry.c
	gcc -c $(TEST_DIR)/geometry.c -o  $(OBJ_TEST_DIR)/geometry.o -lm $(FLAG)


$(OBJ_TEST_DIR)/input.o: $(TEST_DIR)/input.c
	gcc -c $(TEST_DIR)/input.c -o  $(OBJ_TEST_DIR)/input.o $(FLAG)

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/main


run: all
#	$(BIN_DIR)/main
	$(BIN_DIR)/testing

install:
	sudo cp ./bin/main /usr/bin/main

uninstall:
	sudo rm -f /usr/bin/main
