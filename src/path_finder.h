#ifndef _PATH_FINDER_H_
#define _PATH_FINDER_H_

#include <stdio.h>
#include "maze.h"
#include "./data_structures/queue.h"
#include "./io/coder.h"

int find_path_in_maze(FILE* in, struct maze* m);

#endif