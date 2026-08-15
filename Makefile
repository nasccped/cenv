CC=gcc
SRC=./src
FILES=$(wildcard $(SRC)/*.c)
CFLAGS=-Wall -Wextra -Werror

build: $(FILES)
	$(CC) $^ -o cenv $(CFLAGS)

.PHONY: build
