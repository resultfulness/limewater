#include <stdlib.h>

#include "parser.h"

int main(int argc, char** argv) {
    char* filename = argc > 1 ? argv[1] : "data/16.txt";
    struct maze* maze = malloc(sizeof(struct maze));
    enum PARSE_MAZE_RETURN_CODE err;
    FILE *data = parse_maze(filename, maze, &err);
    if(err != 0)
        return err;
    return 0;
}
