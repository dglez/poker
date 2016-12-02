/*-----------------------------------------------------------------------------+ 
File Name: Deck.c
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
 * [createDeck initialized a new organized deck 
 * @param deck deck to be initialized
 */
void createDeck(Deck *deck){

    int faceIndex; 
    int suitIndex; 
    int deckIndex = 0;

    deck->cards = (Card *)malloc(sizeof(Card) * DECK_CARDS);
    deck->cardsAmt = DECK_CARDS;

    for (suitIndex = 0; suitIndex < NUM_SUITS; suitIndex++) {

        for (faceIndex = 0 ; faceIndex < NUM_FACES; faceIndex++) {

            deck->cards[deckIndex].face = faceIndex;
            deck->cards[deckIndex].suit = suitIndex;
            deckIndex++;
        }
        
    } 
}













































/*-----------------------------------------------------------------------------+
 * [displayDeck Displays all the cards in the deck
 * @param deck Deck to be displayed
 */
void displayDeck(Deck *deck){

    int index;
    int topCards, bottomCards;
    int deckRemainder = deck->cardsAmt % NUM_FACES;
    Boolean nextLine;

    printf(
        "\n\n\n%s\n|%50s%38s|\n%s\n",
        "+--------------------------------------------"
        "--------------------------------------------+",
        "CURRENT DECK",
        "",
        "+--------------------------------------------"
        "--------------------------------------------+"
        );

    
    displayTopCards((NUM_FACES >= deck->cardsAmt )? deckRemainder : NUM_FACES );
    for ( index = 0; index < deck->cardsAmt ; index++ ) {

        nextLine = ((( index + OFFSET ) % NUM_FACES ) == 0 )? TRUE : FALSE;        

        displayCard( &( deck->cards[index] ));         

        if ( nextLine && index < ( deck->cardsAmt - OFFSET ) ){
            displayBottomCards( NUM_FACES % deck->cardsAmt );            
            
            topCards = (index >= ( deck->cardsAmt - NUM_FACES ))?
                                 (( deckRemainder == 0 )? 
                                     NUM_FACES :
                                     deckRemainder ):
                                 NUM_FACES;

            displayTopCards(topCards);
        }        
    } 
    bottomCards = ( deckRemainder == 0 )? NUM_FACES : deckRemainder;
    displayBottomCards( bottomCards );
    
}



/*-----------------------------------------------------------------------------+
 * [shuffle Shuffles the cards from the deck
 * @param deck Deck to be shuffled
 */
void shuffle(Deck *deck){

    int pos = 0;
    int index = 0;
    time_t t;

    srand((unsigned) time(&t));

    for( index = 0 ; index < DECK_CARDS ; index++ ) {
        pos = rand() % DECK_CARDS;
        swap(&(deck->cards[index]), &(deck->cards[pos]));        

    }


}


/*-----------------------------------------------------------------------------+
 * [swap helper function for shuffle swaps tow cards in a deck
 * @param card1 card1 to be swap
 * @param card2 card to be swap with card1
 */
void swap(Card *card1, Card *card2 ){

    Card tempCard;
    tempCard = *card1;
    *card1 = *card2;
    *card2 = tempCard;

}