#include <getopt.h>
#include <stdio.h>

#include "config.h"

enum BUILD_CONFIG_STATUS build_config(struct config* cfg,
                                      int argc,
                                      char **argv) {
    int c;
    // hide builtin errs
    opterr = 0;

    while ((c = getopt(argc, argv, CONFIG_FLAGS)) != -1) {
        switch (c) {
            case 'b':
                cfg->is_input_binary = 1;
                break;
            case 'h':
                return BUILD_CONFIG_INCORRECT_HELP_USAGE;
            case '?':
                switch (optopt) {
                    case 'h':
                        return BUILD_CONFIG_INCORRECT_HELP_USAGE;
                    default:
                        return BUILD_CONFIG_UNKNOWN_ARGUMENT;
                }
            default:
                return BUILD_CONFIG_UNKNOWN_ARGUMENT;
        }
    }

    argc -= optind;
    argv += optind;

    if (argc < 1)
        return BUILD_CONFIG_MISSING_INPUT_FILE_ARGUMENT;
    if (argc > 1) 
        return BUILD_CONFIG_TOO_MANY_ARGUMENTS;

    cfg->input_file = *argv;

    return BUILD_CONFIG_OK;
}

void print_build_config_err(enum BUILD_CONFIG_STATUS s, char* scriptname) {
    switch (s) {
        case BUILD_CONFIG_UNKNOWN_ARGUMENT:
            fprintf(stderr,
                    "%s: nieznany argument '-%c'\n",
                    scriptname,
                    optopt);
            break;
        case BUILD_CONFIG_MISSING_INPUT_FILE_ARGUMENT:
            fprintf(stderr, "%s: brak nazwy pliku wejściowego\n", scriptname);
            break;
        case BUILD_CONFIG_TOO_MANY_ARGUMENTS:
            fprintf(stderr, "%s: zbyt dużo argumentów\n", scriptname);
            break;
        case BUILD_CONFIG_INCORRECT_HELP_USAGE:
            fprintf(stderr,
                    "%s: niepoprawne użycie argumentu '-h'\n",
                    scriptname);
            break;
        case BUILD_CONFIG_OK:
            break;
    }
    fprintf(stderr, "więcej informacji: '%s -h'\n", scriptname);
}
