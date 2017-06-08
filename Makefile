CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = intstack.o treestack.o queue.o huffman.o

.PHONY: all
all: encode decode

encode: $(OBJECTS) encode.o
	$(CC) $(CFLAGS) encode.o $(OBJECTS) $(CFLAGS) -g -o encode -lm

decode: $(OBJECTS) decode.o
	$(CC) $(CFLAGS) decode.o $(OBJECTS) $(CFLAGS) -g -o decode -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c -g encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c -g decode.c

intstack.o: intstack.c
	$(CC) $(CFLAGS) -c -g intstack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c -g queue.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c -g huffman.c

treestack.o: treestack.c
	$(CC) $(CFLAGS) -c -g treestack.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) encode.o decode.o encode decode

