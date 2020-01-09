#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "deck.h"

void *sortCards_noSort( Card cards[], int nCards, int nRanks );
void *sortCards_bySuit( Card cards[], int nCards, int nRanks );
void *sortCards_byRank( Card cards[], int nCards, int nRanks );

void printHand( Hand *pHand );
void printGame( Game *pGame );

void (*pfuncSort[])( Card cards[], int nCards, int nRanks ) = { &sortCards_noSort, &sortCards_bySuit, &sortCards_byRank };

/**
 * Creates a deck, which is a series of shorts, 0..51 or 0..27, terminated by a special character
 */
Card *_createDeck( Game *pGame, int nCards )
{
    short i = 0;

    Card *deck = malloc( nCards * sizeof( Card ) );

    for ( i = 0; i < nCards; i++ )
        deck[i] = i;

    return deck;
}

void _swapCards( Card cards[], int i, int j )
{
    short iTemp = cards[j];
    cards[j] = cards[i];
    cards[i] = iTemp;
}

void *shuffleCards( Card cards[], int nCards )
{
    int i = 0;
    for ( i = 0; i < nCards; i++ )
	_swapCards( cards, i, rand() % nCards );
}

void *sortCards_byRank( Card cards[], int nCards, int nRanks )
{
    int i = 0;
    int j = 0;

    for ( i = 0; i < nCards-1; i++ )
    {
	for ( j = 0; j < nCards-i-1; j++ )
	{
	    int rankA = cards[j] % nRanks;
	    int rankB = cards[j+1] % nRanks;
	    if ( rankA > rankB || rankA == rankB && cards[j]/nRanks > cards[j+1]/nRanks )
	        _swapCards( cards, j, j+1 );
	}
    }
}

void *sortCards_bySuit( Card cards[], int nCards, int nRanks )
{
    int i = 0;
    int j = 0;

    for ( i = 0; i < nCards-1; i++ )
	for ( j = 0; j < nCards-i-1; j++ )
	    if ( cards[j] > cards[j+1] )
	        _swapCards( cards, j, j+1 );
}

void *sortCards_noSort( Card cards[], int nCards, int nRanks )
{
     ; /* leave them unsorted */
}

/**
 * Hands are implemented as an array of pointers to the array of cards
 */
void *initializeGame( Game *pGame, int nRanks, int nHands )
{
    int iHand = 0;

    pGame->nRanks = nRanks;
    pGame->deck.nCards = nRanks * NUM_SUITS;	

    /* create the deck, and shuffle it */
    pGame->deck.cards = _createDeck( pGame->deck.cards, pGame->deck.nCards );
    shuffleCards( pGame->deck.cards, pGame->deck.nCards );

    /* allocate the space we'll need for the specified number of hands */
    pGame->nHands = nHands;
    pGame->hands = (Hand *) malloc( nHands * sizeof( Hand ) );		

    /* initialize each of the hands */
    for ( iHand = 0; iHand < nHands; iHand++ )
    {
	pGame->hands[iHand].cards = NULL;	
	pGame->hands[iHand].nCards = 0;
    }

    /* printGame( pGame ); */
}


/**
 * Transfer ONE card from the deck, to the specified hand.  Both arrays are modified in the process.
 */
void dealCard( Game *pGame, int iHand )
{
    Hand *pHand = &(pGame->hands[iHand]);		/* get a reference to the hand of interest */
    pHand->nCards++;				/* record that we now have one more card in the deck */
    pHand->cards = realloc( pHand->cards, pHand->nCards * sizeof( Card ) );	/* resize the hard, so we have room for the new card */

    /* for simplicity, we're actually drawing off the END of the deck... so basically, we're treating our deck as a reversed array */
    pHand->cards[pHand->nCards-1] = pGame->deck.cards[pGame->deck.nCards-1];	/* stuff a card from the deck, into the new space we made in the array */

    pGame->deck.nCards--;			/* shrink the size of the cards in the deck */
    pGame->deck.cards = realloc( pGame->deck.cards, pGame->deck.nCards * sizeof( Card ) );	/* resize the deck */
}

void printCard( Card iCard, char *ranks[], int nRanks )
{
    if ( iCard < 0 || iCard > nRanks * NUM_SUITS )
         printf( "Error: invalid card %d", iCard );
     else
         printf( "%2s%s", ranks[iCard%nRanks], SUITS[iCard/nRanks] );
}

/**
 * This could be either a hand, or the deck, but either way it must be terminated
 *
 * There's a flag that says whether we print from 0..N-1, or N-1..0
 *
 * We're actually drawing off the BOTTOM of the deck, so we'
 */
void printCards( short cards[], int nCards, char* ranks[], int nRanks, int modeReversed )
{
    int i = 0;
    for ( i = 0; i < nCards; i++ )
    {
        if ( i > 0 )
	    printf( " " );

	printCard( cards[ modeReversed == PRINT_REVERSE ? (nCards-i-1) : i ], ranks, nRanks );
    }
    printf ( "\n" );
}

/**
 * Debug routine to print out the hand in an approximate JSON object 
 */
void printHand( Hand *pHand )
{
    printf( "{ addr: 0x%08lx, ", pHand );
    printf( "nCards: %d, cards: 0x%08lx ", pHand->nCards, pHand->cards );
    printf( "}" );
};

/**
 * Debug routine to print out the game in an approximate JSON object 
 */
void printGame( Game *pGame )
{
    int iHand = 0;
    printf( "{ addr: 0x%08lx, ", pGame );
    printf( "nRanks: %d, nHands: %d, hands: [", pGame->nRanks, pGame->nHands );
    for ( iHand = 0; iHand < pGame->nHands; iHand++ )
    {
	if ( iHand > 0 )
	    printf( ", " );
        printHand( &(pGame->hands[iHand]) );
    }
    printf( "], deck: " );
    printHand( &(pGame->deck) );
    printf( "}\n" );
}

