#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static void d_add(char* cval, const char d) {
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

static int cell_encode(char* cval, const char d, const char dval) {
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

enum PARSE_MAZE_RETURN_CODE parse_maze(const char* filename, struct maze* m) {
    enum PARSE_MAZE_RETURN_CODE ret = OK;

    FILE* in = fopen(filename, "r");
    if (in == NULL)
        return INPUT_CANT_BE_OPENED;
    FILE* ou = fopen("/tmp/savior.limewater", "w");
    if (ou == NULL) {
        ret = OUTPUT_CANT_BE_OPENED;
        goto out_close_input;
    }

    char b[BUFSIZE],
        bprev[BUFSIZE],
        bnext[BUFSIZE];

    if (fgets(b, BUFSIZE, in) == NULL) {
        ret = INPUT_READ_ERROR;
        goto out_close_all;
    }
    m->width = strlen(b) / 2 - 1;
    m->height = flenleft(in, b) / 2;
    if (m->height <= 0 || m->width <= 0) {
        ret = INPUT_INVALID;
        goto out_close_all;
    }
    rewind(in);

    int b_i = 0; // position of buffer b in file
    int b_j = 0; // position while iterating over b contents
    int maze_i = 0, // position in maze
        maze_j = 0;

    // load initial data into the buffers
    if (fgets(bnext, BUFSIZE, in) == NULL) {
        ret = INPUT_READ_ERROR;
        goto out_close_all;
    }
    strcpy(bprev, bnext);
    if (fgets(bnext, BUFSIZE, in) == NULL) {
        ret = INPUT_READ_ERROR;
        goto out_close_all;
    }
    strcpy(b, bnext);
    b_i++;

    while (fgets(bnext, BUFSIZE, in) != NULL) {
        if (ferror(in)) {
            ret = INPUT_READ_ERROR;
            goto out_close_all;
        }
        if (b_i % 2 == 1) {
            /* printf("bprev: \t\t%sb: \t\t%sbnext: \t\t%s\n", bprev, b, bnext); */
            for (b_j = 0, maze_j = 0; b_j < strlen(b) - 1; b_j++) {
                if (b_j % 2 == 0)
                    continue;

                char cell = b[b_j];
                if (cell != ' ') {
                    ret = INPUT_INVALID;
                    goto out_close_all;
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
                    goto out_close_all;
                }

                fputc(cell, ou);
                if (ferror(ou)) {
                    ret = OUTPUT_WRITE_ERROR;
                    goto out_close_all;
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

out_close_all:
    fclose(ou);
out_close_input:
    fclose(in);

    return ret;
}
