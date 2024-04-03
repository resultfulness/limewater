#include <stdlib.h>

#include "parser.h"

int main(int argc, char** argv) {
    int ret = 0;
    char* input_fn = argc > 1 ? argv[1] : "data/16.txt";
    struct maze* maze = malloc(sizeof(struct maze));
    if (maze == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        ret = 1;
        goto out;
    }
    FILE* tmp = fopen(TEMP_FILE_PATH, "w+");
    if (tmp == NULL) {
        fprintf(stderr,
                "%s: nie udało się otworzyć pliku '%s'\n",
                argv[0],
                TEMP_FILE_PATH);
        ret = 1;
        goto out_free_maze;
    }
    ret = parse_maze(input_fn, maze, tmp);
    if (ret != 0) {
        print_parse_maze_err(ret, argv[0], input_fn, TEMP_FILE_PATH);
        ret = 1;
        goto out_close_tmp;
    }

out_close_tmp:
    fclose(tmp);
out_free_maze:
    free(maze);
out:
    return ret;
}
