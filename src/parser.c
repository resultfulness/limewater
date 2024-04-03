#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static int cell_handle_adj(char* cval, const char adj, enum DIRECTION d) {
    switch (adj) {
        case 'X':
            break;
        case ' ':
            *cval += d;
            break;
        case 'P':
            *cval += START_ENCODE_VALUE;
            break;
        case 'K':
            *cval += END_ENCODE_VALUE;
            break;
        default:
            return 1;
    }
    return 0;
}

static int cell_encode(char* cval,
                       const char n,
                       const char e,
                       const char s,
                       const char w) {
    /* _Bool won't go past 1 no matter what */
    _Bool ret = 0;
    ret += cell_handle_adj(cval, n, NORTH);
    ret += cell_handle_adj(cval, e, EAST);
    ret += cell_handle_adj(cval, s, SOUTH);
    ret += cell_handle_adj(cval, w, WEST);
    return ret;
}

enum PARSE_MAZE_RETURN_CODE parse_maze_meta(FILE* in, struct maze* m) {
    char b[BUFSIZE];
    if (fgets(b, BUFSIZE, in) == NULL)
        return INPUT_READ_ERROR;

    m->width = strlen(b) / 2 - 1;
    m->height = 0;
    while (1) {
        size_t llen = fread(b, 1, BUFSIZE, in);
        if (ferror(in)) 
            return INPUT_READ_ERROR;

        for (int i = 0; i < llen; i++) {
            if (b[i] == '\n')
                m->height++;
        }

        if (feof(in))
            break;
    }
    m->height /= 2;
    if (m->height <= 0 || m->width <= 0) 
        return INPUT_INVALID;

    rewind(in);
    return OK;
}

enum PARSE_MAZE_RETURN_CODE parse_maze_structure(FILE* in, FILE* tmp_file) {
    char b[BUFSIZE],
        bprev[BUFSIZE],
        bnext[BUFSIZE];

    int b_i = 0; // position of buffer b in file
    int b_j = 0; // position while iterating over b contents
    int maze_i = 0, // position in maze
    maze_j = 0;

    // load initial data into the buffers
    if (fgets(bnext, BUFSIZE, in) == NULL) 
        return INPUT_READ_ERROR;

    strcpy(bprev, bnext);
    if (fgets(bnext, BUFSIZE, in) == NULL)
        return INPUT_READ_ERROR;

    strcpy(b, bnext);
    b_i++;

    while (fgets(bnext, BUFSIZE, in) != NULL) {
        if (ferror(in)) 
            return INPUT_READ_ERROR;

        if (b_i % 2 == 1) {
            for (b_j = 0, maze_j = 0; b_j < strlen(b) - 1; b_j++) {
                if (b_j % 2 == 0)
                    continue;
                if (b[b_j] != ' ') 
                    return INPUT_INVALID;

                char cell = 0;
                const char adjN = bprev[b_j];
                const char adjE = b[b_j + 1];
                const char adjS = bnext[b_j];
                const char adjW = b[b_j - 1];
                if (cell_encode(&cell, adjN, adjE, adjS, adjW) != 0) 
                    return INPUT_INVALID;

                fputc(cell, tmp_file);
                if (ferror(tmp_file)) 
                    return OUTPUT_WRITE_ERROR;

                maze_j++;
            }

            maze_i++;
            maze_j = 0;
        }

        // move buffers forward
        strcpy(bprev, b);
        strcpy(b, bnext);
        b_i++;
    }

    return OK;
}

enum PARSE_MAZE_RETURN_CODE parse_maze(const char* filename,
                                       struct maze* m,
                                       FILE* tmpf) {
    enum PARSE_MAZE_RETURN_CODE ret = OK;

    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        ret = INPUT_CANT_BE_OPENED;
        goto out;
    }
    if (tmpf == NULL) {
        ret = OUTPUT_CANT_BE_OPENED;
        goto out_close_input;
    }

    char b[BUFSIZE];

    if (fgets(b, BUFSIZE, in) == NULL) {
        ret = INPUT_READ_ERROR;
        goto out_close_input;
    }

    _Bool is_in_binary = 0;
    if (b[4] == 27) { is_in_binary = 1; }

    rewind(in);

    if (!is_in_binary) {
        ret = parse_maze_meta(in, m);
        if (ret != OK)
            goto out_close_input;
    }

    if (!is_in_binary) {
        ret = parse_maze_structure(in, tmpf);
        if (ret != OK)
            goto out_close_input;
    }

out_close_input:
    fclose(in);
out:
    return ret;
}

int get_cell_data(FILE* data,
                  const int index,
                  char* cell_data) {
    if(data == NULL)
        return 1;
    if(fseek(data, index, SEEK_SET) != 0)
        return 1;

    *cell_data = fgetc(data);
    if (feof(data) || ferror(data))
        return 1;
    return 0;
}

int set_cell_parent(FILE* data,
                    const int index,
                    const enum PARENT_DIRECTION parent) {
    if(fseek(data, index, SEEK_SET) != 0)
        return 1;

    char cell_data = fgetc(data);
    if (feof(data) || ferror(data))
        return 1;
    cell_data += parent;

    if(fseek(data, index, SEEK_SET) != 0)
        return 1;
    fputc(cell_data, data);
    if(ferror(data))
        return 1;

    return 0;
}

void print_parse_maze_err(enum PARSE_MAZE_RETURN_CODE ret,
                          char* scriptname,
                          char* input_fn ) {
    switch (ret) {
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
