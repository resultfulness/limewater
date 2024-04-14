#include <stdio.h>

#include "parser_err.h"

void print_parse_maze_err(enum PARSE_STATUS s,
                          char* scriptname) {
    switch (s) {
        case PARSE_INPUT_READ_ERROR:
            fprintf(stderr,
                    "%s: wystąpił błąd podczas odczytywania pliku wejściowego\n",
                    scriptname);
            break;
        case PARSE_INPUT_INVALID:
            fprintf(stderr,
                    "%s: plik wejściowy jest w błędnym formacie\n",
                    scriptname);
            break;
        case PARSE_OUTPUT_WRITE_ERROR:
            fprintf(stderr,
                    "%s: wystąpił błąd podczas zapisywania do pliku tymczasowego\n",
                    scriptname);
            break;
        case PARSE_OK:
            break;
    }
}
