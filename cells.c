//
// Created by Scott Fennell on 5/25/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cells.h"

void get_dimensions(char *input_filename, unsigned int *width, unsigned int *height) {
    FILE *input;
    input = fopen(input_filename, "r");
    fscanf(input, "%d\n%d\n", width, height);
    fclose(input);
}

void get_generations(char *input_filename, unsigned int *generations) {
    FILE *input = fopen(input_filename, "r");
    fscanf(input, "%*d\n%*d\n%d", generations);
    fclose(input);
}

int **input_to_2d_array(char *input_filename, unsigned int width,
                        unsigned int height) {
    FILE *input = fopen(input_filename, "r");
    fscanf(input, "%*d\n%*d\n%*d\n");
    int **array = allocate_2d_array(width, height);
    int next;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width - 1; x++) {
            fscanf(input, "%d ", &next);
            array[x][y] = next;
        }
        fscanf(input, "%d\n", &next);
    }
    fclose(input);
    return array;
}

int **allocate_2d_array(unsigned int width, unsigned int height) {
    int **array = calloc(width, sizeof(int *));
    for (int i = 0; i < width; i++) {
        array[i] = calloc(height, sizeof(int));
    }
    return array;
}

void free_2d_array(int **array, unsigned int width, unsigned int height) {
    for (int i = 0; i < width; i++) {
        free(array[i]);
    }
    free(array);
}

void print_2d_array(int **array, unsigned int width, unsigned int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (array[x][y]) {
                putchar('@');
            } else {
                putchar('.');
            }
            putchar(' ');
        }
        putchar('\n');
    }
}

const struct timespec quarter_sec = {0, 250000000};

void sleep_250_ms(void) {
    nanosleep(&quarter_sec, NULL);
}

char *get_input_file_name(int argc, char **argv) {
    if (argc == 2) {
        return argv[1];
    } else {
        return "input.txt";
    }
}