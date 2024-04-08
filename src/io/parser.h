#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>

#include "../config.h"
#include "../maze.h"
#include "parser_err.h"

#define BUFSIZE 1024*2+1

enum PARSE_MAZE_STATUS parse_maze(struct config cfg,
                                  struct maze* m,
                                  FILE* tmpf);

#endif
