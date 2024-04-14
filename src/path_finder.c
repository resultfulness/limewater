#include "path_finder.h"

int find_path_in_maze(FILE* in, struct maze* m) {
    struct queue* queue = NULL;
    struct queue* memory_queue = NULL;
    menqueue(&queue, m->start_index, &memory_queue);
    int current_cell_index;
    char current_cell_data, child_cell_data;

    while((current_cell_index = mdequeue(&queue, &memory_queue)) != -1) {
        if(get_cell_data(in, current_cell_index, &current_cell_data) != 0)
            return 1;

        // Process cell located Westwise to current
        if((current_cell_data & WEST) == WEST && get_cell_data(in, current_cell_index - 1, &child_cell_data) == 0) {
            if((child_cell_data & VISITED_STATE_VALUE) != VISITED_STATE_VALUE) {
                set_cell_parent(in, current_cell_index - 1, PARENT_EAST);
                if((child_cell_data >> 6 & 1) == 1)
                    break;
                menqueue(&queue, current_cell_index - 1, &memory_queue);
            }
        }
        // Process cell located Southwise to current
        if((current_cell_data & SOUTH) == SOUTH && get_cell_data(in, current_cell_index + m->width, &child_cell_data) == 0) {
            if((child_cell_data & VISITED_STATE_VALUE) != VISITED_STATE_VALUE) {
                set_cell_parent(in, current_cell_index + m->width, PARENT_NORTH);
                if((child_cell_data >> 6 & 1) == 1)
                    break;
                menqueue(&queue, current_cell_index + m->width, &memory_queue);
            }
        }
        // Process cell located Eastwise to current
        if((current_cell_data & EAST) == EAST && get_cell_data(in, current_cell_index + 1, &child_cell_data) == 0) {
            if((child_cell_data & VISITED_STATE_VALUE) != VISITED_STATE_VALUE) {
                set_cell_parent(in, current_cell_index + 1, PARENT_WEST);
                if((child_cell_data >> 6 & 1) == 1)
                    break;
                menqueue(&queue, current_cell_index + 1, &memory_queue);
            }
        }
        // Process cell located Northwise to current
        if((current_cell_data & NORTH) == NORTH && get_cell_data(in, current_cell_index - m->width, &child_cell_data) == 0) {
            if((child_cell_data & VISITED_STATE_VALUE) != VISITED_STATE_VALUE) {
                set_cell_parent(in, current_cell_index - m->width, PARENT_SOUTH);
                if((child_cell_data >> 6 & 1) == 1)
                    break;
                menqueue(&queue, current_cell_index - m->width, &memory_queue);
            }
        }
    }
    // Free queue if any cells left
    while((current_cell_index = mdequeue(&queue, &memory_queue)) != -1) {}
    while((current_cell_index = free_mqueue(&memory_queue)) != -1) {}
    return 0;
}