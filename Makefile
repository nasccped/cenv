CC=gcc
SRC=./src
FILES=$(wildcard $(SRC)/*.c)
CFLAGS=-Wall -Wextra -Werror
FINAL_BINARY=cenv
DEFINE_VALUES=-DAPP_NAME='"$(FINAL_BINARY)"' -DTAG_NAME='"temp-tag"' -DTAG_COMMIT_HASH='"temp-hash"' \
							-DTAG_COMMIT_DATE='"0000-00-00"'

build: $(FILES)
	$(CC) $^ -o $(FINAL_BINARY) $(CFLAGS) $(DEFINE_VALUES)

fmt:
	clang-format -i src/*.c src/*.h --style=Microsoft

.PHONY: build
