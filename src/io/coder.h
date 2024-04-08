#ifndef _CODER_H
#define _CODER_H

#include <stdio.h>

#define START_ENCODE_VALUE 128 /* 0b10000000 */
#define END_ENCODE_VALUE 64    /* 0b01000000 */

enum PARENT_DIRECTION { 
    PARENT_NORTH = 48, /* 0b00110000 */
    PARENT_WEST = 32,  /* 0b00100000 */
    PARENT_EAST = 16,  /* 0b00010000 */
    PARENT_SOUTH = 0   /* 0b00000000 */
};

enum DIRECTION {
    NORTH = 8, /* 0b00001000 */
    EAST  = 4, /* 0b00000100 */
    SOUTH = 2, /* 0b00000010 */
    WEST  = 1  /* 0b00000001 */
};

int get_cell_data(FILE *data, const int index, char* cell_data);
int set_cell_parent(FILE *data, const int index, enum PARENT_DIRECTION parent);
int cell_encode(char* cval,
                const char n,
                const char e,
                const char s,
                const char w);


#endif
