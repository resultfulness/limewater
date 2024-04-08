#ifndef _PARSER_ERR_H
#define _PARSER_ERR_H

enum PARSE_MAZE_STATUS {
    OK = 0,
    INPUT_INVALID = 1,
    INPUT_CANT_BE_OPENED = 10,
    INPUT_READ_ERROR = 11,
    OUTPUT_CANT_BE_OPENED = 20,
    OUTPUT_READ_ERROR = 21,
    OUTPUT_WRITE_ERROR = 22
};

void print_parse_maze_err(enum PARSE_MAZE_STATUS s,
                          char* scriptname,
                          char* input_fn);

#endif
