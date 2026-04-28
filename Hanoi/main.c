#include <stdio.h>
#include <stdlib.h>

#include "tasks.h"

int main( int argc, char* argv[] ){
    printf("Welcome in %s program!\n", argv[0]);
    int puck;
    char buffer[BUFFER];
    if( argc == 2 ) puck = atoi( argv[1] );
    else{
        fgets( buffer, sizeof(buffer), stdin );
        sscanf( buffer, "%d", &puck );
    }
    Tower* towers = starter( puck );
    int game = 1;
    while(game){
        display( towers, puck );
        runner( &game, towers, puck );
    }
    display( towers, puck );
    destroy(towers);
}