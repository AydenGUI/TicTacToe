# fixed Makefile ---
CFLAGS = -g -Wall -pedantic
CC = gcc

all :  \
	clearscreen \
	tictactoe

clearscreen: clearscreen.o
	$(CC) $(CFLAGS) $^ -o $@  -lncurses

tictactoe: tictactoe.o 
	$(CC) $(CFLAGS) $@.o -o $@ 

%: %.o
	$(CC) $(CFLAGS) $^ -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f clearscreen
	rm -f tictactoe
	rm -f *.o a.out
	rm -rf *.dSYM
