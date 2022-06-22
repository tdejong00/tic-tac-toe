INC = include
SRC = src

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

COMPILER = g++
PARAMETERS = -c -Wall -Wextra -Wpedantic -Wshadow -Wconversion -std=c++17

TARGET = tic-tac-toe
OBJECTS = tic-tac-toe.o main.o

all: $(OBJECTS)
	$(COMPILER) $(OBJECTS) -o $(TARGET)

tic-tac-toe.o: ./$(SRC)/tic-tac-toe.cc ./$(INC)/tic-tac-toe.h
	$(COMPILER) $(PARAMETERS) ./$(SRC)/tic-tac-toe.cc

main.o: main.cc ./$(INC)/tic-tac-toe.h
	$(COMPILER) $(PARAMETERS) main.cc

install:
	install $(TARGET) $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)