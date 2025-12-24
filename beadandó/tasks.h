#ifndef TASKS_H
#define TASKS_H

#define BUFFER 16

typedef char** Character;

typedef struct{
    int height;
    Character* characters;
} Alphabet;

Alphabet read_txt( FILE* input );
void draw_str ( char* line, Alphabet alphabet );
void free_all( Alphabet alphabet );

#endif