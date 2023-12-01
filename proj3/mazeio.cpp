/*
mazeio.cpp
*/

#include "mazeio.h"
#include <cstring>
#include <fstream>
#include <iostream>

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char **read_maze(char *filename, int *rows, int *cols) {
    std::ifstream file{filename};
    if (file.fail())
        return NULL;
    int r, c;
    file >> r >> c;
    *rows = r;
    *cols = c;
    char **output = new char *[r];
    char *buf = new char[c + 1];
    for (int i = 0; i < r; ++i) {
        output[i] = new char[c];
        file >> buf;
        for (int j = 0; j < c; ++j) {
            if (buf[j] != '.' && buf[j] != '#' && buf[j] != 'S' &&
                buf[j] != 'F') {
                delete[] buf;
                for (int k = 0; k < r; ++k) delete[] output[k];
                delete[] output;
                return NULL;
            }
        }
        strncpy(output[i], buf, c);
    }
    delete[] buf;
    file.close();
    return output;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char **maze, int rows, int cols) {
    std::cout << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << maze[i][j];
        }
        std::cout << "\n";
    }
}
