#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#define ctrl(x) ((x) & 0x1f)
// TODO: Make backspace compatible with other machines
#define BACKSPACE   127 
#define ESCAPE      27
#define SPACE       32 
#define ENTER       10
#define KEY_TAB     9
#define DOWN_ARROW  258 
#define UP_ARROW    259 
#define LEFT_ARROW  260 
#define RIGHT_ARROW 261 

typedef struct {
    size_t index;
    size_t size;
    char *contents;
} Row;

typedef struct {
    char *buf;
    Row rows;
    size_t row_index;
    size_t row_s;
    size_t cur_pos;
} Buffer;

void backspace(){
    int y, x;
    getyx(stdscr, y, x);
    move(y, x-1);
    delch();
    refresh();
    if((x == 0) & (y != 0)) {
        move(y-1, x);
        int my, mx;
        getyx(stdscr, y, x);
        getmaxyx(stdscr, my, mx);
        move(y, mx-1);
        while(inch() == ' ') { 
            getyx(stdscr, y, x);
            if(x == 0) {
                break;
            } else {
                move(y, --mx);
            }
        }
        getyx(stdscr, y, x);
        if(x != 0) {
            move(y, x+1);
            refresh();
        }  
    }
}

int main() {
    Buffer buffer = {0};
    buffer.row_s = 1;
    for(size_t i = 0; i < 1024; i++) {
        buffer.rows[i].contents = calloc(1024, sizeof(char));
    }


    initscr();			
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int ch = 0;
    while(ch != ctrl('q')){
        int my, mx;
        getmaxyx(stdscr, my, mx);
        ch = getch();
        int y, x;
        switch(ch) {
            case BACKSPACE:
                backspace();
                break;
            case UP_ARROW:
                getyx(stdscr, y, x);
                if(y != 0)move(y-1, x);
                break;
            case DOWN_ARROW:
                getyx(stdscr, y, x);
                if(y != my)move(y+1, x);
                break;
            case LEFT_ARROW:
                getyx(stdscr, y, x);
                if(x != 0)move(y, x-1);
                break;
            case RIGHT_ARROW:
                getyx(stdscr, y, x);
                if(x != mx)move(y, x+1);
                break;
            default:
                addch(ch);
                break;
                refresh();
        }
    }   
    FILE *file = fopen("out.txt", "w");
    fwrite(buffer.buf, 1024 , 1, file);
    fclose(file);
    refresh();
    endwin();			
    return 0;;
}

