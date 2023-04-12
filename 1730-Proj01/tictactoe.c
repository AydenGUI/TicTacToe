#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <curses.h>
#include <term.h>


char	** createboard(int size);
void 	printboard(char** Board, int size);
int 	isdraw(char** Board, int size);
char 	winningmove(char** Board, int i, int j, int size);
int getMove( char ** Board, int board_sz, char x, char y );
int play_tictactoe(int size, int compEnabled );

// Prints the board
void printboard( char** Board, int size )
{
    printf(" ");
    for (int i =0; i < size; i++) {
        printf("|%d", i );
    }
    printf("|\n");
    for(int i = 0; i < size; ++i)
    {
    	printf("%c|", 'a' + i);
    	for( int j = 0; j < size; ++j )
        {
      		printf("%c|", Board[i][j]);
    	}
    	printf("\n");
    }
}

// Creates 3x3 tic tac toe board
char** createboard(int size)
{
    char** B = calloc( size, sizeof(char*) );

    // space for board
    for(int i = 0; i < size; ++i)
    {
    	B[i] = calloc(size, sizeof(char));
    }

    for(int j=0; j < size; ++j)
    {
    	for(int k=0; k < size; ++k)
        {
      		B[j][k] = ' ';
    	}
    }
    return B;
}



int main(int argc, char *argv[])
{
    int opt;
    int size = 3;
    int comp_Enabled = 0, failed_Start = 0;
    srand(time(0));
    while ((opt = getopt(argc, argv, ":is:h")) != -1)
    {
        switch(opt)
        {
        case 'i':
            comp_Enabled = 1;
            break;
        case 's':
            size = atoi(optarg);
            break;
        case 'h':
            failed_Start = 1;
            printf("Usage: tictactoe [-s <board_size>] [-i] [-h]\n");
            break;
        case '?':
            failed_Start = 1;
            printf("invalid option --'%c'\n", optopt);
            break;
        }
    } // while
    if(!failed_Start)
        play_tictactoe(size, comp_Enabled);
    return 0;
} // main

int play_tictactoe(int size, int comp_Enabled ) {
    char** Board = createboard(size);
    char winner = '\0';
    char row;
    char col, nothing;
    char turn = 'X';
    int quit = 0, temp_Move, invali = 0;
// standard game loop

    while(!winner && !isdraw(Board, size) )
    {
        if (invali) {
            invali = 0;
            printf("invalid input, try again.\n");
        } // if
        printboard(Board, size);
            // Get Move
            if ( (turn != 'O' && comp_Enabled) || !comp_Enabled)
            {
                temp_Move  = getMove(Board, size, row, col);
                row = temp_Move/100 + 'a';
                col = temp_Move%100 + '0';
                // gets random possible move

                printf( "Player's %c turn (qq to quit)\n", turn );
                printf("\n*---> suggestion:   (%c%c)\n\n", row, col);
                printf( "(%c) Enter Move (row column) ", turn );
                printf("--------------------------->");
                fflush(stdout);
                scanf(" %c %c", &row, &col);
            } else
            {

                temp_Move  = getMove(Board, size, row, col);

                row = temp_Move/100 + 'a';
                col = temp_Move%100 + '0';
                printf("row %c: col %c\n", row, col);
                printf( "(%c) Computer Picks (%c%c) (Enter any key to continue)\t---->\n", turn, row, col);
                scanf(" %c", &nothing);
                fflush(stdout);
            } // computer pick
            if (row == 'q' && col == 'q') {
                quit = 1;
                break;
            } //quits game

            // Make move if square is free
            int rowind = row - 'a';
            int colind = col - '0';
            if (rowind >= size || colind >= size || rowind < 0 || colind < 0) {
                system("clear");
                invali = 1; //says invalid move performed in last iteration
            } else if (Board[rowind][colind] == ' ')
            {
                printf("Move is %c %c (%d, %d)\n", row, col, rowind, colind);
                Board[rowind][colind] = turn;

                if (turn == 'X')
                {
                    turn = 'O';
                }
                else
                {
                    turn = 'X';
                }

                winner = winningmove( Board, rowind, colind, size);
            }
            else
            {
                printf("Square is occupied; try again.\n");
            }
            if(!winner && !isdraw(Board, size) ) {
                system("clear");
            } // if continues
        }// gameLoop

        // Game over - print board & declare finish


        if (quit) {
            printf("Thanks for playing\n");
        } else {

            if (winner == 'X' || winner == 'O')
            {
                printf("Congratulations %c!\n", winner);
                printboard(Board, size);
            }
            else
            {
                printf("Game ends in a draw.\n");
            }
        }
        return 0;
    }

    int getMove( char ** Board, int board_sz, char x, char y ) {
        int rowint, colint;
        int rando;
        do {
            rando = rand() % board_sz;
            x = '0' + rando;
            rando  = rand() % board_sz;
            y = 'a' + rando;
            rowint = y - 'a';
            colint = x - '1';
        } while (Board[rowint][colint] != ' ');
        return rowint * 100 + colint; // index combined as int
    } // getMove


// Returns true if the game is a draw
    int isdraw(char** Board, int size) {
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if (Board[i][j] == ' ') {
                    // empty square, so game ain't over yet
                    return 0;
                }
            }
        }
        // no empty squares, so it's a draw
        return 1;
    }



// Returns 'X' if (i,j) was a winning move for X
// Returns 'Y' if (i,j) was a winning move for Y
// Returns ASCII value 0 otherwise
    char winningmove( char** Board, int i, int j, int size )
    {
        int win = 0;
        char use_Char = Board[i][j];
        //check row
        for (int k = 0; k < size; k++) {
            if (use_Char != Board[i][(k + 1)%size]) {
                k = size;
            } // if
            if (use_Char == Board[i][(k + 1)%size] && k + 1 == size) {
                win = 1;
            } // if
        } // for

        //check column
        for (int k = 0; k <size; k++) {
            if (use_Char != Board[(k + 1)%size][j]) {
                k = size;
            } // if
            if (use_Char == Board[i][(k+1)%size] && k + 1 == size)
                win = 1;
        } // for

        if (i == j) {
            //check forward diagonal
            for (int k = 0; k < size; k++) {
                if (use_Char != Board[k][k])
                    k = size;
                else if (use_Char == Board[k][k] && (k + 1) == size)  {
                    win = 1;
                }
            } // for
        } // if
        if (i + j + 1 == size) {
            //check backwards diagonal
            for (int k = 0; k < size; k++) {
                if (use_Char != Board[(size - k - 1)][k])
                    k = size;
                else if (use_Char == Board[(size - k - 1)][k] && (k + 1) ==size)
                    win = 1;
            } // for
        } // if

        if (win) {
            // win was found
            return use_Char;
        }  else {
            // got nothing
            return 0;
        }
    }
