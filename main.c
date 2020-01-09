#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "deck.h"
#include "parse.h"

const char *SUITS[] = { "C", "D", "H", "S" };
const char *RANKS[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
const char *EUCHRE_RANKS[] = { "9", "10", "J", "Q", "K", "A" };

int main( int argc, char *argv[] )
{

    Game game;		/* our new game */

    int iCard = 0;
    int iHand = 0;

    int nCardsPerHand = 0;
    int nHands = 0;
    int isEuchre = 0;
    int modeSort = SORT_BYRANK;
    int modePrint = PRINT_REVERSE;
    long nSeed = time( NULL );

    /* parse the command line arguments */
    if ( ! parseArguments( argc, argv, &nCardsPerHand, &nHands, &isEuchre, &modeSort, &modePrint, &nSeed ) )
        exit( EXIT_FAILURE );

    srand( nSeed );	/* seed the random number sequence */

    int nRanks = (isEuchre ? sizeof( EUCHRE_RANKS ) : sizeof( RANKS ) ) / sizeof( RANKS[0] );
    char **ranks;
    ranks = isEuchre ? EUCHRE_RANKS : RANKS; 

    /* set up everything for the game */
    initializeGame( &game, nRanks, nHands );
    /* deal out the cards to the players */
    for ( iCard = 0; iCard < nCardsPerHand; iCard++ )
	for ( iHand = 0; iHand < game.nHands; iHand++ )
	    dealCard( &game, iHand );

    /* print out the hands */
    for ( iHand = 0; iHand < game.nHands; iHand++ )
    {
	(*pfuncSort[modeSort])( game.hands[iHand].cards, game.hands[iHand].nCards, nRanks );

        printf( "Player %d: ", iHand+1 );
	printCards( game.hands[iHand].cards, game.hands[iHand].nCards, ranks, nRanks, modePrint );
    }

    /* print out the hands */
    printf( "Deck:     " );
    printCards( game.deck.cards, game.deck.nCards, ranks, nRanks, PRINT_REVERSE );

    /* clean up */
    for ( iHand = 0; iHand < game.nHands; iHand++ )
    {
        free( game.hands[iHand].cards );
	game.hands[iHand].nCards = 0;
    }

    free( game.deck.cards );
    game.deck.nCards = 0;

    exit( EXIT_SUCCESS );
}
