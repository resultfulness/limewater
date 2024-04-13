#ifndef _PARSER_BIN_H
#define _PARSER_BIN_H

#include <stdio.h>
#include <stdint.h>
#include "parser_err.h"

#define HEADER_TOTAL_BYTES 40
#define CODEWORD_TOTAL_BYTES 3

struct bin_header {
    uint32_t FID;
    uint8_t ESC;
    uint16_t COLS;
    uint16_t ROWS;
    uint16_t SX;
    uint16_t SY;
    uint16_t EX;
    uint16_t EY;
    uint32_t RESERVED_1;
    uint32_t RESERVED_2;
    uint32_t RESERVED_3;
    uint32_t CNTR;
    uint32_t SOFF;
    uint8_t SEP;
    uint8_t WALL;
    uint8_t PATH;
};

struct bin_codeword {
    uint8_t SEP;
    uint8_t VAL;
    uint8_t CNT;
};

struct bin_sol_header {
    uint32_t SID : 32;
    uint8_t STEPS : 8;
};

struct bin_sol_step {
    uint8_t DIR;
    uint8_t CNT;
};

struct bin_format {
    struct bin_header HEADER;
    struct bin_codeword* CODEWORDS;
    struct bin_sol_header SOL_HEADER;
    struct bin_sol_step* SOL_STEPS;
};

enum PARSE_MAZE_STATUS parse_maze_bin(FILE* in,
                                      struct maze* m,
                                      FILE* tmpf);

#endif
