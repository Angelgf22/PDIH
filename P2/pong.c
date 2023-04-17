#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 40000

typedef struct{int x, y, goals, size;} Paddle;

int main(int argc, char *argv[]) {
    int x = 0, y = 0;
    int next_x = 0, next_y = 0;
    int direction_x = 1, direction_y = 1;
    int screen_y, screen_x;
    int i;
    bool quit = false;
    Paddle right_paddle, left_paddle;

    initscr();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    clear();

    refresh();
    getmaxyx(stdscr, screen_y, screen_x);

    WINDOW *window = newwin(screen_y,screen_x,0,0);
    wbkgd(window, COLOR_PAIR(1));
    box(window, '|', '-');

    mvwprintw(window, 1, 1, "Hecho por: Angel Gomez Ferrer (Github: https://github.com/Angelgf22)");
    mvwprintw(window, 4, 4, "Controles:");
    mvwprintw(window, 5, 4, "Jugador izquierda:");
    mvwprintw(window, 6, 4, "\t- W : Subir");
    mvwprintw(window, 7, 4, "\t- S : Bajar");
    mvwprintw(window, 8, 4, "Jugador derecha:");
    mvwprintw(window, 9, 4, "\t- KEY_UP : Subir");
    mvwprintw(window, 10, 4, "\t- KEY_DOWN : Bajar");
    mvwprintw(window, 11, 4, "El primer jugador en llega a 10 goles gana!");
    mvwprintw(window, 12, 4, "Pulse una tecla para comenzar el juego, utiliza la tecla Q para cerrar.");
    mvwprintw(window, 13, 4, "Suerte!");
    wrefresh(window);

    getch();
    endwin();

    initscr();
    noecho();
    curs_set(false);
    nodelay(stdscr, true);
    keypad(stdscr, true);

    right_paddle.size = 7;
    right_paddle.x = screen_x - 2;
    right_paddle.y = screen_y/2 - right_paddle.size/2;
    right_paddle.goals = 0;

    left_paddle.size = 7;
    left_paddle.x = 2;
    left_paddle.y = screen_y/2 - left_paddle.size/2;
    left_paddle.goals = 0;

    while(!quit) {
        clear();
        mvprintw(y, x, "o");
        for(i = 0 ; i < screen_y; ++i) {
            mvprintw(i, screen_x/2, "|");
        }

        for(i = 0 ; i < right_paddle.size; ++i) {
            mvprintw(right_paddle.y + i, right_paddle.x, "|");
        }

        for(i = 0 ; i < left_paddle.size; ++i) {
            mvprintw(left_paddle.y + i, left_paddle.x , "|");
        }
        mvprintw(0, screen_x/4 , "%i", left_paddle.goals);
        mvprintw(0, screen_x- screen_x/4 , "%i", right_paddle.goals);

        switch(getch()){
            case 'w':
                if(left_paddle.y > 0)
                    left_paddle.y--;
                break;
            case 's':
                if(left_paddle.y+left_paddle.size < screen_y)
                    left_paddle.y++;
                break;
            case KEY_UP:
                if(right_paddle.y > 0)
                    right_paddle.y--;
                break;
            case KEY_DOWN:
                if(right_paddle.y+right_paddle.size < screen_y)
                    right_paddle.y++;
                break;
            case 'q':
                quit = true;
                break;
        }

        refresh();

        usleep(DELAY);

        next_x = x + direction_x;
        next_y = y + direction_y;

        //Colisionan (right)
        if(right_paddle.x == x){
            for (i = 0; i < right_paddle.size; ++i) {
                if((right_paddle.y + i) == y){
                    direction_x*= -1;
                    x+= direction_x;
                }
            }
        }

        //Colisionan (left)
        if(left_paddle.x == x){
            for (i = 0; i < left_paddle.size; ++i) {
                if((left_paddle.y + i) == y){
                    direction_x*= -1;
                    x+= direction_x;
                }
            }
        }

        if (next_x >= screen_x) {
            left_paddle.goals++;
            x = screen_x/4;
            y = screen_y/2;
            direction_y*= -1;
        }else if (next_x < 0) {
            right_paddle.goals++;
            x = screen_x - screen_x/4;
            y = screen_y/2;
            direction_y*= -1;

        }else {
            x+= direction_x;
        }

        if (next_y >= screen_y || next_y < 0) {
            direction_y*= -1;
        } else {
            y+= direction_y;
        }
        if(left_paddle.goals == 10) {
            quit = true;
        }
        if(right_paddle.goals == 10) {
            quit = true;
        }

    }

    endwin();
}
