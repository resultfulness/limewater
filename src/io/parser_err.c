#include <stdio.h>
#include "parser_err.h"

void print_parse_maze_err(enum PARSE_MAZE_STATUS s,
                          char* scriptname,
                          char* input_fn) {
    switch (s) {
        case INPUT_INVALID:
            fprintf(stderr,
                    "%s: plik '%s' jest w błędnym formacie\n",
                    scriptname,
                    input_fn);
            break;
        case INPUT_CANT_BE_OPENED:
            fprintf(stderr,
                    "%s: nie udało się otworzyć pliku '%s'\n",
                    scriptname,
                    input_fn);
            break;
        case INPUT_READ_ERROR:
            fprintf(stderr,
                    "%s: wystąpił błąd podczas odczytywania pliku '%s'\n",
                    scriptname,
                    input_fn);
            break;
        case OUTPUT_CANT_BE_OPENED:
            fprintf(stderr,
                    "%s: nie udało się otworzyć pliku tymczasowego\n",
                    scriptname);
            break;
        case OUTPUT_READ_ERROR: break;
            fprintf(stderr,
                    "%s: wystąpił błąd podczas odczytywania pliku tymczasowego\n",
                    scriptname);
        case OUTPUT_WRITE_ERROR:
            fprintf(stderr,
                    "%s: wystąpił błąd podczas zapisywania do pliku tymczasowego\n",
                    scriptname);
            break;
        case OK:
            break;
    }
}
