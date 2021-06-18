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

//Modified to fix error where the last column was not being put into the array
int **input_to_2d_array(char *input_filename, unsigned int width,
                        unsigned int height) {
    FILE *input = fopen(input_filename, "r");
    fscanf(input, "%*d\n%*d\n%*d\n");
    int **array = allocate_2d_array(width, height);
    int next;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width -1; x++) {
            fscanf(input, "%d ", &next);
            array[x][y] = next;
        }
        fscanf(input, "%d\n", &next);
        array[width-1][y] = next;
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

//Modified to to reduce repeated code.
void print_2d_array(int **array, unsigned int width, unsigned int height) {
    print_2d_array_to_fp(array, width, height, stdout, 1);
}

void print_2d_array_to_fp(int **array, unsigned int width, unsigned int height, FILE* fp, int graphic) {
    char zero, one;
    if (graphic) {
        zero = '.';
        one = '@';
    } else {
        zero = '0';
        one = '1';
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (array[x][y]) {
                fputc(one, fp);
            } else {
                fputc(zero, fp);
            }
            fputc(' ', fp);
        }
        fputc('\n', fp);
    }
}

const struct timespec quarter_sec = {0, 250000000};

void sleep_250_ms(void) {
    nanosleep(&quarter_sec, NULL);
}

//Modified to accept const argv
char *get_input_file_name(int argc, const char **argv) {
    if (argc == 2) {
        return (char*)argv[1];
    } else {
        return "input.txt";
    }
}

void print_line(int generation, int total) {
    printf("----------------------------------: generation %i/%i\n", generation, total);
}