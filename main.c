#include "cells.h"
#include <stdio.h>


//Board
struct Board {
    int** array;
    int** previous;
    int width;
    int height;
    int generations;
    int current_generation;
};

void board_constructor(struct Board* board, char* filename) {
    get_dimensions(filename, &board->width, &board->height);
    get_generations(filename, &board->generations);
    board->previous = input_to_2d_array(filename, board->width, board->height);
    board->array = input_to_2d_array(filename, board->width, board->height);
    board->current_generation = 1;
}

void board_deconstructor(struct Board* board) {
    free_2d_array(board->array, board->width, board->height);
    free_2d_array(board->previous, board->width, board->height);
}

int board_check_cell(const struct Board* board, int cell_x, int cell_y) {
    int alive = 0;
    int neighbors = 0;
    for (int x=cell_x-1; x<=cell_x+1; x++) {
        for (int y=cell_y-1; y<=cell_y+1; y++) {
            if (x == cell_x && y == cell_y) continue;
            if (x < 0 || y < 0) continue;
            if (x >= board->width || y >= board->height ) continue;

            if (board->previous[x][y] == 1) {
                alive++;
            } else if (board->previous[x][y] == 0) {
                neighbors++;
            } else {
                return -1;
            }
        }
    }
    return alive;
}

int board_update(struct Board* board) {
    int alive = 0;
    int is_alive = 0;
    for (int x=0; x<board->width; x++) { 
        for (int y=0; y<board->height; y++) {
            alive = board_check_cell(board, x, y);
            is_alive = (board->previous[x][y] == 1);
            if (is_alive) {
                if (alive < 2) {
                    board->array[x][y] = 0;
                } else if (alive == 2 || alive == 3) {
                    board->array[x][y] = 1;
                } else if (alive > 3) {
                    board->array[x][y] = 0;
                } else {
                    return -1;
                }
            } else {
                if (alive == 3) {
                    board->array[x][y] = 1;
                }
            }
        }
    }

    for (int x=0; x<board->width; x++) { 
        for (int y=0; y<board->height; y++) {
            board->previous[x][y] = board->array[x][y];
        }
    }
    board->current_generation++;
    return 0;
}

void board_print(const struct Board* board) {
    print_2d_array(board->array, board->width, board->height);
    print_line(board->current_generation, board->generations);
}
//End Board

//Utils
void print_line(int generation, int total) {
    printf("----------------------------------: generation %i/%i\n", generation, total);
}

//Tests
int test_check_alive() {
    char* filename = "input.txt";
    struct Board board;
    board_constructor(&board, filename);

    if (board_check_cell(&board, 3, 1) != 2) {
        return -1;
    }
    if (board_check_cell(&board, 0, 0) != 1) {
        return -1;
    }
    if (board_check_cell(&board, 2, 2) != 3) {
        return -1;
    }
    return 0;
}

int tests_update() {
    char* filename;
    struct Board board1, board3;
    board_constructor(&board1, "test1.txt");
    board_constructor(&board3, "test3.txt");
    
    // print_2d_array(board1.array, board1.width, board1.height);
    // print_line();
    // board_update(&board1);
    // print_2d_array(board1.array, board1.width, board1.height);
    // print_line();

    // for (int x=0; x<3; x++) {
    //     print_2d_array(board3.array, board3.width, board3.height);
    //     print_line();
    //     board_update(&board3);
    // }
    return 0;
}
//End tests

int main(int argc, char const *argv[])
{      
    if (test_check_alive() != 0) {
        printf("ERROR:function check_alive failed\n");
        return -1;
    }
    if (tests_update() != 0) {
        printf("ERROR:function update failed\n");
        return -1;
    }

    char* filename;
    struct Board board;
    filename = get_input_file_name(argc, argv);
    board_constructor(&board, filename);

    for (int i=0; i<board.generations; i++) {
        board_print(&board);
        board_update(&board);
        sleep_250_ms();
    }

    board_deconstructor(&board);
    
    return 0;
}
