#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tasks.h"

Alphabet read_txt( FILE* input ){

    Alphabet to_return;
    fscanf( input, "%d", &to_return.height );
    fgetc(input);
    to_return.characters = malloc( sizeof( Character ) * 25 );

    for( int character_index = 0; character_index < 26; character_index++ ){
        to_return.characters[character_index] = (Character) malloc( sizeof( char* ) * to_return.height );
        if( to_return.characters[character_index] == NULL ){ printf("Malloc ERROR!\n");  exit(1); }
        
        for( int y_coordinate = 0; y_coordinate < to_return.height; y_coordinate++ ){
            to_return.characters[character_index][y_coordinate] = (char*) malloc( sizeof( char ) * BUFFER );
            if( to_return.characters[character_index][y_coordinate] == NULL){ printf("Malloc ERROR!\n");  exit(1); }

            fgets( to_return.characters[character_index][y_coordinate], BUFFER, input );
            // printf("%s", to_return.characters[character_index][y_coordinate]);
            to_return.characters[character_index][y_coordinate][strcspn(to_return.characters[character_index][y_coordinate], "\n")] = '\0';

        }
    }

    return to_return;
}

void draw_str( char* line, Alphabet alphabet ){
    int character, y_coordinate;
    unsigned int letter;
    for( y_coordinate = 0; y_coordinate < alphabet.height; y_coordinate++ ){
        for( letter = 0; letter < strlen(line); letter++ ){
            character = (int) line[letter] - 'a';
            printf("%s", alphabet.characters[character][y_coordinate]);
        }
        printf("\n");
    }
}

void free_all( Alphabet alphabet ){

    for( int letters; letters < 25; letters++ ){
        for( int y_coordinate = 0; y_coordinate < alphabet.height; y_coordinate++ ){
            free( alphabet.characters[letters][y_coordinate] );
        }
        free( alphabet.characters[letters] );
    }
    free( alphabet.characters );
}