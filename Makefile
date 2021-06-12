CC = gcc
VPATH = src/sources
EXEC = bin/pacman
SRC = $(wildcard src/sources/*.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

%.o : %.c
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

.PHONY : clean mrproper
clean :
	del /s *.o

mrproper : clean
	del /s pacman.exe