CC = gcc
L_FLAGS = -Wall
NAME = DataBlockTest

all: bin/$(NAME)

bin/$(NAME): src/DataBlockTest.c
	$(CC) $(L_FLAGS) $^ -o $@
