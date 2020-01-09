extern const char *SUITS[];
extern const char *RANKS[];
extern const char *EUCHRE_RANKS[];

typedef short	Card;

typedef struct hand {
    Card	*cards;		/* our array of cards */
    int		nCards;		/* how many cards in this hand? */
} Hand;

typedef struct game {
    int		nRanks;		/* how many ranks in the deck we're using? */

    Hand 	deck;		/* we treat the undealt cards as a special "hand" */

    Hand 	*hands;		/* our array of hands */
    int		nHands;		/* how many hands in this game */
} Game;

