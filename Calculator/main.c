#include <stdio.h>
#include <stdbool.h>

#include "tasks.h"

int main( int argc, char* argv[] ){

    Calculator c;
    c.input = 0;
    c.memory = 0;
    c.state = LEFT;

    if( argc > 1 ){
        char good[11] = "0123456789";
        bool go = false;
        for( int i = 1; i < argc; i++ ){

            for( unsigned int j = 0; j < sizeof( argv[i] ) - 1; j++ ){

                for( unsigned int jo = 0; jo < sizeof(good) - 1; jo++ ){
                    if( argv[i][j] == good[jo] ){
                        go = true;
                    }
                }

                if( go || argv[i][j] == '+' || argv[i][j] == '*' ){
    
                    if( argv[i][j] == '+' ){
                        plus( &c );
                        printf("+ ");
                        // printf("%d ", plus( &c ));
                    }
                    else if( argv[i][j] == '*' ){
                        times( &c );
                        printf("* ");
                        // printf("%d ", times( &c ));
                    }
                    else {
                        printf("%d ", digit( argv[i][j] - '0', &c ) );
                    }
                    if( j == sizeof( argv[i] ) - 2 && argv[i][j] != '+' && argv[i][j] != '*' ){
                        int index = j;
                        while( index > 0 && argv[i][index] != '+' && argv[i][index] != '*' ) index--;
                        if( index == 0 ) printf("= %s", argv[i] );
                        else {
                            switch( argv[i][index] - '*' ){
                                case 1:
                                printf("= %d", c.memory + c.input );
                                break;
                                case 0:
                                printf("= %d", c.memory * c.input );
                                break;
                            }
                        }
                    }
                    go = false;
                } else break;
            }
            reset( &c );
            printf("\n");

        }
    }

    reset( &c );
    return 0;
}