CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

mainmat: macro.c main.c sentence_parser.c sentence_parser.h macro.h
	$(CC) $(CFLAGS) -o main macro.c main.c sentence_parser.c