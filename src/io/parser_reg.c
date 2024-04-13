#include <stdio.h>
#include <string.h>

#include "coder.h"
#include "parser.h"
#include "parser_err.h"
#include "parser_reg.h"

enum PARSE_MAZE_STATUS parse_maze_reg_meta(FILE* in, struct maze* m) {
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

enum PARSE_MAZE_STATUS parse_maze_reg_structure(FILE* in,
                                                struct maze* m,
                                                FILE* tmpf) {
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

                if (cell & START_ENCODE_VALUE)
                    m->start_index = maze_i * m->width + maze_j;

                fputc(cell, tmpf);
                if (ferror(tmpf)) 
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
