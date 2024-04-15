#ifndef _OUT_REG_H_
#define _OUT_REG_H_

#include <stdio.h>
#include "../maze.h"
#include "coder.h"

/**
 * @brief changes data structure in a way that reverses route from end to start
 *        to start to end
 * 
 * @param data  file where the encoded maze is stored
 * @param m     maze structure with maze metadata  
 */
void reverse_path(FILE *data, struct maze *m);

/**
 * @brief prints route from start_cell to end_cell to stdout in format
 *        TURNLEFT/TURNRIGHT
 *        FORWARD (n), where n is the amount of concurrent steps
 *        where the starting direction is right regardless of maze structure
 * 
 * @param data  file where the encoded maze is stored
 * @param m     maze structure with maze metadata  
 */
void print_path(FILE *data, struct maze *m);

#endif
