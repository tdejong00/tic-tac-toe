INC = include
SRC = src

COMPILER = g++
PARAMETERS = -c -Wall -Wextra -Wpedantic -Wshadow -Wconversion -std=c++17

TARGET = tic-tac-toe
OBJECTS = tictactoe.o main.o

all: $(OBJECTS)
	$(COMPILER) $(OBJECTS) -o $(TARGET)

tictactoe.o: ./$(SRC)/tictactoe.cc ./$(INC)/tictactoe.h
	$(COMPILER) $(PARAMETERS) ./$(SRC)/tictactoe.cc

main.o: main.cc ./$(INC)/tictactoe.h
	$(COMPILER) $(PARAMETERS) main.cc

clean:
	rm -f $(OBJECTS) $(TARGET)