#include <stdio.h>

#include "coder.h"

int get_cell_data(FILE* data,
                  const int index,
                  char* cell_data) {
    if(data == NULL)
        return 1;
    if(fseek(data, index, SEEK_SET) != 0)
        return 1;

    *cell_data = fgetc(data);
    if (feof(data) || ferror(data))
        return 1;
    return 0;
}

int set_cell_parent(FILE* data,
                    const int index,
                    const enum PARENT_DIRECTION parent) {
    if(fseek(data, index, SEEK_SET) != 0)
        return 1;

    char cell_data = fgetc(data);
    if (feof(data) || ferror(data))
        return 1;
    cell_data = cell_data & 79; // 0b01001111
    cell_data += parent;
    cell_data += VISITED_STATE_VALUE;

    if(fseek(data, index, SEEK_SET) != 0)
        return 1;
    fputc(cell_data, data);
    if(ferror(data))
        return 1;

    return 0;
}

static int cell_handle_adj(char* cval, const char adj, enum DIRECTION d) {
    switch (adj) {
        case 'X':
            break;
        case ' ':
            *cval += d;
            break;
        case 'P':
            break;
        case 'K':
            *cval += END_ENCODE_VALUE;
            break;
        default:
            return 1;
    }
    return 0;
}

int cell_encode(char* cval,
                       const char n,
                       const char e,
                       const char s,
                       const char w) {
    if (cell_handle_adj(cval, n, NORTH) == 1)
        return 1;
    if (cell_handle_adj(cval, e, EAST) == 1)
        return 1;
    if (cell_handle_adj(cval, s, SOUTH) == 1)
        return 1;
    if (cell_handle_adj(cval, w, WEST) == 1)
        return 1;

    return 0;
}

