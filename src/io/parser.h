#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>

#include "../maze.h"
#include "parser_err.h"

#define BUFSIZE 1024*2+1

enum PARSE_MAZE_RETURN_CODE parse_maze(const char* filename,
                                       int is_binary,
                                       struct maze* m,
                                       FILE* tmpf);

#endif
