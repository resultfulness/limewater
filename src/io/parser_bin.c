#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "../maze.h"
#include "parser_bin.h"
#include "coder.h"
#include "parser.h"
#include "parser_err.h"

char* read_uint8(char* buffer, uint8_t* val) {
    *val = *buffer++;
    return buffer;
}

char* read_uint16_le(char* buffer, uint16_t* val) {
    uint8_t low, high;

    buffer = read_uint8(buffer, &high);
    buffer = read_uint8(buffer, &low);
    /* low first because little endian */
    *val = (low << 8) | high;
    return buffer;
}

char* read_uint32_le(char* buffer, uint32_t* val) {
    uint16_t low, high;

    buffer = read_uint16_le(buffer, &high);
    buffer = read_uint16_le(buffer, &low);
    /* low first because little endian */
    *val = (low << 16) | high;
    return buffer;
}

int serialize_header(struct bin_format* bf, FILE* in) {
    char b[HEADER_TOTAL_BYTES];
    char* buf = b;
    
    fread(buf, sizeof b, 1, in);
    if (feof(in) || ferror(in))
        return 1;
    buf = read_uint32_le(buf, &bf->HEADER.FID);
    buf = read_uint8(buf, &bf->HEADER.ESC);
    buf = read_uint16_le(buf, &bf->HEADER.COLS);
    buf = read_uint16_le(buf, &bf->HEADER.ROWS);
    buf = read_uint16_le(buf, &bf->HEADER.SX);
    buf = read_uint16_le(buf, &bf->HEADER.SY);
    buf = read_uint16_le(buf, &bf->HEADER.EX);
    buf = read_uint16_le(buf, &bf->HEADER.EY);
    buf = read_uint32_le(buf, &bf->HEADER.RESERVED_1);
    buf = read_uint32_le(buf, &bf->HEADER.RESERVED_2);
    buf = read_uint32_le(buf, &bf->HEADER.RESERVED_3);
    buf = read_uint32_le(buf, &bf->HEADER.CNTR);
    buf = read_uint32_le(buf, &bf->HEADER.SOFF);
    buf = read_uint8(buf, &bf->HEADER.SEP);
    buf = read_uint8(buf, &bf->HEADER.WALL);
    buf = read_uint8(buf, &bf->HEADER.PATH);
    return 0;
}

int serialize_codeword(struct bin_format bf,
                       FILE* in,
                       struct bin_codeword* bc) {
    char b[CODEWORD_TOTAL_BYTES];
    char* buf = b;
    
    fread(buf, sizeof b, 1, in);
    if (feof(in) || ferror(in))
        return 1;

    buf = read_uint8(buf, &bc->SEP);
    buf = read_uint8(buf, &bc->VAL);
    buf = read_uint8(buf, &bc->CNT);
    return 0;
}

int buf_fill_with_maze_text(char* buffer, struct bin_format bf, FILE* in) {
    struct bin_codeword bc;
    int counter = 0;
    while (counter < bf.HEADER.COLS - 1) {
        if (serialize_codeword(bf, in, &bc) != 0)
            return 1;
        for (int i = 0; i < bc.CNT + 1; i++) {
            buffer[counter + i] = bc.VAL;
        }
        counter += bc.CNT + 1;
    }
    return 0;
}

int parse_maze_bin_structure(struct bin_format bf, FILE* in, FILE* tmpf) {
    char b[BUFSIZE],
        bprev[BUFSIZE],
        bnext[BUFSIZE];

    if (buf_fill_with_maze_text(bnext, bf, in) != 0)
        return 1;
    strcpy(bprev, bnext);

    if (buf_fill_with_maze_text(bnext, bf, in) != 0)
        return 1;
    strcpy(b, bnext);
    
    printf("%s\n", bprev);
    printf("%s\n", b);
    while (buf_fill_with_maze_text(bnext, bf, in) != 1)
        printf("%s\n", bnext);

    return 0;
}

enum PARSE_MAZE_STATUS parse_maze_bin(FILE* in, struct maze* m, FILE* tmpf) {
    struct bin_format bf;

    serialize_header(&bf, in);

    m->width = bf.HEADER.COLS - 1;
    m->height = bf.HEADER.ROWS - 1;
    m->start_index = bf.HEADER.SY - 1 + m->width * bf.HEADER.SX - 1;
    m->end_index = bf.HEADER.EY - 1 + m->width * bf.HEADER.EX - 1;
    
    parse_maze_bin_structure(bf, in, tmpf);

    char c;
    get_cell_data(tmpf, 752, &c);
    printf("%b\n", c);

    return OK;
}
