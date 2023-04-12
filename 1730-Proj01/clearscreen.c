#include <stdio.h>
#include <stdlib.h>

#include <curses.h> // tgetstr, tgeten - termcap library routines
#include <term.h>   // tgetstr, tgeten - termcap library routines

// --------------------------------------------------------------- 
// http://stackoverflow.com/questions/17271576/clear-screen-in-c-and-c-on-unix-based-system
// --------------------------------------------------------------- 
//
// Compile line on nike.cc
// gcc -g clearscreen.c -o clearscreen -ltermcap
// need to link to termcap library
// --------------------------------------------------------------- 

#define CLEAR_SCREEN() printf("\033[H\033[J")

void clearScreenTermcap()
{
        char buf[1024];
        char *str;

        tgetent( buf, getenv("TERM") );
        str = tgetstr( "cl", NULL );    // linux
        fputs( str, stdout );
}


void display_menu()
{
	printf(" Type 5, 55, 555 then enter to clear screen\n");
 	printf( "\t(termcap (5), escape sequence(55), system(555)\n" );
	printf(" Enter 0 then enter to quit \n" );
	printf(" Enter 9 then enter to display menu \n" );
	printf(" (0 to quit, 9 for menu) Enter a Number (1-10)---> ");
}



int main( int argc, char * argv[] )
{
        int file_stdin = 1;
        int number;

	(void) file_stdin; // unused for now.

	display_menu();
        while ( scanf( "%d", & number ) == 1 )
        {
                printf("We just read %d --> ", number);
                if( number==0 ) 
		{
                        printf(" good bye ... \n\n");
			break;
		}
                if( number==5 )
                {
                        clearScreenTermcap();
 			printf("--- (termcap (5), escape sequence(55), system(555)\n" );
                        printf("(termcap clear) currently\n");
                        printf("(termcap clear)         Enter (another number) [0 to quit] ---> ");
                }
		else if( number == 55 )
                {
                        CLEAR_SCREEN();
 			printf("--- (termcap (5), escape sequence(55), system(555)\n" );
                        printf("(escape sequence clear) currently\n");
                        printf("(escape sequence clear) Enter (another number) [0 to quit] ---> ");
                }
		else if( number == 555 )
                {
                        system("clear");
 			printf("--- (termcap (5), escape sequence(55), system(555)\n" );
                        printf("(system clear) currently\n");
                        printf("(system clear)         Enter (another number) [0 to quit] ---> ");
                } 
		else if ( number == 9 ) display_menu();
        } // end  while
} // end main

