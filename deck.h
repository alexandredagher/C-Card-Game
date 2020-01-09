#define NUM_SUITS	4

#define PRINT_NORMAL 	0
#define PRINT_REVERSE 	1

#define SORT_NOSORT 	0
#define SORT_BYSUIT 	1
#define SORT_BYRANK 	2

extern void (*pfuncSort[])( Card cards[], int nCards, int nRanks );

extern void *initializeGame( Game *pGame, int nRanks, int nHands );

extern void *shuffleCards( Card cards[], int nCards );

extern void dealCard( Game *pGame, int iHand );

extern void printCard( short iCard, char *ranks[], int nRanks );
extern void printCards( short cards[], int nCards, char *ranks[], int nRanks, int modeReversed );
