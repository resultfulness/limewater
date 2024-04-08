#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "help.h"
#include "io/parser.h"
#include "io/parser_err.h"

int main(int argc, char** argv) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_help(argv[0]);
        goto out;
    }

    int ret = 0;

    struct maze* maze = malloc(sizeof(struct maze));
    struct config* cfg =  malloc(sizeof(struct config));
    if (maze == NULL || cfg == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        ret = 1;
        goto out;
    }

    ret = build_config(cfg, argc, argv);
    if (ret != 0) {
        print_build_config_err(ret, argv[0]);
        ret = 1;
        goto out_free_maze;
    }

    FILE* tmpf = tmpfile();
    if (tmpf == NULL) {
        fprintf(stderr,
                "%s: nie udało się otworzyć pliku tymczasowego\n",
                argv[0]);
        ret = 1;
        goto out_free_maze;
    }

    ret = parse_maze(*cfg, maze, tmpf);
    if (ret != 0) {
        print_parse_maze_err(ret, argv[0], cfg->input_file);
        ret = 1;
        goto out_close_tmp;
    }

out_close_tmp:
    fclose(tmpf);
out_free_maze:
    free(cfg);
    free(maze);
out:
    return ret;
}
