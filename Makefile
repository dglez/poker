#/*-----------------------------------------------------------------------------+ 
#File Name:  Makefile
#+------------------------------------------------------------------------------+
#
#+------------------------------------------------------------------------------+
#   Programming III COP4338
#   Author: Daniel Gonzalez P#4926400
#   assignment 3: Deck of Cards
#   Date: 10/20/2016
#
#  program description
#     Input: Accept input via the command-line arguments. Validate command-line
#     input. Input will be the number of cards/hand and the number of 
#     hands(players), in that order.
#
#     Output: Display of a deck of cards, cards of each hands after dealing 
#             and a winner hand..
#
#
#  +-------------------------------------------------------------------------+
#  | I Daniel Gonzalez #4926400 hereby certify that this collective work is  |
#  | my own and none of it is the work of any other person or entity.        |
#  +-------------------------------------------------------------------------+
#  
#
#  how to compile and execute:
#    1.Open the terminal
#        Go to the program folder
#        Run the following command "make"
#
#    2.Open the terminal
#        Go to the program folder
#        Run the following command 
#        "gcc -Wall -w -lm Main.c Game.c Deck.c Card.c Player.c -o poker"
#
#    Program execution:
#    From the terminal enter “./poker [#Cards][#Players]"
#    both arguments are required
#
#+-----------------------------------------------------------------------------*/

CC = gcc
FLAGS = -Wall -w -lm
EXE = poker
OUT = -o
HEADER = Main.h
OBJS = Main.o Game.o Deck.o Card.o Player.o
SOURCE = Main.c Game.c Deck.c Card.c Player.c


$(EXE): $(OBJS)
	$(CC) $(FLAGS) $(SOURCE) $(OUT) $(EXE) 


Game.o:$(HEADER)
Deck.o:$(HEADER)
Card.o:$(HEADER)
Player.o:$(HEADER)

.PHONY:	clean
clean:
	rm *.o