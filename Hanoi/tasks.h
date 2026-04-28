#ifndef TASKS_H
#define TASKS_H

#define BUFFER 20
#define TOWERS 3

typedef struct{
    int* data;
    int top;
} Tower;

void runner( int* game, Tower* towers, int puck );
Tower* starter( int puck );
void destroy( Tower* towers );
void display( Tower* towers, int puck );

#endif