/*
 * File: game_logic.c
 * Project: f:\Documents\C\Semester 2\Hedgehogs in a Hurry\
 * Created Date: Saturday March 9th 2019 4:44:25 pm
 * Author: ConorHK, thomasreilly1011 (based on template by lpasquale) 
 * -----
 * Description: File responsible for initialzing the game.
 */

#include "stack.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printLine();

token *top = NULL;
token *curr = NULL;

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */




char print_token(token *t)
{
    if ((*t).col == PINK)
        return 'P';
    if ((*t).col == RED)
        return 'R';
    if ((*t).col == BLU)
        return 'B';
    if ((*t).col == GREEN)
        return 'G';
    if ((*t).col == ORANGE)
        return 'O';
    if ((*t).col == YELLOW)
        return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS])
{
    printf("                THE BOARD\n");
    for (int i = 0; i < NUM_ROWS; i++)
    {

        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0';
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++)
        {
            if (board[i][j].stack != NULL)
            {
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else
            {
                //c is assigned 'X' if the square represents an obstacle
                if (board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else
                    c = ' ';
            }
            printf("| %c ", c);
        }
        printf("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine()
{
    printf("   -------------------------------------\n");
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
    //The minimum number of tokens placed on a square in the first column of the board.
    int minNumOfTokens = 0;
    int selectedSquare = 0;

    for(size_t i = 0; i < 4; i++){
        for(size_t j = 0; j < numPlayers; j++){
            step:
            printf("Player %d, please enter a square: ", j+1);
            scanf("%d", &selectedSquare);
            
            //Check to see if input is valid.
            if(selectedSquare < 0 || selectedSquare > 5){
                puts("Error: Invalid input.");
                goto step;
            }
            /*Verify whether the square selected by the 
            user has the minimum number of tokens and whether it does not 
            contain a token of the same color selected by the player */
             if((board[selectedSquare][0].numTokens == minNumOfTokens) && (board[selectedSquare][0].stack == NULL || board[selectedSquare][0].stack->col != players[j].col)){
                /*board[selectedSquare][0].stack = (token *) malloc(sizeof(token));
                board[selectedSquare][0].stack->col = players[j].col;
                board[selectedSquare][0].numTokens++;*/
                push(board, players[j], selectedSquare, 0);
                board[selectedSquare][0].numTokens++;
            }

            else{
                puts("Error: Invalid input.");
                printf("\nValid moves: ");
                for(size_t m = 0; m < 6; m++){
                    if((board[m][0].numTokens == minNumOfTokens) && (board[m][0].stack == NULL || board[m][0].stack->col != players[j].col)){
                        printf("%d ", m);
                    }
                }
                printf("\n");
                
                goto step;
            }
            

            //Updates the minimum number of tokens.
            if(((numPlayers * i) + j + 1) % NUM_ROWS == 0){
                minNumOfTokens++;
            }

            print_board(board);
        }
    }
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
    //Game status is true while the game is still running and false when the game is won or lost.
    bool win;
    int dieRoll;

    //Each loop represents a new round ingame.
    while(win == false)
    {
        //Each loop represents each players go.
        for(int i=0; i < numPlayers; i++)
        {
           dieRoll = rollDie();
          // moveVertical(board, players[i], dieRoll);
          // moveHorizontal(board, players[i], dieRoll);
          // win = winCheck(players[i]);
        }
        win = true;
    }
}

int rollDie(){
    srand(time(NULL));
    int dieRoll = rand()%6 + 1;
    printf("Die rolling");
    delay(1);
    printf(".");
    delay(1);
    printf(".");
    printf(" %d!\n", dieRoll);
    return dieRoll;
}

void moveVertical(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer, int dieRoll){
    /*int choice;

    reChoose:
    printf("Would you like to move one of your tokens up/down?\n");
    printf("\t1: Yes\n");
    printf("\t2: No\n");

    scanf("%d", &choice);
    switch(choice){
        case 1:
            int rowChoice, colChoice, moveChoice;
            printf("Please select a token: \n");
            printf("\tRow: ");
            scanf("%d", &rowChoice);
            printf("\tColumn: ");
            scanf("%d", &colChoice);

            if(board[rowChoice][colChoice].stack->col == currentPlayer.col){
                upOrDown:
                printf("\nWould you like to move the token up or down?\n");
                printf("\t1: Up\n");
                printf("\t: Down\n");
                scanf("%d", &moveChoice);

                switch(moveChoice){
                    case 1:

                            break;
                    case 2:
                            break;
                    default:
                            printf("\nERROR: Invalid input.\n");
                            delay(1);
                            goto upOrDown;
                            break;
                }
            }

            break;
        case 2:
            break;

        default:
            printf("ERROR: Invalid input.\n");
            delay(1);
            goto reChoose;
            break;
    }

*/
}

void moveHorizontal(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer, int dieRoll){

}

bool winCheck(player currentPlayer){

}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
} 