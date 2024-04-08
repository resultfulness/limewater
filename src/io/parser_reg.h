#ifndef _PARSER_REG_H
#define _PARSER_REG_H

#include <stdio.h>
#include "parser_err.h"

enum PARSE_MAZE_STATUS parse_maze_reg_meta(FILE* in, struct maze* m);
enum PARSE_MAZE_STATUS parse_maze_reg_structure(FILE* in, FILE* tmpf);

#endif
