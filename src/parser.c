#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static void d_add(unsigned char* cval, const char d) {
    switch (d) {
        case 'N':
            *cval += 0b00001000;
            break;
        case 'E':
            *cval += 0b00000100;
            break;
        case 'W':
            *cval += 0b00000010;
            break;
        case 'S':
            *cval += 0b00000001;
            break;
    }
}

static int cell_encode(unsigned char* cval, const char d, const char dval) {
    if (!(d == 'N' || d == 'E' || d == 'S' || d == 'W'))
        return 2;
    switch (dval) {
        case 'X':
            break;
        case ' ':
            d_add(cval, d);
            break;
        case 'P':
            *cval += 0b10000000;
            d_add(cval, d);
            break;
        case 'K':
            *cval += 0b01000000;
            d_add(cval, d);
            break;
        default:
            return 1;
    }
    return 0;
}

static int flenleft(FILE* in, char buf[BUFSIZE]) {
    int len = 0;
    while (1) {
        size_t llen = fread(buf, 1, BUFSIZE, in);
        if (ferror(in))
            return -1;

        for (int i = 0; i < llen; i++) {
            if (buf[i] == '\n')
                len++;
        }

        if (feof(in))
            break;
    }
    return len;
}

enum PARSE_MAZE_RETURN_CODE parse_maze(const char* filename,
                                   struct maze* m,
                                   FILE* tmp_file) {
    enum PARSE_MAZE_RETURN_CODE ret = OK;

    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        ret = INPUT_CANT_BE_OPENED;
        goto out;
    }
    if (tmp_file == NULL) {
        ret = OUTPUT_CANT_BE_OPENED;
        goto out_close_input;
    }

    char b[BUFSIZE],
        bprev[BUFSIZE],
        bnext[BUFSIZE];

    if (fgets(b, BUFSIZE, in) == NULL) {
        ret = INPUT_READ_ERROR;
        goto out_close_input;
    }
    m->width = strlen(b) / 2 - 1;
    m->height = flenleft(in, b) / 2;
    if (m->height <= 0 || m->width <= 0) {
        ret = INPUT_INVALID;
        goto out_close_input;
    }
    rewind(in);

    int b_i = 0; // position of buffer b in file
    int b_j = 0; // position while iterating over b contents
    int maze_i = 0, // position in maze
        maze_j = 0;

    // load initial data into the buffers
    if (fgets(bnext, BUFSIZE, in) == NULL) {
        ret = INPUT_READ_ERROR;
        goto out_close_input;
    }
    strcpy(bprev, bnext);
    if (fgets(bnext, BUFSIZE, in) == NULL) {
        ret = INPUT_READ_ERROR;
        goto out_close_input;
    }
    strcpy(b, bnext);
    b_i++;

    while (fgets(bnext, BUFSIZE, in) != NULL) {
        if (ferror(in)) {
            ret = INPUT_READ_ERROR;
            goto out_close_input;
        }
        if (b_i % 2 == 1) {
            /* printf("bprev: \t\t%sb: \t\t%sbnext: \t\t%s\n", bprev, b, bnext); */
            for (b_j = 0, maze_j = 0; b_j < strlen(b) - 1; b_j++) {
                if (b_j % 2 == 0)
                    continue;

                unsigned char cell = b[b_j];
                if (cell != ' ') {
                    ret = INPUT_INVALID;
                    goto out_close_input;
                }
                cell = 0;
                const char adjN = bprev[b_j];
                const char adjE = b[b_j + 1];
                const char adjS = bnext[b_j];
                const char adjW = b[b_j - 1];
                char ret;
                ret = cell_encode(&cell, 'N', adjN);
                ret = cell_encode(&cell, 'E', adjE);
                ret = cell_encode(&cell, 'S', adjS);
                ret = cell_encode(&cell, 'W', adjW);
                if (ret != 0) {
                    ret = INPUT_INVALID;
                    goto out_close_input;
                }

                fputc(cell, ou);
                if (ferror(ou)) {
                    ret = OUTPUT_WRITE_ERROR;
                    goto out_close_input;
                }
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

out_close_input:
    fclose(in);
out:
    return ret;
}

enum PARSE_MAZE_RETURN_CODE get_cell_data(FILE *data, const int index, unsigned char* cell_data) {
    enum PARSE_MAZE_RETURN_CODE ret = OK;


    if(data == NULL) {
        ret = OUTPUT_CANT_BE_OPENED;
        goto close;
    }

    if(fseek(data, index, SEEK_SET) != 0) {
        ret = OUTPUT_READ_ERROR;
        goto close;
    }
    *cell_data = fgetc(data);
    if(*cell_data == EOF)
    {
        ret = OUTPUT_READ_ERROR;
        goto close;
    }


close:
    return ret;
}

enum PARSE_MAZE_RETURN_CODE set_cell_parent(FILE *data, const int index, const enum DIRECTIONS parent) {
    enum PARSE_MAZE_RETURN_CODE ret = OK;

    if(fseek(data, index, SEEK_SET) != 0) {
        ret = OUTPUT_WRITE_ERROR;
        goto close;
    }
    unsigned char cell_data = fgetc(data);
    cell_data += parent << 4;

    fseek(data, index, SEEK_SET);
    fputc(cell_data, data);
    if(ferror(data)) {
        ret = OUTPUT_WRITE_ERROR;
        goto close;
    }

close:
    return ret;
}