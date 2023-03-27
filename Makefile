# replace CC for your preferred compiler

CC=clang    # compiler
TARGET=pgen # taget name

all:
	$(CC) main.c words.c -o $(TARGET)
