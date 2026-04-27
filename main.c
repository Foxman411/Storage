#include <stdio.h>

#include "tasks.h"

int main(){
    int glasses = starter();
    Flask* flasks = generator(glasses);
    int game = 1;
    while (game){
        display( flasks, glasses );
        runner( flasks, glasses, &game );
    }
    destroy( flasks, glasses );
}