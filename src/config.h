#ifndef _CONFIG_H
#define _CONFIG_H

#define CONFIG_FLAGS "b"

struct config {
    int is_input_binary;
    char* input_file;
};

enum BUILD_CONFIG_STATUS {
    BUILD_CONFIG_OK,
    BUILD_CONFIG_UNKNOWN_ARGUMENT,
    BUILD_CONFIG_MISSING_INPUT_FILE_ARGUMENT,
    BUILD_CONFIG_TOO_MANY_ARGUMENTS,
    BUILD_CONFIG_INCORRECT_HELP_USAGE
};

enum BUILD_CONFIG_STATUS build_config(struct config* cfg,
                                      int argc,
                                      char** argv);
void print_build_config_err(enum BUILD_CONFIG_STATUS s, char* scriptname);

#endif
