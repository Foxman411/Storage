#ifndef TASK_H
#define TASKS_H

#define BUFFER 10
#define FLASK_SIZE 3
#define RESET "\033[0m"
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

typedef struct {
    int* data;
    int top;
}Flask;

int starter();
Flask* generator( int glasses );
void display( Flask* flasks, int glasses );
void destroy( Flask* flasks, int glasses );
void runner( Flask* flasks, int glasses, int* game );

#endif