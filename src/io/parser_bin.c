#include <stdio.h>

#include "../maze.h"
#include "binio.h"
#include "parser_bin.h"
#include "parser_err.h"
#include "parser_reg.h"

enum PARSE_STATUS bin_to_reg(struct bin_format bf, FILE* in, FILE* tmpf_in) {
    int ret = PARSE_OK;
    int colpos = 0;

    for (int i = 0; i < bf.HEADER.CNTR; i++) {
        if ((ret = serialize_codeword(&bf, in)) != 0) {
            if (ret == 1)
                return PARSE_INPUT_READ_ERROR;
            if (ret == 2)
                return PARSE_INPUT_INVALID;
        }
        for (int j = 0; j < bf.CODEWORD.CNT + 1; j++) {
            fputc(bf.CODEWORD.VAL, tmpf_in);
            if (ferror(tmpf_in))
                return PARSE_OUTPUT_WRITE_ERROR;
            colpos++;
            if (colpos == bf.HEADER.COLS) {
                fputc('\n', tmpf_in);
                if (ferror(tmpf_in))
                    return PARSE_OUTPUT_WRITE_ERROR;
                colpos = 0;
            }
        }
    }

    return PARSE_OK;
}

enum PARSE_STATUS parse_maze_bin(FILE* in, struct maze* m, FILE* tmpf) {
    int ret = PARSE_OK;
    struct bin_format bf;

    if ((ret = serialize_header(&bf, in)) != 0) {
        if (ret == 1)
            return PARSE_INPUT_READ_ERROR;
        if (ret == 2)
            return PARSE_INPUT_INVALID;
    }

    m->width = (bf.HEADER.COLS - 1) / 2;
    m->height = (bf.HEADER.ROWS - 1) / 2;
    m->start_index = bf.HEADER.SY - 1 + m->width * bf.HEADER.SX - 1;
    m->end_index = bf.HEADER.EY - 1 + m->width * bf.HEADER.EX - 1;

    FILE* tmpf_in = tmpfile();
    if (tmpf_in == NULL)
        return PARSE_OUTPUT_WRITE_ERROR;

    if ((ret = bin_to_reg(bf, in, tmpf_in)) != PARSE_OK)
        goto out_close_tmpf_in;

    rewind(in);
    ret = parse_maze_reg_structure(tmpf_in, m, tmpf);

out_close_tmpf_in:
    fclose(tmpf_in);
    return ret;
}
