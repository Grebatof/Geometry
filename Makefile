FLAGS := -std=c99
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./build
.PHONY: clean install uninstall all run

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/geometry.o $(OBJ_DIR)/processing.o $(OBJ_DIR)/input.o
	gcc -Wall -Wextra $(OBJ_DIR)/main.o $(OBJ_DIR)/geometry.o $(OBJ_DIR)/processing.o $(OBJ_DIR)/input.o -o $(BIN_DIR)/main -lm $(FLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/main.c -o  $(OBJ_DIR)/main.o -lm $(FLAGS)

$(OBJ_DIR)/geometry.o: $(SRC_DIR)/geometry.c
		gcc -Wall -Wextra -c  $(SRC_DIR)/geometry.c -o  $(OBJ_DIR)/geometry.o -lm $(FLAGS)

$(OBJ_DIR)/processing.o: $(SRC_DIR)/processing.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/processing.c -o  $(OBJ_DIR)/processing.o -lm $(FLAGS)

$(OBJ_DIR)/input.o: $(SRC_DIR)/input.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/input.c -o  $(OBJ_DIR)/input.o $(FLAGS)

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/main

run: all
	$(BIN_DIR)/main

install:
	sudo cp ./bin/main /usr/bin/main

uninstall:
	sudo rm -f /usr/bin/main
