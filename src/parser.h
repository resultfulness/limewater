#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>

#define BUFSIZE 1024*2+1

struct maze { int width; int height; };

enum PARSE_MAZE_RETURN_CODE {
    OK = 0,
    INPUT_INVALID = 1,
    INPUT_CANT_BE_OPENED = 10,
    INPUT_READ_ERROR = 11,
    OUTPUT_CANT_BE_OPENED = 20,
    OUTPUT_READ_ERROR = 21,
    OUTPUT_WRITE_ERROR = 22,
};

/* encoding scheme */

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

enum PARSE_MAZE_RETURN_CODE parse_maze(const char* filename,
                                       struct maze* m,
                                       FILE* tmp_file);
int get_cell_data(FILE *data, const int index, char* cell_data);
int set_cell_parent(FILE *data, const int index, enum PARENT_DIRECTION parent);
void print_parse_maze_err(enum PARSE_MAZE_RETURN_CODE ret,
                          char* scriptname,
                          char* input_fn);

#endif
