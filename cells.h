//
// Created by Scott Fennell on 5/25/18.
//

#ifndef CELLS_H
#define CELLS_H


/* takes argc and argv from main() and returns a pointer to the first command line argument.
 * if there was no command line argument, the default return value is "input.txt" */
char *get_input_file_name(int argc, char **argv);

/* gets the dimensions from the input file and puts them in the location pointed to by 'width' and 'height' */
void get_dimensions(char *input_filename, unsigned int *width, unsigned int *height);

/* puts the number of generations from the input file into the location pointed to by 'generations' */
void get_generations(char *input_filename, unsigned int *generations);

/* allocates a 2d array and fills it from the input file.
 * elements are accessed by <array_name>[x][y] where x < width, y < height (zero-indexed) */
int **input_to_2d_array(char *input_filename, unsigned int width, unsigned int height);

/* allocates an empty 2d integer array.
 * elements are accessed by <array_name>[x][y] where x < width, y < height (zero-indexed) */
int **allocate_2d_array(unsigned int width, unsigned int height);

/* deallocates arrays that were allocated from 'input_to_2d_array' and 'allocate_2d_array'. */
void free_2d_array(int **array, unsigned int width, unsigned int height);

/* prints a 2d array to the console */
void print_2d_array(int **array, unsigned int width, unsigned int height);

/*sleeps the process for 250ms. */
void sleep_250_ms(void);

#endif //CELLS_H


