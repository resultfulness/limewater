#include <stdio.h>

#include "out_bin.h"
#include "binio.h"
#include "coder.h"

char get_dir_c(enum PARENT_DIRECTION d) {
    switch (d) {
        case PARENT_NORTH:
            return 'N';
        case PARENT_EAST:
            return 'E';
        case PARENT_SOUTH:
            return 'S';
        case PARENT_WEST:
            return 'W';
    }
}

int bin_update_with_sol(FILE *in, FILE *tmpf, struct maze m, int sol_offset) {
    if (sol_offset == 0)
        return -1;

    struct bin_format bf;
    if (fseek(in, sol_offset + sizeof(bf.SOL_HEADER.SID), SEEK_SET) != 0)
        return 1;
    int sol_steps = -1;
    fputc(sol_steps, in);

    int cindex = m.start_index;
    char cval = 0;

    get_cell_data(tmpf, cindex, &cval);
    enum PARENT_DIRECTION d = cval & PARENT_NORTH;
    enum PARENT_DIRECTION prevd = PARENT_WEST;

    int mcntr = 0;
    
    while (cindex != m.end_index) {
        switch (d) {
            case PARENT_NORTH:
                cindex -= m.width;
                break;
            case PARENT_EAST:
                cindex++;
                break;
            case PARENT_SOUTH:
                cindex += m.width;
                break;
            case PARENT_WEST:
                cindex--;
                break;
        }
        if (get_cell_data(tmpf, cindex, &cval) != 0)
            return 1;
        prevd = d;
        d = cval & PARENT_NORTH;
        if (d != prevd && cindex != m.end_index) {
            fputc(get_dir_c(prevd), in);
            fputc(mcntr, in);
            sol_steps++;
            mcntr = 0;
        } else {
            mcntr++;
        }
    }
    fputc(get_dir_c(prevd), in);
    fputc(mcntr, in);
    sol_steps++;

    if (fseek(in, sol_offset + sizeof(bf.SOL_HEADER.SID), SEEK_SET) != 0)
        return 1;
    fputc(sol_steps, in);

    return 0;
}
