CC = gcc
CFLAGS = -Wall -ansi -pedantic

mainmat: main.c sentence_parser.c sentence_parser.h
	$(CC) $(CFLAGS) -o main main.c sentence_parser.c