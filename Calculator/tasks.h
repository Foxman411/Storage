#include <stdio.h>

#ifndef TASKS_H
#define TASKS_H

typedef struct{
    int state;
    int input;
    int memory;
} Calculator;

typedef enum {
    LEFT,
    LEFT_PLUS,
    LEFT_TIMES,
    PLUS_RIGHT,
    TIMES_RIGHT
} STATE;

int digit( int n, Calculator* c ){
    c->input = 10 * c->input + n;
    
    if( c->state == LEFT_PLUS ){
        c->state = PLUS_RIGHT;
    } else if( c->state == LEFT_TIMES ){
        c->state = TIMES_RIGHT;
    }
    return c->input;
}

int plus( Calculator* c ){
    switch( c->state ){
        case LEFT: 
        c->memory = c->input;
        break;
        case PLUS_RIGHT:
        c->memory += c->input;
        break;
        case TIMES_RIGHT:
        c->memory *= c->input;
        break;
        default:
        break;
    }

    c->input = 0;
    c->state = LEFT_PLUS;
    return c->memory;
}

int times( Calculator* c ){
    switch( c->state ){
        case LEFT: 
        c->memory = c->input;
        break;
        case PLUS_RIGHT:
        c->memory += c->input;
        break;
        case TIMES_RIGHT:
        c->memory *= c->input;
        break;
        default:
        break;
    }

    c->input = 0;
    c->state = LEFT_TIMES;
    return c->memory;
}

void reset( Calculator* c ){
    c->memory = 0;
    c->input = 0;
    c->state = LEFT;
}

#endif