CC = gcc
CFLAGS = -Wall -Wextra
FLAGS = -lpthread

SRC = ./threads.c
OBJ = $(SRC:.c=.o)
DEST = ./threads

all: $(DEST)

$(DEST): $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@ $(FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEST)

# run: all
# 	@./$(DEST) $(arg)

.PHONY: all clean
