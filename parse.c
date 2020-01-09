/* PROGRAM:  Lab6

   AUTHOR:  Alex Dagher

   DATE:   December 6, 2017

   PURPOSE:  command line flags and arguments

   LEVEL OF DIFFICULTY: 4.3

   CHALLENGES: working with getopt

   HOURS SPENT: 10

 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <getopt.h>


int parseArguments( int argc, char *argv[], int *pnCardsPerHand, int *pnHands, int *pisEuchre, int *pmodeSort, int *pmodePrint, long *pnSeed ){

  int flag;
  int amountOfcards;

while ((flag = getopt (argc, argv, ":s:ep:c:t:m:h")) != -1){

    switch (flag)  {
      
    case 's': 
    if (atoi(optarg) == NULL){
    	flag++;
    }else{
    *pnSeed = atoi(optarg); 
	}
    break;

    case 'e':
    *pisEuchre = 1;
    break;

    case 'p': 
    *pnHands = atoi(optarg);
    break;

    case 'c':	 
    *pnCardsPerHand = atoi(optarg);
    break;

    case 't':
    if (atoi(optarg) == 0 || atoi(optarg) == 1 || atoi(optarg) == 2){

      	             if(atoi(optarg) == 0){
      		              *pmodeSort = 0;
      	                }
                     else if(atoi(optarg) == 1){
      		              *pmodeSort = 1;
      	                }
      	             else{
      		              *pmodeSort = 3;
      	                }
      	     
    }else{
    	printf("The Only Options for sorting methods is either 0, 1, 2", );
    	printUsageMessage();
    	return 0;
    }


    *pmodeSort = atoi(optarg);
    break;

    case 'm':
    *pmodePrint = atoi(optarg);
    break;


    case 'h':
    printUsageMessage();
    break;

    default:
    printf("Please only enter valid flags. (case sensitive!) \n");
    printUsageMessage();
    break;
  }
}


        if(*pisEuchre == 1){
           amountOfcards = *pnCardsPerHand * *pnHands;
              if(amountOfcards > 24){
         	       printf("The amount of cards you requested to support that amount of players and cards is to much");
         	   printUsageMessage();
         	   return 0;
         }
        }
        else {
             amountOfcards = *pnCardsPerHand * *pnHands;
         	    if(amountOfcards > 52){
         	        printf("The amount of cards you requested to support that amount of players and cards is to much");
         	   printUsageMessage();
         	   return 0;
            }
        }

       if (*pmodeSort != 0 && *pmodeSort != 1 && *pmodeSort != 2){ 
                printf("You must select 0, 1, or 2 for the sorting methods.\n");
                printUsageMessage();
                return 0;
        }

        if (*pnCardsPerHand == 0){ 
                printf("You must specify the amounts of cards per hand, this is a mandatory field. \n");
                printUsageMessage();
                return 0;
        }

        if (*pnHands == 0){ 
                printf("You must specify the amounts of hands, this is a mandatory field. \n");
                printUsageMessage();
                return 0;
        }

        if (*pisEuchre == 0){ 

                if (((*pnCardsPerHand) * (*pnHands)) > 52){ 
                        printf("You have chosen too many cards/players. (cards x players is over 52) \n");
                        printUsageMessage();
                        return 0;
                }
        }

   return 1;
}




void printUsageMessage(){

printf("   -s                         allows user to specify a specific seed for random function\n");
printf("   -e                         allows user to use a euchre deck instead of normal deck\n");
printf("   -p                         allows user to specify the amount of players\n");
printf("   -c                         allows user to specify the amount of cards per players\n");
printf("   -t                         allows user to specify the mode of sorting with arguments 0 for no sort 1 for by suit and 2 for by value\n");
printf("   -m                         allows user to select more of printing cards if they would like it backwards\n");

}

