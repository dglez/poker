/*-----------------------------------------------------------------------------+ 
File Name:  Main.c
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
             and a winner hand.


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
/* Include structures, prototypes and libraries for the program


+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------+
 * deck main function Pseudo-code:
    .Validate input 
      .Create Deck
      .display Deck
      .shuffle Deck
        .iterate over the deck swapping a random 
         number with the current index
      .Display Deck
      .Create players
      .Deal cards to Players 
          .copy consecutive sections of deck with 
           amount of cards to deal for each player      
      .organize Players cards
        .sort cards of each player 
      .rank players      
      .Display Players cards
      .Display cards left on deck
      .find and display winner 
 
 */
int main(int argc, char *argv[]){

    int cardsToDeal;
    int gamePlayers;


    if (validateGame(argc, argv, &cardsToDeal, &gamePlayers)){


        Deck deck;
        createDeck(&deck);
        displayDeck(&deck);
        shuffle(&deck);
        printf("\n\n%57s\n"," ----- SHUFFLING ------" );
        displayDeck(&deck);

        Player players[gamePlayers];

        dealPlayers(&deck, players, gamePlayers, cardsToDeal);
        organizePlayers(players, gamePlayers); 
        rankPlayers(players, gamePlayers);  
        displayPlayers(players, gamePlayers);    
        displayDeck(&deck);
        findWinner(players, gamePlayers);




    }

    return NOERRORS;

}