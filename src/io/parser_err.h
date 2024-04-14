#ifndef _PARSER_ERR_H
#define _PARSER_ERR_H

enum PARSE_STATUS {
    PARSE_OK = 0,
    PARSE_INPUT_READ_ERROR = 1,
    PARSE_INPUT_INVALID = 2,
    PARSE_OUTPUT_WRITE_ERROR = 3
};

void print_parse_maze_err(enum PARSE_STATUS s,
                          char* scriptname);

#endif
