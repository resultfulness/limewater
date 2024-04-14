#ifndef _PATH_FINDER_H_
#define _PATH_FINDER_H_

#include <stdio.h>
#include "maze.h"
#include "./data_structures/queue.h"
#include "./io/coder.h"

/**
 * @brief finds path in maze structure using BFS algorithm
 *        and saves the path to data
 * 
 * @param data  file where the encoded maze is stored
 * @param m     maze structure with maze metadata  
 * @return 0 if ok, 1 if data is corrupted
 */
int find_path_in_maze(FILE* data, struct maze* m);

#endif