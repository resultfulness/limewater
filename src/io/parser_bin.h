#ifndef _PARSER_BIN_H
#define _PARSER_BIN_H

#include <stdio.h>

#include "../maze.h"
#include "binio.h"
#include "parser_err.h"

/**
 * @brief using a list of binary codewords, produces a regular format maze and
 * stores it in a temporary file; the input file will be advanced past the 
 * codewords section
 *
 * @param bf binary file format
 * @param in binary input file at the beginning of the codeword section
 * @param tmpf_in temporary file where the regular format maze will be stored
 * @return PARSE_STATUS error enum
 */
enum PARSE_STATUS bin_to_reg(struct bin_format bf, FILE* in, FILE* tmpf_in);

/**
 * @brief parses a binary maze file, storing metadata in a maze struct and the 
 * encoded maze in an output file; the binary input file will be advanced to
 * the start of the solution header section
 *
 * @param in binary input file
 * @param m maze structure for maze metadata
 * @param tmpf file where the encoded maze will be stored
 * @param sol_offset solution offset for use later on in printing the solution
 * out
 * @return PARSE_STATUS error enum
 */
enum PARSE_STATUS parse_maze_bin(FILE* in,
                                 struct maze* m,
                                 FILE* tmpf,
                                 int* sol_offset);

#endif
