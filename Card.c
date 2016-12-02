/*-----------------------------------------------------------------------------+ 
File Name:  Card.c
+------------------------------------------------------------------------------+

+------------------------------------------------------------------------------+
   Programming III COP4338
   Author: Daniel Gonzalez P#4926400
   assignment 3: Deck of Cards
   Date: 10/20/2016

  program description
     Input: Accept input via the command-line arguments. Validate command-line
     input. Input will be the number of cards/hand and the number of 
     hands(players), in that order.

     Output: Display of a deck of cards, cards of each hands after dealing 
             and a winner hand..


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































#include "Main.h"   
/* Include structures, prototypes and libraries for the program */




/*-----------------------------------------------------------------------------+
 * [displayCard Displays a card
 * @param card Card to be displayed
 */
void displayCard(Card *card)
{
    const  char *FACES[] = {"A","2","3","4",
                           "5","6","7","8","9",
                           "10","J","Q","K"};
    const  char *TYPE[] = {SPADE, CLUB,DIAMOND, HEART};                  


   printf("|%2s%2s | ", FACES[card->face], TYPE[card->suit]);
}



/*-----------------------------------------------------------------------------+
 * [displayBottomCards displays the bottom of the cards in a line
 * @param cardsPerLine amount of cards per line
 */
void displayBottomCards(int cardsPerLine){

    printf("%s\n","" );
    int i;
    for (i = 0; i < cardsPerLine; i++){
        printf("|%4s| ","" );
    }

    printf("%s\n","" );

    for (i = 0; i < cardsPerLine; i++){
        printf("%s ","+----+" );
    }
    printf("%s\n","" );

}



/*-----------------------------------------------------------------------------+
 * [displayTopCards displays the top of the cards in a line
 * @param cardsPerLine amount of cards per line
 */
void displayTopCards(int cardsPerLine){

    
    int i;
    for (i = 0; i < cardsPerLine; i++){
        printf("%s ","+----+" );
    }
    printf("%s\n","" );

    for (i = 0; i < cardsPerLine; i++){
        printf("|%4s| ","" );
    }
    printf("%s\n","" );

}