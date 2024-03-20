#include <stdlib.h>

#include "parser.h"

int main(int argc, char** argv) {
    char* filename = argc > 1 ? argv[1] : "data/3.txt";
    struct maze* maze = malloc(sizeof(struct maze));
    parse_maze(filename, maze);

    return 0;
}
