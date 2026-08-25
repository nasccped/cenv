CC=gcc
SRC=./src
FILES=$(wildcard $(SRC)/*.c)
CFLAGS=-Wall -Wextra -Werror
FINAL_BINARY=cenv
DEFINE_VALUES=-DAPP_NAME='"$(FINAL_BINARY)"' \
							-DTAG_ANNOTATION='"$(shell git describe --tags --abbrev=0)"' \
							-DSHORT_COMMIT_HASH='"$(shell git describe | sed 's/.*-g//')"' \
							-DFULL_COMMIT_HASH='"$(shell git rev-parse HEAD)"' \
							-DCOMMIT_DATE='"$(shell git log -1 --format=%cs)"'

build: $(FILES)
	$(CC) $^ -o $(FINAL_BINARY) $(CFLAGS) $(DEFINE_VALUES)

fmt:
	clang-format -i src/*.c src/*.h --style=Microsoft

.PHONY: build
