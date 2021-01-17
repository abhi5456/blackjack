// Include Files
#include <stdio.h>
#include <blackjack>

// Defines
#define NUM_CARDS 52
#define MAX_CARDS 11
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_card
// Description  : print the card from the integer value
//
// Inputs       : card - the card to print
// Outputs      : 0 always

int print_card( int card ) {

    // CODE HERE
    char card_faces[] = "234567891JQKA";
    char *card_suits[] = { SPADE, CLUB, HEART, DIAMOND };
    int suit = card / 13, cardty = card % 13;
    if ( cardty == 8 ) {
        printf( "10%s", card_suits[suit] );
    } else {
        printf( "%c%s", card_faces[cardty], card_suits[suit] );
    }

    // Return zero
    return( 0 );
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int print_cards( int cards[], int num_cards )
{
    int count = 0;
    for (int i = 0; i < num_cards; i ++) //this loop iterates through the cards array and prints it out
    {
        print_card(cards[i]);
        printf(" ");
        count++;
        
        if (count == 13) //this is so that there are 13 cards per line
        {
            printf("\n");
            count = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : shuffle_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

void swap(int *var1, int *var2) //swap method to swap places of elements in array
{
    int temp = *var1;
    *var1 = *var2;
    *var2 = temp;
}
int shuffle_cards( int cards[], int num_cards) //shuffles the cards using the Fisher-Yates shuffle
{
    uint32_t k = UINT32_MAX; 
    for (int i = num_cards - 1; i > 0; i--) //for loop iterates through the cards
    {
        k = rand() % (i + 1); //generates the random number
        swap(&cards[i], &cards[k]); //swaps the cards
    }
    printf("\n");
}

 
////////////////////////////////////////////////////////////////////////////////
//
// Function     : hand_value
// Description  : return the value of the hand
//
// Inputs       : cards - the array of cards in the hand
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int hand_value( int cards[], int num_cards ) 
{
    int val = 0; //value of hand
    int ace = 0; //number of aces
    for (int i = 0; i < num_cards; i++) //this is a loop to check the value of the hand
    {
        int temp = cards[i] % 13;
        if (temp <= 8)
        {
            val += temp + 2;
        }
        else if (temp != 12)
        {
            val += 10;
        }
        else
        {
            ace++;
            val += 11;
        }
        
    }
    return (val > 21 && ace != 0? val - 10:val); //returns hand value
}
////////////////////////////////////////////////////////////////////////////////
//
// Function     : sort_cards
// Description  : sort a collection of cards
//
// Inputs       : hand - the cards to sort
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int sort_cards( int hand[], int num_cards ) //sorts card with buuble sort implementation
{
    for ( int i = 0; i < num_cards - 1; i++) //iterate though the shuffled deck
    {
        int s = 0;
        for (int j = 0; j < num_cards - 1 - i; j++) 
        {
            int a1 = hand[j] % 13, a2 = hand[j + 1] % 13;
            int b1 = hand[j] / 13, b2 = hand[j + 1] / 13;
            if(a1 > a2 || a1 == a2 && b1 > b2)
            {
                swap(&hand[j], &hand[j+1]); //swaps the cards
                s = 1;
            }
        }
        if (s == 0)
        {
            break;
        }
    }

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : dealer_play
// Description  : dealer decision to hit or stand (hit on anything less 
//                than 17)
//
// Inputs       : hand - cards dealer has
//                num_cards - the number of cards in player hand
// Outputs      : 0 = stand, 1 = hit

int dealer_play( int hand[], int num_cards ) 
{
    int val = hand_value(hand, num_cards); //checks the hand value
    return val <= 16; //returns if value is less than or equal to 16

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : player_play
// Description  : player decision to hit or stand
//
// Inputs       : hand - cards player has
//                num_cards - the number of cards in player hand
//                dealer_card - the dealers face up card
// Outputs      : 0 = stand, 1 = hit

int player_play( int hand[], int num_cards, int dealer_card ) 
{
    int temp = dealer_card % 13; //check dealer card
    if (temp <= 8)
    {
        dealer_card = temp;
    }
    else if (temp != 12)
    {
        dealer_card = 10;
    }
    else
    {
        dealer_card = 11;
    }

    int val = hand_value(hand, num_cards); //total hand value
    if (val > 21) //if over 21 then bust or following for under 21
    {
        return 0;
    }
    else if (val > dealer_card + 2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
    

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : play_hand
// Description  : play a hand of black jack
//
// Inputs       : deck - the whole deck of cards
//                num_cards - the number of cards in the deck
//                player_money - pointer to player amount of money
// Outputs      : 1 if player wins, 0 if dealer wins

int play_hand( int deck[], int num_cards, float *player_money ) 
{
    printf("----New Hand----\n\n");
    shuffle_cards(deck, num_cards);
    int playerCards[MAX_CARDS]; //players cards array created
    int playerCardsCount = 2; //number of cards player has
    playerCards[0] = deck[0]; //player card 1
    playerCards[1] = deck[1]; //player card 2

    int dealerCards[MAX_CARDS]; //dealer cards array created
    int dealerCardsCount = 2; //number of cards dealer has
    dealerCards[0] = deck[2]; //dealer card 1
    dealerCards[1] = deck[3]; //dealer card 2

    printf("Dealer Cards: "); //prints out dealers card
    print_cards(dealerCards, 1);
    printf(" XX\n\n");

    printf("Player Cards: "); //print out player cards
    print_cards(playerCards, playerCardsCount);
    printf("\n");

    if (hand_value(playerCards, 2) == 21) //checks if 21 with two cards for player
    {
        printf("Player has Blackjack!, wins $7.50\n");
        *player_money += 7.50;
        return 1;
    }

    while (player_play(playerCards, playerCardsCount, dealerCards[0])) //deals cards while player cards under 21
    {
        playerCards[playerCardsCount] = deck[playerCardsCount + dealerCardsCount];
        playerCardsCount++;
        printf("Player hit (%d): ", hand_value(playerCards, playerCardsCount));
        print_cards(playerCards, playerCardsCount);
        printf("\n");
    }

    if (hand_value(playerCards, playerCardsCount) > 21) //if the player's hand goes over 21
    {
        printf("Player BUSTS ... dealer wins!\n");
		*player_money -= 5.0;
		return 0;
    }
    else //player has a hand value under 21 and over 16
	{
		printf("Player stands (%d): ", hand_value(playerCards, playerCardsCount));
		print_cards(playerCards, playerCardsCount);
		printf("\n\n");
	}

    while(dealer_play(dealerCards, dealerCardsCount)) //dealer plays
	{
		dealerCards[dealerCardsCount] = deck[dealerCardsCount + playerCardsCount];
		dealerCardsCount++;
		printf("Dealer hit (%d): ", hand_value(dealerCards, dealerCardsCount));
		print_cards(dealerCards, dealerCardsCount);
		printf("\n");
	}

	if(hand_value(dealerCards, dealerCardsCount) > 21) //checks if dealer cards are over 21
	{
		printf("Dealer BUSTS ... player wins!\n");
		*player_money += 5.0;
		return 1;
	}
	else //prints dealer cards when under 21 and over 16
	{
		printf("Dealer stands (%d): ", hand_value(dealerCards, dealerCardsCount));
		print_cards(dealerCards, dealerCardsCount);
		printf("\n\n");		
	}

	if(hand_value(playerCards, playerCardsCount) > hand_value(dealerCards, dealerCardsCount)) //checks if player hand is higher 
	{
		printf("Player wins!!!\n");
		*player_money += 5.0;
		return 1;
	}
	else //since dealer hand is higher than player, dealer wins
	{
		printf("Dealer wins!!!\n");
		*player_money -= 5.0;
		return 0;
	}

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : show_player_money_histogram
// Description  : Display a histogram of the player funds by hands
//
// Inputs       : money_rounds - the list of player money by hand number
//                last_round - the hand number where the game stopped
// Outputs      : 0 always

int show_player_money_histogram( float money_rounds[], int last_round ) 
{
    float max = 0;
    int numRound = 100 - last_round;
    for (int i = 0; i < last_round; i++) //loop for number of rounds
    {
        if (max < money_rounds[i])
        {
            max = money_rounds[i];
        }
    }
    int yAxis= (((int)max) / 100 + 1) * 100; //creating y axis
    for (int i = 0; i < 45; i++)
    {
        printf(" ");
    }
    printf("Player Cash by Round\n     "); //title of graoh
    for (int i = 0; i < 100; i++)
    {
        printf("-");
    }
    printf("\n");
    
    for(yAxis; yAxis >= 0; yAxis -= 5)
    {
        printf("%3d |", yAxis);
        for (int i = 0; i < 100; i++) //to plot points on graph
        {
            if ((int)money_rounds[i] >= yAxis)
            {
                printf("X");
                
            }
            else if (yAxis == 0 && i > (100 - numRound))
            {
                printf("X");
            }
            else
            {
                printf(".");
            }
            
        }
        printf("|\n");
    }
    printf("     ");
    for (int i = 0; i < 100; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("     ");
    for (int i = 1; i<= 10; i++) //xaxis labels
    {
        printf("         %d", i);
    }
    printf("\n     ");
    for (int i = 1; i <= 100; i++)
    {
        printf("%d", i % 10);
    }
    printf("\n");
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMPSC311 assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main( int argc, char **argv ) {

    /* Local variables */
    int cmp311_deck[NUM_CARDS];  // This is the deck of cards

    /* Preamble information */
    printf( "CMPSC311 - Assignment #1 - Fall 2020\n\n" );
    srand(time(NULL)) ;

    /* Step #1 - create the deck of cards */
    for (int i = 0; i < NUM_CARDS; i++)
    {
        cmp311_deck[i] = i;
    }
    
    /* Step #2 - print the deck of cards */
    print_cards(cmp311_deck,NUM_CARDS);
    printf("\n");

    /* Step #4 - shuffle the deck */
    shuffle_cards(cmp311_deck,NUM_CARDS);

    /* Step #5 - print the shuffled deck of cards */
    print_cards(cmp311_deck, NUM_CARDS);
    printf("\n");

    /* Step #6 - sort the cards */
    sort_cards(cmp311_deck, NUM_CARDS);

    /* Step #7 - print the sorted deck of cards */
    print_cards(cmp311_deck, NUM_CARDS);
    printf("\n");

    /* Step #9 - deal the hands */
    float playerMoney = 100.0;
    int count = 0;
    int win = 0;
    float histrographArray[100];
    while (count < 100 && playerMoney >= 5.0)
    {
        histrographArray[count] = playerMoney;
        win += play_hand(cmp311_deck, NUM_CARDS, &playerMoney);
        count++;
        printf("\nAfter hand %d player has %.2f$ left\n", count, playerMoney);
    }
	printf("-------------\nBlackjack done - player won %d out of 100 hands (%.2f).\n\n", win, win/100.0 * 100.0);
    /* Step 10 show historgrapm */
    show_player_money_histogram(histrographArray, count);

    /* Exit the program successfully */
    return( 0 );
}
