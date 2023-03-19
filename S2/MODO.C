#include <dos.h>
#define BYTE unsigned char

void video_mode(BYTE modo){
 union REGS inregs, outregs;
 inregs.h.ah = 0x00;
 inregs.h.al = modo;
 int86(0x10,&inregs,&outregs);
 return;
}

void pause(){
  union REGS inregs, outregs;
  inregs.h.ah = 8;
  int86(0x21, &inregs, &outregs);
}

char read_char(){
  union REGS inregs, outregs;
  char character;
  inregs.h.ah = 1;
  int86(0x21, &inregs, &outregs);
  character = outregs.h.al;

  return character;
}

void write_char(char c){
  union REGS inregs, outregs;

  inregs.h.ah = 2;
  inregs.h.dl = c;
  int86(0x21, &inregs, &outregs);
}


int main(){
  char aux;

  video_mode(3); // Texto 80x25 16Colores
  printf("\nPulsa una tecla: ");

  pause();

  video_mode(4); // Grafico 320x200 4Colores
  printf("\nPulsa una tecla para continuar con el ejercicio 2");
  pause();
  video_mode(3); // Volvemos a modo texto
  printf("\n Introducir un caracter: ");
  aux = read_char();
  printf("\n Caracter introducido: ");
  write_char(aux);

  return 0;
}
