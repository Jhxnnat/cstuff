CC = gcc
CFLAGS = #-Wall -Wextra

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEST = ./main

all: $(DEST)

$(DEST): $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEST)

# run: all
# 	@./$(DEST) $(arg)

.PHONY: all clean
