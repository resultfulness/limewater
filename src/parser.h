#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>

#define BUFSIZE 1024*2+1
#define MAZE_DATA_FILENAME "/tmp/savior.limewater"

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

enum DIRECTIONS { 
    N = 0b00000011,
    E = 0b00000010,
    W = 0b00000001,
    S = 0b00000000,
};

FILE *parse_maze(const char* filename, struct maze* m, enum PARSE_MAZE_RETURN_CODE *err);
enum PARSE_MAZE_RETURN_CODE get_cell_data(FILE *data, const int index, unsigned char* cell_data);
enum PARSE_MAZE_RETURN_CODE set_cell_parent(FILE *data, const int index, const enum DIRECTIONS parent);
enum PARSE_MAZE_RETURN_CODE parse_maze(const char* filename,
                                       struct maze* m,
                                       FILE* tmp_file);

#endif
