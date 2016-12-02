/*-----------------------------------------------------------------------------+ 
File Name: Game.c
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
 * dealPlayers function assigns to each player the specified amount of 
 *             cards from the deck
 * @param deck        deck to get the cards from
 * @param players     players to deal the cards
 * @param gamePlayers amount of players
 * @param cardsToDeal amount of cards to deal to the players
 */
void dealPlayers( Deck *deck, 
  Player players[], 
  int gamePlayers, 
  int cardsToDeal){

  int index;
  int cardsIndex;

  for(index = 0; index < gamePlayers; index++){      
    createPlayer(&players[index], cardsToDeal, deck->cards);
    deck->cards += cardsToDeal;
    deck->cardsAmt -= cardsToDeal;
  }
}


/*-----------------------------------------------------------------------------+
 * [finds a winner or more and displays them]
 * @param players     [list of players]
 * @param gamePlayers [amount of payers]
 */
void findWinner(Player players[], int gamePlayers){

    int index;
    int winner = 0;
    for (index = 1; index < gamePlayers; index++){  
     winner = (players[index].rank > players[winner].rank)? index : winner;       
   }
  
   printf(
    "\n\n%s\n|%40s%d%s%40s|\n%s\n",
    "+--------------------------------------------"
    "--------------------------------------------+", 
    "Player ",
    (winner + OFFSET),
    " WINNER",       
    "",
    "+--------------------------------------------"
    "--------------------------------------------+" 
    );    
   displayPlayer(&players[winner]);
  
   for (index = 0; index < gamePlayers; index++){
  
    if (index != winner){
      if (players[index].rank == players[winner].rank ){
        printf(
          "\n\n%s\n|%40s%d%s%40s|\n%s\n",
          "+--------------------------------------------"
          "--------------------------------------------+", 
          "Player ",
          (winner + OFFSET),
          " WINNER",       
          "",
          "+--------------------------------------------"
          "--------------------------------------------+" 
          );    
        displayPlayer(&players[winner]);
      }
    }
  }
}

/*-----------------------------------------------------------------------------+
 * [gives a rank to each player]
 * @param players     [players to be ranked]
 * @param gamePlayers [amount of players]
 */
void rankPlayers( Player players[], int gamePlayers ){
  int index;

  for ( index = 0; index < gamePlayers; ++index ){
    rankPlayer( &players[index] );
  }
}

/*-----------------------------------------------------------------------------+
 *  validateGame ensures that all required parameters 
 *         are present and valid for the program to run
 * @param  argc        argument counter
 * @param  argv        program arguments
 * @param  cardsToDeal amount of cards to be assign for dealing
 * @param  gamePlayers amount of players to be assign for the game 
 * @return             TRUE if it is a valid game and FALSE if not valid
 */
Boolean validateGame( 
                      int argc, char **argv, 
                      int *cardsToDeal, int *gamePlayers){

    int total_cards = 0;
  
    if ( argc == GAME_ARG) {
      *cardsToDeal = atoi(argv[ARG_1]);       
      *gamePlayers = atoi(argv[ARG_2]);
  
      total_cards = (*cardsToDeal) * (*gamePlayers);
  
      if (*gamePlayers <= MAX_PLAYERS &&
        *cardsToDeal <= MAX_CARDS &&
        total_cards <= DECK_CARDS){
        return TRUE;
    }else{
      printf(
        "%s\n\n%s\n%s%d%s%d%s\n%s\n\n%s\n\n",
        "+--------------------------------------------"
        "--------------------------------------------+",
        "The amount of players or card per players are not valid",
        "This game requires a max of ",
        MAX_PLAYERS,
        " players, ",
        MAX_CARDS, 
        " cards per player,",
        "and the sum of all the cards per players can't be more than 52",
        "+--------------------------------------------"
        "--------------------------------------------+"
        );
      return FALSE;
    }  
  
  }else{
    printf("%s\n\n%s\n%s\n\n%s\n\n%s\n\n",
      "+--------------------------------------------"
      "--------------------------------------------+",
      "This program requires two arguments for the amount of,",
      "cards per player and the amount of players. ",
      "./poker [#Cards][#Players]",
      "+--------------------------------------------"
      "--------------------------------------------+"
      );
    return FALSE;
  }
}