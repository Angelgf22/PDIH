#include <ncurses.h>
int main(){
    initscr(); //inicializar modo curses
    printw("Holita"); //imprimir mensaje (aún no se verá)
    refresh(); //mostrarlo en pantalla
    getch(); //esperar la pulsación de una tecla
    endwin(); //terminar el modo curses
    return 0;
}
