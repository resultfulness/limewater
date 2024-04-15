#ifndef _OUT_BIN_H
#define _OUT_BIN_H

#include <stdio.h>

#include "../maze.h"

/**
 * @brief updates binary file with solution encoded in the temporary file,
 * advancing the binary file to eof
 *
 * @param in binary file where solution will be stored
 * @param tmpf file where the encoded solved maze is stored
 * @param maze struct with metadata about the maze
 * @param sol_offset offset of the solution section in the binary file
 * @return 0 if ok, -1 if solution offset is zero, 1 if file io error
 */
int bin_update_with_sol(FILE* in, FILE* tmpf, struct maze m, int sol_offset);


#endif
