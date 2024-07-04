#include <stdio.h>
#include <curses.h>

#define ctrl(x) ((x) & 0x1f)
#define BACKSPACE 127 // TODO: Make backspace compatible with other machines

int main() {

    initscr();			
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int ch = getch();
    while(ch != ctrl('q')){
        ch = getch();
        if(ch == BACKSPACE){
            int y, x;
            getyx(stdscr, y, x);
            move(y, x-1);
            delch();
            refresh();
            if(x == 0) {
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
                if(x == 0) {
                    continue;
                } else {
                move(y, x+1);
                refresh();
                }
            }
        } else {
            addch(ch);
        }
    }
    refresh();
    endwin();			
    return 0;;
}

