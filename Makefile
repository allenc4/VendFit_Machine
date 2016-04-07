CC=g++
CFLAGS=-c -Wall -lstdc++ -lpigpio -lrt
SRC=./src
INC=./inc
BIN=./bin

all: main

main: Dispenser.o VendFitClient.o VendingMachine.o main.o
	$(CC) $(BIN)/main.o $(BIN)/VendingMachine.o $(BIN)/VendFitClient.o $(BIN)/Dispenser.o -o $(BIN)/VendFitMachine

main.o: 
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $(BIN)/main.o

VendingMachine.o:
	$(CC) $(CFLAGS) $(SRC)/VendingMachine.cpp -o $(BIN)/VendingMachine.o

VendFitClient.o:
	$(CC) $(CFLAGS) $(SRC)/VendFitClient.cpp -o $(BIN)/VendFitClient.o

Dispenser.o:
	$(CC) $(CFLAGS) $(SRC)/Dispenser.cpp -o $(BIN)/Dispenser.o

clean:
	rm $(BIN)/*.o $(BIN)/VendFitMachine
