#ifndef _CODER_H
#define _CODER_H

#include <stdio.h>

#define VISITED_STATE_VALUE 128 /* 0b10000000 */
#define END_ENCODE_VALUE 64    /* 0b01000000 */

enum PARENT_DIRECTION { 
    PARENT_NORTH = 48, /* 0b00110000 */
    PARENT_WEST = 32,  /* 0b00100000 */
    PARENT_EAST = 16,  /* 0b00010000 */
    PARENT_SOUTH = 0   /* 0b00000000 */
};

enum DIRECTION {
    NORTH = 8, /* 0b00001000 */
    EAST  = 4, /* 0b00000100 */
    SOUTH = 2, /* 0b00000010 */
    WEST  = 1  /* 0b00000001 */
};

/**
 * @brief gets the data of a cell at a given index from a given file and stores
 * it in the variable being pointed to by the given pointer
 *
 * @param data file with encoded cells
 * @param index index of cell to obtain data about
 * @param cell_data pointer to the variable where the cell's data will be stored
 * @return 0 if ok, 1 if there was an error reading the file
 */
int get_cell_data(FILE* data, const int index, char* cell_data);

/**
 * @brief sets parent info and visited state for a cell at a given index in a given file
 *
 * @param data file with encoded cells
 * @param index index of cell to set parent info for
 * @param parent parent info to encode
 * @return 0 if ok, 1 if there was an error reading or writing to the file
 */
int set_cell_parent(FILE* data, const int index, enum PARENT_DIRECTION parent);

/**
 * @brief using characters adjacent to the cell character, encodes the cell
 *
 * @param cval pointer to variable where the encoded cell will be stored
 * @param n character north of the cell character
 * @param e character east of the cell character
 * @param s character south of the cell character
 * @param w character west of the south character
 * @return 0 if ok, 1 if at least one of the characters is invalid
 */
int cell_encode(char* cval,
                const char n,
                const char e,
                const char s,
                const char w);


#endif
