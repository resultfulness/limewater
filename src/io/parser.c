#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "parser_bin.h"
#include "parser_err.h"
#include "parser_reg.h"

enum PARSE_MAZE_STATUS parse_maze(struct config cfg,
                                  struct maze* m,
                                  FILE* tmpf) {
    enum PARSE_MAZE_STATUS ret = OK;

    FILE* in = fopen(cfg.input_file, "r");
    if (in == NULL) {
        ret = INPUT_CANT_BE_OPENED;
        goto out;
    }
    if (tmpf == NULL) {
        ret = OUTPUT_CANT_BE_OPENED;
        goto out_close_input;
    }

    if (!cfg.is_input_binary) {
        ret = parse_maze_reg_meta(in, m);
        if (ret != OK)
            goto out_close_input;

        ret = parse_maze_reg_structure(in, tmpf);
        if (ret != OK)
            goto out_close_input;
    } else {
        parse_maze_bin(in, m, tmpf);
    }

out_close_input:
    fclose(in);
out:
    return ret;
}
