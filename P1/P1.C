#include <dos.h>
#define BYTE unsigned char

BYTE MODOTEXTO=3;
BYTE MODOVIDEO=4;

unsigned char bcolor = 0;
unsigned char tcolor = 1;


// EJ 1
void gotoxy(int x, int y) {
 union REGS inregs, outregs;
 inregs.h.ah = 2; // Indicamos que queremos cambiar la pos del cursor
 inregs.h.dh = y; // Fila
 inregs.h.dl = x; // Columna
 inregs.h.bh = 0x00; // (En la ventana actual)
 int86(0x10, &inregs, &outregs);
}
// AUX
void pause() {
 union REGS inregs, outregs;
 inregs.h.ah = 0x00;
 int86(0x16, &inregs, &outregs);
}
// EJ 2
void setcursortype(int cursor_type) {
  union REGS inregs, outregs;
  inregs.h.ah = 0x01;
  switch(cursor_type){
    case 0:                 //invisible
      inregs.h.ch = 010;
      inregs.h.cl = 000;
      break;
    case 1:                 //normal
      inregs.h.ch = 010;
      inregs.h.cl = 010;
      break;
    case 2:                 //grueso
      inregs.h.ch = 000;
      inregs.h.cl = 010;
      break;
  }
  int86(0x10, &inregs, &outregs);
}

// EJ 3
void setvideomode(BYTE mode) {
 union REGS inregs, outregs;
 inregs.h.ah = 0;
 inregs.h.al = mode;
 int86(0x10,&inregs,&outregs);
 return;
}

// EJ 4
int getvideomode() {

    int mode;
    union REGS inregs, outregs;
    inregs.h.ah = 15;
    int86(0x10, &inregs, &outregs);
    mode = outregs.h.al;
    return mode;
}

// EJ 5
void textcolor(unsigned char color) {
	tcolor = color;
}
// EJ 6
void textbackground(unsigned char color) {
	bcolor = color;
}

// EJ 7
void clrscr() {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


// EJ 8
void cputchar(char c) {
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = (bcolor << 4) | tcolor;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;

	int86(0x10, &inregs, &outregs);
}


// EJ 9
int getche() {
  union REGS inregs, outregs;
  int character;
  inregs.h.ah = 1;
  int86(0x21, &inregs, &outregs);
  character = outregs.h.al;

  return character;
}



void dibujarcuadrado(int xsi, int ysi, int xid, int yid, unsigned char text, unsigned char bg) {

 int i;

 clrscr();
 printf("\nEjercicio extra: Pintar cuadrado");

 textcolor(text);
 textbackground(bg);
  //Arriba
 for (i = xsi; i <= xid; ++i) {
   gotoxy(i, ysi);
   cputchar(' ');
 }
 //Abajo
 for (i = xsi; i <= xid; ++i) {
   gotoxy(i, yid);
   cputchar(' ');
 }
 //Izquierda
 for (i = ysi; i <= yid; ++i) {
   gotoxy(ysi, i);
   cputchar(' ');
 }
 //Derecha
 for (i = ysi; i <= yid; ++i) {
   gotoxy(yid, i);
   cputchar(' ');
 }


}



int main() {
  int aux;
  int video_mode;
  clrscr();
  printf("\nSe ha limpiado la pantalla.");
  //EJ 1 Gotoxy
  printf("\nEjercicio 1: Pulsa una tecla (GOTOXY 20,20): ");
  gotoxy(20,20);
  pause();

  printf("\n");
  // Ej 2 Cursor type
  printf("\nEjercicio 2: Pulsa una tecla (Cursor invisible): ");
  setcursortype(0);
  pause();
  printf("\nEjercicio 2: Pulsa una tecla (Cursor grueso): ");
  setcursortype(2);
  pause();
  printf("\nEjercicio 2: Pulsa una tecla (Cursor normal): ");
  setcursortype(1);
  pause();
  printf("\n");
  // EJ 3 y 4 set video mode y get video mode
  printf("\nEjercicio 3 y 4: Pulsa una tecla (setVideo): ");
  setvideomode(MODOVIDEO);
  video_mode = getvideomode();
  printf("\nEjercicio 3 y 4: Pulsa una tecla (MODO GRAFICO 4): %i", video_mode);
  pause();
  printf("\nEjercicio 3 y 4: Pulsa una tecla (MODO TEXTO 3): ");
  setvideomode(MODOTEXTO);
  video_mode = getvideomode();
  printf("\nEjercicio 3 y 4: (MODO TEXTO 3) video mode: %i", video_mode);
  pause();
  printf("\n");
   //Ejs: 5 6 8 y 9
  printf("\nEjercicios 5, 6, 8 y 9: Introduce una tecla: (GETCHE)");
  aux = getche();
  pause();
  printf("\nEjercicios 5, 6, 8 y 9: Pulsa una tecla: ( TEXTCOLOR 1 (azul oscuro) y background 3 (cian) )\n");
  pause();
  textcolor(1);
  textbackground(3);
  cputchar((char)aux);
  pause();
  printf("\n");
   //7 CLEAR
  printf("\nTEXTO");
  printf("\nEjercicios 7: Pulsa una tecla: (Limpiar Pantalla)\n");
  pause();

  pause();
  dibujarcuadrado(1,1,10,10,1,3);




  return 0;
}
