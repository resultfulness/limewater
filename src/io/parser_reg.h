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

/**
 * @brief uses the input file to encode the maze in the output file, using the
 * scheme specified in coder.h
 *
 * @param in input file in standard maze format
 * @param m struct with metadata about the maze
 * @param tmpf output file where the encoded maze will be stored
 */
enum PARSE_STATUS parse_maze_reg_structure(FILE* in, struct maze* m, FILE* tmpf);

#endif
