#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "help.h"
#include "io/parser_bin.h"
#include "io/parser_err.h"
#include "io/parser_reg.h"

int main(int argc, char** argv) {
    int ret = 0;

    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_help(argv[0]);
        goto out;
    }

    struct maze* maze = malloc(sizeof(struct maze));
    if (maze == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        ret = 1;
        goto out;
    }
    struct config* cfg =  malloc(sizeof(struct config));
    if (cfg == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        ret = 1;
        goto out_free_maze;
    }

    if ((ret = build_config(cfg, argc, argv)) != 0) {
        print_build_config_err(ret, argv[0]);
        ret = 1;
        goto out_free_cfg;
    }

    FILE* tmpf = tmpfile();
    if (tmpf == NULL) {
        fprintf(stderr,
                "%s: nie udało się otworzyć pliku tymczasowego\n",
                argv[0]);
        ret = 1;
        goto out_free_cfg;
    }
    
    FILE* in = fopen(cfg->input_file, "r");
    if (in == NULL) {
        fprintf(stderr,
                "%s: nie udało się otworzyć pliku '%s'\n",
                argv[0],
                cfg->input_file);
        ret = 1;
        goto out_close_tmp;
    }

    if (!cfg->is_input_binary) {
        if ((ret = parse_maze_reg_meta(in, maze)) != PARSE_OK) {
            print_parse_maze_err(ret, argv[0]);
            ret = 1;
            goto out_close_in;
        }
        if ((ret = parse_maze_reg_structure(in, maze, tmpf)) != PARSE_OK) {
            print_parse_maze_err(ret, argv[0]);
            ret = 1;
            goto out_close_in;
        }
    } else {
        if ((ret = parse_maze_bin(in, maze, tmpf)) != PARSE_OK) {
            print_parse_maze_err(ret, argv[0]);
            ret = 1;
            goto out_close_in;
        }
    }

out_close_in:
    fclose(in);
out_close_tmp:
    fclose(tmpf);
out_free_cfg:
    free(cfg);
out_free_maze:
    free(maze);
out:
    return ret;
}
