#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tasks.h"

int main( int argc, char** argv ){
    if( argc != 2 ){ printf("Nem adott meg ascii fajlt!\n"); }
    printf("Udvozli Ont a %s program!\n", argv[0]);
    FILE* file = fopen(argv[1], "r");
    // assert( file != NULL && "Nem adott meg allomanyt!\n" );
    Alphabet letters;
    letters = read_txt( file );
    printf("Gepeljen be valamit (ctr + Z-vel lehet kilepni, ha uj sorban vagy):\n");
    char* word = malloc( sizeof( char ) * BUFFER );
    while ( scanf("%s", word) != EOF ) {
        draw_str( word, letters );
    }
    fclose(file);
    free_all( letters );
    printf("Sikeresen lefutott a program!\n");

    return 0;
}