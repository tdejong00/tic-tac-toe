INC = include
SRC = src

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

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

install:
	install $(TARGET) $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)