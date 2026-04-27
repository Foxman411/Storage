#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tasks.h"

int starter(){

    int to_return;
    char buffer[BUFFER];
    int condition = 1;
    while (condition){
        printf("Number of glasses (2-7): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &to_return);
        if( to_return > 1 && to_return < 8 ) condition = 0;
        else printf("Wrong number given!\n");
    }
    
    return to_return;
}

Flask* generator( int glasses ){

    Flask* to_return = malloc( sizeof( Flask ) * glasses );
    if(!to_return) { printf("MALLOC ERROR!\n"); exit(1); }
    for( int i = 0; i < glasses; i++ ){
        to_return[i].data = malloc( sizeof( int ) * FLASK_SIZE );
        if( !to_return[i].data ) { printf("MALLOC ERROR!\n"); exit(1); }
    }
    
    int total = ( glasses - 1 ) * FLASK_SIZE;
    int* pool = malloc( sizeof( int ) * total );
    if(!pool) { printf("MALLOC ERROR!\n"); exit(1); }
    int idx = 0;
    for( int c = 1; c <= glasses - 1; c++ ){
        for( int k = 0; k < FLASK_SIZE; k++ )
            pool[idx++] = c;
    }

    srand(time(NULL));
    for( int i = total - 1; i > 0; i-- ){
        int j = rand() % ( i + 1 );
        int tmp = pool[i];
        pool[i] = pool[j];
        pool[j] = tmp;
    }

    idx = 0;
    for( int i = 0; i < glasses; i++ ){
        if( i == glasses - 1 ){
            for( int j = 0; j < FLASK_SIZE; j++ )
                to_return[i].data[j] = 0;
            to_return[i].top = 0;
        } else{
            for( int j = 0; j < FLASK_SIZE; j++ )
                to_return[i].data[j] = pool[idx++];
            to_return[i].top = FLASK_SIZE;
        }
    }

    free(pool);
    return to_return;
}

void display( Flask* flasks, int glasses ){
    
    const char* colors[] = {
    " ", "\033[41m", "\033[42m", "\033[43m", "\033[44m", "\033[45m", "\033[46m", "\033[47m"
    };

    for( int level = FLASK_SIZE - 1; level >= 0; level-- ){
        for( int i = 0; i < glasses; i++ ){
            level < flasks[i].top ?
            printf("|%s %s| ", colors[flasks[i].data[level]], RESET):
            printf("| | ");
        }
        printf("\n");
    }

    for( int i = 0; i < glasses; i++ ){
        printf(" %d  ", i + 1);
    }
    printf("\n\n");
}

void destroy( Flask* flasks, int glasses ){
    
    for( int i = 0; i < glasses; i++ ){
        free( flasks[i].data );
    }
    free(flasks);
}

void runner( Flask* flasks, int glasses, int* game ){

        int act;
    int win = 0;
    for( int i = 0; i < glasses; i++ ){
        int db = 0;
        for( int j = 0; j < FLASK_SIZE; j++ ){
            if( j == 0 && flasks[i].data[0] != 0 ){
                act = flasks[i].data[j];
                db++;
            }    
            else if( flasks[i].data[j] == act && flasks[i].data[0] != 0 ){
                db++;
                if( db == FLASK_SIZE ) win++;
                if( win == glasses - 1 ){
                    *game = 0;
                    printf("\033[32mWin! Hohooo!\033[0m\n");
                    break;
                }
            }
        }
    }

    if( *game != 0 ){
        int from;
        int where;
        char buffer[BUFFER];
        int run = 1;
        while( run ){
            while (1){
        
                printf("From (1-%d, q=quit): ", glasses);
                fgets( buffer, sizeof(buffer), stdin );
                buffer[strcspn( buffer, "\n" )] = '\0';
                if( strcmp( buffer, "q" ) == 0 ){
                    *game = 0;
                    return;
                }
                
                if( sscanf( buffer, "%d", &from ) == 1 && from >= 1 && from <= glasses && flasks[from - 1].top > 0 ){
                    break;
                }
                printf("Invalid input!\n");
            }
            
            while (1) {
                printf("Where (1-%d, q=quit): ", glasses);
                fgets( buffer, sizeof(buffer), stdin );
                buffer[strcspn( buffer, "\n" )] = '\0';
                if( strcmp( buffer, "q" ) == 0 ){
                    *game = 0;
                    return; 
                }
                
                if( sscanf( buffer, "%d", &where ) == 1 && where >= 1 && where <= glasses && flasks[where - 1].top < FLASK_SIZE && ( flasks[where - 1].top == 0 ||
                flasks[where - 1].data[flasks[where - 1].top - 1] == flasks[from - 1].data[flasks[from - 1].top - 1] ) ){
                    break;
                }
                printf("Invalid input!\n");
            }
            if( ( flasks[where - 1].top == 0 || flasks[where - 1].data[flasks[where - 1].top - 1] == flasks[from - 1].data[flasks[from - 1].top - 1] ) ){
                run = 0;
            } else{
                printf("Invalid move!\n");
            }
        }
    
        flasks[where - 1].data[flasks[where - 1].top] = flasks[from - 1].data[flasks[from - 1].top - 1];
        flasks[where - 1].top++;
        flasks[from - 1].data[flasks[from - 1].top - 1] = 0;
        flasks[from - 1].top--;
    }

}