/*-----------------------------------------------------------------------------+ 
File Name: Player.c
+------------------------------------------------------------------------------+

+------------------------------------------------------------------------------+
   Programming III COP4338
   Author: Daniel Gonzalez P#4926400
   assignment 3: Deck of Cards
   Date: 10/20/2016

  program description
     Input: Accept input via the command-line arguments. Validate command-line
     input. Input will be the number of cards/hand and the number of 
     hands( players ), in that order.

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
/* Include structures, prototypes and libraries for the program


+-----------------------------------------------------------------------------*/

/**
 * [createPlayer creates a player allocating memory for its cards 
 *  and assigns them]
 * @param player      [player to be created]
 * @param cardsToDeal [amount of cards to assign]
 * @param cards       [cards to assign to the player ]
 */
void createPlayer( Player *player, int cardsToDeal, Card *cards ){

    
    player->cards = ( Card * )malloc( sizeof( Card ) * cardsToDeal );

    int i;
    for ( i = 0; i < cardsToDeal; i++ ){
        player->cards[i] = cards[i];

    }
    player->cardsAmt = cardsToDeal;    
    player->rank = 0;

}


/*-----------------------------------------------------------------------------+
 * [displayPlayer displays cards of a player
 * @param player player to be displayed
 */
void displayPlayer( Player *player ){

    int index;
    
    displayTopCards( player->cardsAmt );
    for ( index = 0; index < player->cardsAmt; ++index ){
        displayCard( &( player->cards[index] ) );
    }
    displayBottomCards( player->cardsAmt );
    printf(
        "\n%s\n%s%ld\n%s\n", 
        player->hand, 
        "Score: ", 
        player->rank,
        "+--------------------------------------------"
        "--------------------------------------------+" 
        );    
}



/*-----------------------------------------------------------------------------+
 * [displayPlayers displays the cards and names of the players]
 * @param players     [players to be displayed]
 * @param gamePlayers [amount of players]
 */
void displayPlayers( Player players[], int gamePlayers ){

    int index, playerNum;

    for ( index = 0; index < gamePlayers; index++ )
    {
        playerNum = index + OFFSET;
        printf( 
            "\n\n%s\n|%45s%3d%40s|\n%s\n",
            "+--------------------------------------------"
            "--------------------------------------------+", 
            "Player", 
            playerNum,
            "",
            "+--------------------------------------------"
            "--------------------------------------------+"
             );
        displayPlayer( &players[index] );
    }
}




/*-----------------------------------------------------------------------------+
 * [gives a score for the player hand if it has a 
 *  straight, a flush, or both]
 * @param  player [description]
 * @return        [partial score for the player hand or 0 
 *                 if no flush or straight found]
 */
long ScoreflushOrStraight(Player *player){

    int index, 
    highest, 
    highestStraightA, 
    current, 
    next;
    int straightCount = 0;
    int flushCount = 0;
    long rank = 0;
    int length = player->cardsAmt - OFFSET;

    for(index = length; index > 0; index--){

        current = player->cards[index].face;
        next = player->cards[index - OFFSET].face;

        straightCount += (current == (next - 1))? 1 : 0;

        straightCount += (current == FACE_10 &&    next == FACE_A)? 1 : 0;

        flushCount += (
            player->cards[index].suit == player->cards[index - OFFSET].suit
            )? 1 : 0;            
    }



    highestStraightA = (
        player->cards[1].face == FACE_10 &&
        player->cards[0].face == FACE_A
        )? HIGH_A : player->cards[player->cardsAmt - OFFSET].face;

    highest = (
        player->cards[0].face == FACE_A
        )? HIGH_A : player->cards[player->cardsAmt - OFFSET].face;

    if (straightCount == STRAIGHT_COUNT && flushCount == FLUSH_COUNT)
    {
        player->hand = "Straight Flush";
        rank = STRAIGHT_FLUSH + highestStraightA;
        return rank;
    }else if (straightCount == STRAIGHT_COUNT )
    {
        player->hand = "Straight";
        rank = STRAIGHT + highestStraightA;
        return rank;
    }
    else if (flushCount == FLUSH_COUNT)
    {
        player->hand = "Flush";
        rank = FLUSH + highest;
        return rank;
    }else{
        return rank;
    }
}




/*-----------------------------------------------------------------------------+
 * [gives a score for the player hand based on how many faces 
 *  are repeated on the hand of the player]
 * @param  player [payer to give score]
 * @return        [score for the player hand]
 *
 * search for consecutive faces in hand 
 *     assign base values to hands depending on how many repeated cards found
 *     add to base value the value per high card.
 *
 *      base values of hands are always higher than the previous highest hand 
 *
 *      sample:
 *       
 *     if high card
 *      [A, 2, 5 ,7 ,8 ] 
 *      13 * 13^4 + 8 * 13^3 + 7 * 13^2 + 5 * 13 + 2
 *
 *     if pair
 *      [A, 2, 2, 7 ,8 ] 
 *      2 * 13^4 + 13 * 13^3 + 8 * 13^2 + 7 * 13 + base pair value
 *      
 *     if two pair
 *      [A, 2, 2, 4, 4 ] 
 *      4 * 13^4 + 2 * 13^3 + 13 * 13^2 + base two pair value
 *      .
 *      . all hands between two pair and four of a kind are 
 *      . calculated the same way
 *      .
 *     if four of a kind
 *      [A, 2, 2, 2 ,2 ] 
 *      2 * 13^4 + 13 * 13^3 + base four of a kind value 
 *
 * 
 * 
 */
long ScoreFaceRepeated(Player *player)
{
    /* Variable Declaration*/
    int index2, current, next, equalFaceCount; 
    int highPair = 0; 
    int lowPair = 0;        
    int pair = 0;
    int trio = 0;
    int four = 0;
    long rank = 0;        
    int length = player->cardsAmt - OFFSET;
    int highest = (player->cards[0].face == FACE_A)? 
                    HIGH_A : player->cards[player->cardsAmt - OFFSET].face;
    int index = 0;

    while (four < 1 && index < length){

        current = player->cards[index].face;
        index2 = index + 1;
        equalFaceCount = 0;            
        next = player->cards[index2].face;

        while (index2 <= length && current == next){
            equalFaceCount++;
            index2++;
            next = player->cards[index2].face;
        }


        if (equalFaceCount == FOUR_COUNT){

            four++;
            
            highest = (current == FACE_A)? HIGH_A : current;

        }else if (equalFaceCount == TRIO_COUNT){

            trio++;

            highest = (current == FACE_A)? HIGH_A : current;
            index = index2;
            
        }else if (equalFaceCount == PAIR_COUNT){

            pair++;
            index = index2;

            highPair = (current == FACE_A)? HIGH_A : 
            (highPair > 0)? highPair : current;                

            if (pair > 1){

                lowPair = (current > highPair)? highPair : current;
                if (highPair == lowPair){
                    highPair = current;
                }

                highest = (highest > highPair)? highest :(
                    player->cards[2].face != highPair 
                    && player->cards[2].face != lowPair
                    )? player->cards[2].face : player->cards[0].face;                    
            }else{

                int tempIndex, tempFace;

                for (tempIndex = 0; tempIndex < length; tempIndex++){

                    tempFace = player->cards[tempIndex].face;
                    tempFace = (tempFace == FACE_A)? HIGH_A : tempFace;
                    highest += (highPair != tempFace)? tempFace : 0;
                }
            }            
        }else{            
            index++;
        }
        
    }

    if (four > 0){            
        rank = FOUR_KIND + highest;
        player->hand = "Four of a Kind";
        return rank;
    }else if (trio > 0){
        player->hand = (pair > 0)? "Full House" : "Three of a Kind";
        rank = (pair > 0)? FULLHOUSE + highest : THREE_KIND + highest;
        return rank;
    }else if (pair > 0){
        if (pair > 1){
            player->hand = "Two Pair";
            rank =  TWO_PAIR + highPair * HIGH_1 + lowPair * HIGH_2 + highest;
        }else {
            
            player->hand = "Pair";
            rank = PAIR + highPair * HIGH_1;
            int exponent = length - OFFSET;
            if (highest == HIGH_A){

                rank += highest * pow(HIGH_A, exponent);
                exponent--;

                for (index = length; index > 0; index--){

                    current = player->cards[index].face;

                    if (current != highPair){
                        rank += current * pow(HIGH_A, exponent);
                        exponent--;
                    }else{
                        rank += 0;
                    }
                }
            }else{

                for (index = length; index >= 0; index--)
                {
                    current = player->cards[index].face;

                    if (current != highPair){
                        rank += current * pow(HIGH_A, exponent);
                        exponent--;
                    }else{
                        rank += 0;
                    }
                }
            }

        }        
        return rank;
    }else{

        player->hand = "High Card";

        int exponent = length;
        if (highest == HIGH_A){

            rank += highest * pow(HIGH_A, exponent);
            exponent--;

            for (index = length; index > 0; index--){

                current = player->cards[index].face;
                rank += current * pow(HIGH_A, exponent);
                exponent--;
            }
        }else{

            for (index = length; index >= 0; index--){
                current = player->cards[index].face;            
                rank += current * pow(HIGH_A, exponent);
                exponent--;    
            }        
        }
        return rank;
    }
}



















/*-----------------------------------------------------------------------------+
 * [organizePlayers sorts the cards for all players
 * @param players     players to sort the cards for 
 * @param gamePlayers amount of players to sort cards for
 */
void organizePlayers( Player players[], int gamePlayers ){


    int index;

    for ( index = 0; index < gamePlayers; ++index )
    {
        sortCards( &players[index] );
    }
}









/*-----------------------------------------------------------------------------+
 * Gives a player a rank value depending on player cards
 * @param player [player to be ranked]
 */
void rankPlayer(Player *player){

    player->rank = ScoreFaceRepeated(player);
    player->rank += ScoreflushOrStraight(player); 
    
}













/*-----------------------------------------------------------------------------+
 * sortCards sorts cards for a player
 * @param player player to sort the cards for
 */
void sortCards( Player *player ){
    int index, index2;

    Card key;

    for ( index = 1; index < player->cardsAmt; index++ )
    {
        key = player->cards[index];
        index2 = index - OFFSET;


        while ( index2 >= 0 && player->cards[index2].face > key.face )
        {
            player->cards[index2 + OFFSET] = player->cards[index2];
            index2 = index2 - OFFSET;
        }
        player->cards[index2 + OFFSET] = key;
    }
}



