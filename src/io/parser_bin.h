#ifndef _PARSER_BIN_H
#define _PARSER_BIN_H

#include <stdio.h>
#include "parser_err.h"

enum PARSE_MAZE_STATUS parse_maze_bin(FILE* in,
                                      struct maze* m,
                                      FILE* tmpf);

#endif
