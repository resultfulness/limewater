#include "help.h"
#include <stdio.h>

void print_help(char* scriptname) {
    printf("Użycie: %s PLIK_LABIRYNTU [OPCJE]\n", scriptname);

    fputs("\
Program rozwiązuje labirynt w PLIK_LABIRYNTU.\n\
Możliwe OPCJE:\n\
  -b    interpretuj PLIK_LABIRYNTU jako plik binarny\n\
", stdout);
}
