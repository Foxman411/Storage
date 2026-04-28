#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tasks.h"

Tower* starter( int puck ){
    
    Tower* to_return = malloc( sizeof( Tower ) * TOWERS );
    if(!to_return){ printf("MALLOC ERROR!\n"); exit(1); }

    for( int i = 0; i < TOWERS; i++ ){
        to_return[i].data = malloc( sizeof( int ) * puck );
        if(!to_return[i].data){ printf("MALLOC ERROR!\n"); exit(1); }
    }

    for( int i = 0; i < TOWERS; i++ ){
        if( i == 0 ){
            for( int j = 0; j < puck; j++ ){
                to_return[i].data[j] = j + 1;
            }
            to_return[i].top = puck;
        } else {
            for( int j = 0; j < puck; j++ ){
                to_return[i].data[j] = 0;
            }
            to_return[i].top = 0;
        }
    }

    srand(time(NULL));
    for( int i = TOWERS - 1; i >= 0; i-- ){
        int j = rand() % ( i + 1 );
        int tmp = to_return[0].data[i];
        to_return[0].data[i] = to_return[0].data[j];
        to_return[0].data[j] = tmp;
    }

    return to_return;

}

void runner( int* game, Tower* towers, int puck ){
    
    int from, to;
    int run = 1;
    char buffer[BUFFER];
    while(run){

        printf("Tower number moving from (q=quit): ");
        fgets( buffer, sizeof(buffer), stdin );
        buffer[strcspn( buffer, "\n" )] = '\0';
        if( strcmp( buffer, "q" ) == 0 ){
            *game = 0;
            return;
        }
        sscanf( buffer, "%d", &from );
        if( from >= 1 && from <= TOWERS && towers[from - 1].top != 0 ) run = 0;
        else printf("Invalid input!\n");
    } run = 1;

    while(run){

        printf("Tower number moving to (q=quit): ");
        fgets( buffer, sizeof(buffer), stdin );
        buffer[strcspn( buffer, "\n" )] = '\0';
        if( strcmp( buffer, "q" ) == 0 ){
            *game = 0;
            return;
        }
        sscanf( buffer, "%d", &to );
        if( to >= 1 && to <= TOWERS && towers[to - 1].top != puck ) run = 0;
        else printf("Invalid input!\n");

    } run = 1;

    towers[to - 1].data[towers[to - 1].top] = towers[from - 1].data[towers[from - 1].top - 1];
    towers[to - 1].top++;
    towers[from - 1].data[towers[from - 1].top - 1] = 0;
    towers[from - 1].top--;

    int done = 0;
    int db = 0;
    for( int i = 0; i < TOWERS; i++ ){
        if( towers[i].top == 0 ) done++;
        else{
            for( int j = 1; j < puck; j++ ){
                if( towers[i].data[j - 1] > towers[i].data[j] ) db++;
            }
            if( db == 4 ) done++;
        }
    }

    if( done == 3 ) {
        printf("\033[33mYou won!\n\033[0m");
        *game = 0;
    }

}

void destroy( Tower* towers ){
    for( int i = 0; i < TOWERS; i++ ){
        free(towers[i].data);
    }
    free(towers);
}

void display( Tower* towers, int puck ){

    // printf("I.\tII.\tIII.\n--------------------\n");
    // for( int i = puck - 1; i >= 0; i-- ){
    //     printf(" ");
    //     for( int j = 0; j < TOWERS; j++ ){
    //         printf("%d\t", towers[j].data[i] );
    //     }
    //     printf("\n");
    // }

    printf("I. tower\tII. tower\tIII. tower\n");
    for( int i = puck - 1; i >= 0; i-- ){
        for( int j = 0; j < TOWERS; j++ ){
            for( int k = puck - 1; k >= 0; k-- ){
                if( towers[j].data[i] - k > 0 ) printf("=");
                else printf(" ");
            }
            printf("|");
            for( int k = 0; k < puck; k++ ){
                if( towers[j].data[i] - k > 0 ) printf("=");
                else printf(" ");
            }
            printf("\t");
        }
        printf("\n");
    }

}