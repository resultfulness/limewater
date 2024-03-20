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
    OUTPUT_WRITE_ERROR = 22,
};
enum PARSE_MAZE_RETURN_CODE parse_maze(const char* filename, struct maze* m);

#endif
