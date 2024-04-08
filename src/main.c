#include <stdlib.h>

#include "io/parser.h"
#include "io/parser_err.h"

int main(int argc, char** argv) {
    int ret = 0;
    char* in_filename = argc > 1 ? argv[1] : "data/16.txt";
    struct maze* maze = malloc(sizeof(struct maze));
    if (maze == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        ret = 1;
        goto out;
    }
    FILE* tmpf = tmpfile();
    if (tmpf == NULL) {
        fprintf(stderr,
                "%s: nie udało się otworzyć pliku tymczasowego\n",
                argv[0]);
        ret = 1;
        goto out_free_maze;
    }
    ret = parse_maze(in_filename, 0, maze, tmpf);
    if (ret != 0) {
        print_parse_maze_err(ret, argv[0], in_filename);
        ret = 1;
        goto out_close_tmp;
    }

out_close_tmp:
    fclose(tmpf);
out_free_maze:
    free(maze);
out:
    return ret;
}
