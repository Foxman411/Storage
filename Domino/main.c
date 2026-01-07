#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int left;
    int right;
} Domino;

Domino* read( void );
void clear( Domino* dominos );
int putable( Domino domino1, Domino domino2 );
void line( char memory[], int size, char o1, char o2 );

int main(){
    
    Domino* dominos = read();
    Domino down = dominos[0];
    dominos[0].left = 0;
    dominos[0].right = 0;
    char memory[ sizeof( dominos ) * 4 + 2 ];
    memset( memory, '0', sizeof( dominos ) * 4 + 2 );
    char digit[2];
    sprintf( digit, "%d", down.left );
    char o1 = digit[0];
    memory[ sizeof( dominos ) * 2 ] = digit[0];
    sprintf( digit, "%d", down.right );
    char o2 = digit[0];
    memory[ sizeof( dominos ) * 2 + 1 ] = digit[0];
    printf("\nInitial domino: %d | %d\t(%d dominos we have)\n", down.left, down.right, sizeof( dominos ) );
    int db = 0;
    int right = 0;
    int left = 0;
    unsigned int j;

    for( unsigned int i = 0; i < sizeof( dominos ); i++ ){                              // domino elhelyezese

        j = 0;
        while( j < sizeof( dominos ) && ( putable( down, dominos[j]) - 1 ) ) j++;       // jo domino megkeresese

        if( down.right == dominos[j].left ) {                                           // siman jobbra teszed

            printf("Added to the right end: %d | %d\n", dominos[j].left, dominos[j].right);
            down.right = dominos[j].right;
            db++;
            right++;
            sprintf( digit, "%d", dominos[j].left );
            memory[ sizeof( dominos ) * 2 + ( right * 2 ) ] = digit[0];
            sprintf( digit, "%d", dominos[j].right );
            memory[ sizeof( dominos ) * 2 + ( right * 2 ) + 1 ] = digit[0];
            dominos[j].left = 0;
            dominos[j].right = 0;

        } else if( down.right == dominos[j].right ) {                                   // forditva teszed jobbra

            printf("Added to the right end: %d | %d\n", dominos[j].left, dominos[j].right);
            down.right = dominos[j].left;
            db++;
            right++;
            sprintf( digit, "%d", dominos[j].right );
            memory[ sizeof( dominos ) * 2 + ( right * 2 ) ] = digit[0];
            sprintf( digit, "%d", dominos[j].left );
            memory[ sizeof( dominos ) * 2 + ( right * 2 ) + 1 ] = digit[0];
            dominos[j].left = 0;
            dominos[j].right = 0;

        } else if( down.left == dominos[j].right ) {                                    // siman balra teszed

            printf("Added to the left end: %d | %d\n", dominos[j].left, dominos[j].right);
            down.left = dominos[j].left;
            db++;
            left++;
            sprintf( digit, "%d", dominos[j].left );
            memory[ sizeof( dominos ) * 2 - ( left * 2 ) ] = digit[0];
            sprintf( digit, "%d", dominos[j].right );
            memory[ sizeof( dominos ) * 2 - ( left * 2 ) + 1 ] = digit[0];
            dominos[j].left = 0;
            dominos[j].right = 0;

        } else if( down.left == dominos[j].left ) {                                     // forditva teszed balra

            printf("Added to the left end: %d | %d\n", dominos[j].left, dominos[j].right);
            down.left = dominos[j].right;
            db++;
            left++;
            sprintf( digit, "%d", down.right );
            memory[ sizeof( dominos ) * 2 + 1 - ( left * 2) + 1 ] = digit[0];
            sprintf( digit, "%d", down.left );
            memory[ sizeof( dominos ) * 2 + 1 - ( left * 2 ) ] = digit[0];
            dominos[j].left = 0;
            dominos[j].right = 0;
        }

    }
    printf("\nSummary: %d domino were placed.\n", db );
    line( memory, sizeof( dominos ) * 4 + 2, o1, o2 );

    clear( dominos );
    return 0;
}

Domino* read( void ){
    
    FILE* file = fopen( "Dominos.txt", "r" );
    Domino* to_return;


    int left, right, db, i;
    fscanf( file , "%d %d\n%d\n", &left, &right, &db );

    to_return = (Domino*) malloc( sizeof( Domino ) * (db + 1) );
    if( to_return == NULL ){ printf("MALLOC ERROR!\n"); exit(1); }
    to_return[0].left = left;
    to_return[0].right = right;

    for( i = 1; i <= db; i++ ){
        fscanf( file, "%d", &left );
        to_return[i].left = left;
        fscanf( file, "%d", &right );
        to_return[i].right = right;
    }

    fclose( file );
    return to_return;
}

void clear( Domino* to_clear ){

    free( to_clear );

}

int putable( Domino domino1, Domino domino2 ){
    
    int to_return = 0;

    if( domino1.right == domino2.right ){
        to_return = 1;
    } else if( domino1.right == domino2.left ){
        domino1.right = domino2.right;
        to_return = 1;
    } else if( domino1.left == domino2.right ){
        domino1.right = domino2.left;
        to_return = 1;
    } else if( domino1.left == domino2.left ){
        domino1.right = domino2.right;
        to_return = 1;
    }

    return to_return;
}

void line( char memory[], int size, char o1, char o2 ){
    for( int i = 0; i < size; i += 2 ){
        if( memory[i] != '0' ) {
            if( memory[i] == o1 && memory[i + 1] == o2 ) {
                printf("\33[0;34m|%c %c| \033[0m", memory[i], memory[i + 1] );
            }
            else printf("|%c %c| ", memory[i], memory[i + 1] );
        }
    }
}