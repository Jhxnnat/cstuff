CC = gcc
CFLAGS = -Wall -Wextra

SRC = ./strlib.c
OBJ = $(SRC:.c=.o)
DEST = ./strlib

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
