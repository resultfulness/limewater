#include "out_reg.h"

char *get_turn(enum PARENT_DIRECTION parent, enum PARENT_DIRECTION child) {
    switch(parent) {
        case PARENT_WEST:
            switch(child) {
                case PARENT_SOUTH:
                    return "TURNLEFT";
                case PARENT_NORTH:
                    return "TURNRIGHT";
                default:
                    return "IMPOSSIBLETURN";
            }
        case PARENT_SOUTH:
            switch(child) {
                case PARENT_WEST:
                    return "TURNRIGHT";
                case PARENT_EAST:
                    return "TURNLEFT";
                default:
                    return "IMPOSSIBLETURN";
            }
        case PARENT_EAST:
            switch(child) {
                case PARENT_SOUTH:
                    return "TURNRIGHT";            
                case PARENT_NORTH:
                    return "TURNRIGHT";
                default:
                    return "IMPOSSIBLETURN";
            }
        case PARENT_NORTH:
            switch(child) {
                case PARENT_WEST:
                    return "TURNLEFT";
                case PARENT_EAST:
                    return "TURNRIGHT";
                default:
                    return "IMPOSSIBLETURN";
            }
        default:
            return "IMPOSSIBLETURN";
    }
    return "IMPOSSIBLETURN";
}

void reverse_path(FILE *data, struct maze *m) {
    int cell_index, parent_cell_index;
    char cell_data;
    enum PARENT_DIRECTION direction = PARENT_EAST;
    cell_index = m->end_index;
    while(cell_index != m->start_index) {
        get_cell_data(data, cell_index, &cell_data);
        set_cell_parent(data, cell_index, direction);

        switch(cell_data & PARENT_NORTH) {
            case PARENT_WEST:
                parent_cell_index = cell_index - 1;
                direction = PARENT_EAST;
                break;
            case PARENT_SOUTH:
                parent_cell_index = cell_index + m->width;
                direction = PARENT_NORTH;
                break;
            case PARENT_EAST:
                parent_cell_index = cell_index + 1;
                direction = PARENT_WEST;
                break;
            case PARENT_NORTH:
                parent_cell_index = cell_index - m->width;
                direction = PARENT_SOUTH;
                break;
        }
        cell_index = parent_cell_index;
    }

    set_cell_parent(data, cell_index, direction);
}

void print_path(FILE *data, struct maze *m, FILE *out) {
    enum PARENT_DIRECTION direction, previous_direction;
    int cell_index = m->start_index, move_counter = 1;
    char cell_data;
    get_cell_data(data, cell_index, &cell_data);
    previous_direction = PARENT_WEST;
    direction = cell_data & PARENT_NORTH;

    fprintf(out, "START\n");

    switch(direction) {
        case PARENT_NORTH:
            fprintf(out, "TURNLEFT\n");
            break;
        case PARENT_SOUTH:
            fprintf(out, "TURNRIGHT\n");
            break;
        case PARENT_EAST:
            fprintf(out, "TURNRIGHT\nTURNRIGHT\n");
            break;
        default:
            break;
    }
    while(cell_index != m->end_index) {
        switch(direction) {
            case PARENT_WEST:
                cell_index = cell_index - 1;
                break;
            case PARENT_SOUTH:
                cell_index = cell_index + m->width;
                break;
            case PARENT_EAST:
                cell_index = cell_index + 1;
                break;
            case PARENT_NORTH:
                cell_index = cell_index - m->width;
                break;
        }
        if(get_cell_data(data, cell_index, &cell_data) != 0) {
            fprintf(out, "Solution file corrupted\n");
            return;
        }
        previous_direction = direction;
        direction = cell_data & PARENT_NORTH;
        if(direction != previous_direction && cell_index != m->end_index) {
            fprintf(out, "FORWARD %d\n", move_counter);
            fprintf(out, "%s\n", get_turn(previous_direction, direction));
            move_counter = 1;
        }
        else
            move_counter++;
    }
    fprintf(out, "FORWARD %d\n", move_counter);
    fprintf(out, "STOP\n");
}
