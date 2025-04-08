CC=gcc
CFLAGS=-Wall -Wextra -O2 -lcurl

SRC=src/main.c
BIN=bin/send_mail

all: directories $(BIN)

directories:
	mkdir -p bin

$(BIN): $(SRC)
	$(CC) $(SRC) -o $(BIN) $(CFLAGS)

clean:
	rm -rf bin/*.o $(BIN)

.PHONY: all clean directories

