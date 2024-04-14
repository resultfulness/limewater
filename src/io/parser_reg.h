#ifndef _PARSER_REG_H
#define _PARSER_REG_H

#include <stdio.h>

#include "../maze.h"
#include "parser_err.h"

#define BUFSIZE 1024*2+1

/**
 * @brief uses the input file to fill the maze struct fields with metadata about
 * the maze; the file gets read in its entirety and needs to be rewound
 *
 * @param in input file
 * @param m maze struct to save the metadata to
 * @return PARSE_STATUS error enum
 */
enum PARSE_STATUS parse_maze_reg_meta(FILE* in, struct maze* m);
enum PARSE_STATUS parse_maze_reg_structure(FILE* in, struct maze* m, FILE* tmpf);

#endif
