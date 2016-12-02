/*-----------------------------------------------------------------------------+ 
File Name: Main.h
+------------------------------------------------------------------------------+

+------------------------------------------------------------------------------+
   Programming III COP4338
   Author: Daniel Gonzalez P#4926400
   assignment 3: Deck of Cards
   Date: 10/20/2016

  program description
     Input: Accept input via the command-line arguments. Validate command-line
     input. Input will be the number of cards/hand and the number of 
     hands ( players ), in that order.

     Output: Display of a deck of cards and hands of cards.


  +-------------------------------------------------------------------------+
  | I Daniel Gonzalez #4926400 hereby certify that this collective work is  |
  | my own and none of it is the work of any other person or entity.        |
  +-------------------------------------------------------------------------+
  

  how to compile and execute:
    1.Open the terminal
        Go to the program folder
        Run the following command "make"

    2.Open the terminal
        Go to the program folder
        Run the following command 
        "gcc -Wall -w -lm Main.c Game.c Deck.c Card.c Player.c -o poker"

    Program execution:
    From the terminal enter “./poker [#Cards][#Players]"
    both arguments are required

+-----------------------------------------------------------------------------*/































#include <stdio.h>
#include <stdlib.h>             /* using rand and malloc */
                                /* in Deck.c and Player.c*/
#include <time.h>               /* using time_t in Deck.c file*/
#include <math.h>               /* using double pow(double,double) in Player.c*/


#define NOERRORS 0              /* for clean return */
#define OFFSET 1                /* for array offset value*/
#define DECK_CARDS 52           /* total of cards on the deck */
#define GAME_ARG 3              /* total arguments of the program */
#define NUM_SUITS 4             /* maximum number of card suits */
#define NUM_FACES 13            /* maximum number of card faces */
#define MAX_PLAYERS 7           /* maximum amount of players player.*/
#define MAX_CARDS 5             /* maximum amount of cards per player.*/
#define ARG_1 1                 /* first argument*/
#define ARG_2 2                 /* Second argument*/
#define CLUB "\xe2\x99\xa3"     /* club char UTF-8 */
#define DIAMOND "\xe2\x99\xa6"  /* diamond char UTF-8 */
#define HEART "\xe2\x99\xa5"    /* heart char UTF-8 */
#define SPADE "\xe2\x99\xa0"    /* spade char UTF-8 */


#define HIGH_4 13               /*required to ensure rank 13^1*/
#define HIGH_3 169              /*required to ensure rank 13^2*/
#define HIGH_2 2197             /*required to ensure rank 13^3*/
#define HIGH_1 28561            /*required to ensure rank 13^4*/
#define PAIR 399655             /* 1 Pair base value */
#define TWO_PAIR 799182         /* 2 Pair base value */
#define THREE_KIND 1196851      /* three of a kind base value */
#define STRAIGHT 1196865        /* straight base value */
#define FLUSH 1196879           /* Flush base value */
#define FULLHOUSE 1596534       /* Full house base value */
#define FOUR_KIND 1596548       /* four Of a kind base value */
#define STRAIGHT_FLUSH 1596562  /* straight flush base value */
#define FACE_A 0                /* face A to compare for highest straight*/
#define FACE_10 9               /* face 10 to compare for highest straight */
#define HIGH_A 13               /* Face A high value */
#define STRAIGHT_COUNT 4        /* Require count to be straight */
#define FLUSH_COUNT 4           /* Require count to be flush */
#define FOUR_COUNT 3            /* Require count to be Four of a kind*/
#define TRIO_COUNT 2            /* Require count to be three of a kind*/
#define PAIR_COUNT 1            /* Require count to be three of a kind*/

/* Use for boolean expressions */
typedef enum boolean{ 
  FALSE, 
  TRUE 
}Boolean;     

/* Type definitions  and structures*/ 
typedef char * String;
typedef struct Card {
  int face;
  int suit;
}Card;

typedef struct Deck {    
  Card * cards;
  int cardsAmt;  
}Deck;

typedef struct Player
{
  int cardsAmt;
  long rank;
  String hand;
  struct Card *cards;
}Player;


/*-----------------------------------------------------------------------------+     
*    Function prototypes: 
*    Function declarations are listed as 
*    below in their files.
*    
*    Game.c prototypes
*/

void dealPlayers ( Deck *, Player[], int , int );
void findWinner(Player[], int);
void rankPlayers(Player[], int);
Boolean validateGame ( int, char **, int *, int * );


/*-----------------------------------------------------------------------------+
    Deck.c prototypes
*/
void createDeck ( Deck * );
void displayDeck ( Deck * );
void shuffle ( Deck * );
void swap ( Card *, Card * );


/*-----------------------------------------------------------------------------+
    Player.c prototypes
*/

void createPlayer ( Player *, int , Card * );
void displayPlayer ( Player * );
void displayPlayers ( Player[], int );
long ScoreflushOrStraight(Player *);
long ScoreFaceRepeated(Player *);
void organizePlayers ( Player [], int );
void rankPlayer(Player *);
void sortCards ( Player * );

/*-----------------------------------------------------------------------------+
    Card.c prototypes
*/
void displayCard ( Card * );
void displayTopCards ( int );
void displayBottomCards ( int );

/*----------------------------------------------------------------------------*/