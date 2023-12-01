/*
maze.cpp
*/

#include <iostream>

#include "mazeio.h"
#include "queue.h"

// Prototype for maze_search, which you will fill in below.
int maze_search(char **, int, int);

// Add other prototypes here for any functions you wish to use

// main function to read, solve maze, and print result
int main(int argc, char *argv[]) {
    int rows, cols, result;
    char **mymaze = NULL;
    const char *invalid_char_message = "Error, invalid character.";
    const char *invalid_maze_message = "Invalid maze.";
    const char *no_path_message = "No path could be found!";

    if (argc < 2) {
        std::cout << "Please provide a maze input file"
                  << "\n";
        return 1;
    }

    mymaze = read_maze(argv[1], &rows, &cols);
    if (mymaze == NULL) {
        std::cout << invalid_char_message << "\n";
        for (int i = 0; i < rows; ++i) delete[] mymaze[i];
        delete[] mymaze;
        return 0;
    }

    result = maze_search(mymaze, rows, cols);

    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.

    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    if (result == -1) std::cout << invalid_maze_message << "\n";
    if (result == 0) std::cout << no_path_message << "\n";
    if (result == 1) print_maze(mymaze, rows, cols);

    //================================
    // ADD CODE BELOW
    // to delete all memory that read_maze allocated: CHECKPOINT 2
    for (int i = 0; i < rows; ++i) delete[] mymaze[i];
    delete[] mymaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char **maze, int rows, int cols) {
    // *** You complete **** CHECKPOINT 4
    Location start = {-1, -1};
    bool foundStart = false;
    bool foundFin = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'S') {
                if (foundStart == true) return -1;
                start = {i, j};
                foundStart = true;
            }
            if (maze[i][j] == 'F') {
                if (foundFin == true) return -1;
                foundFin = true;
            }
        }
    }
    if (!foundStart || !foundFin) return -1;
    bool **explored = new bool *[rows];
    for (int i = 0; i < rows; ++i) {
        explored[i] = new bool[cols];
        for (int j = 0; j < cols; ++j) {
            explored[i][j] = false;
            if (maze[i][j] == 'S')
                explored[i][j] = true;
        }
    }
    Location **pred = new Location *[rows];
    for (int i = 0; i < rows; ++i) {
        pred[i] = new Location[cols];
        for (int j = 0; j < cols; ++j) {
            Location loc{0, 0};
            pred[i][j] = loc;
        }
    }
    Queue q(rows * cols);
    // find shortest path
    explored[start.row][start.col] = true;
    q.add_to_back(start);
    Location curr;
    bool pathFound = false;
    while (!q.is_empty()) {
        curr = q.remove_from_front();
        if (maze[curr.row][curr.col] == 'F') {
            pathFound = true;
            break;
        }
        // North
        if (curr.row - 1 >= 0 && maze[curr.row - 1][curr.col] != '#' &&
            !explored[curr.row - 1][curr.col]) {
            Location loc = {curr.row - 1, curr.col};
            explored[curr.row - 1][curr.col] = true;
            q.add_to_back(loc);
            pred[curr.row - 1][curr.col] = curr;
        }
        // West
        if (curr.col - 1 >= 0 && maze[curr.row][curr.col - 1] != '#' &&
            !explored[curr.row][curr.col - 1]) {
            Location loc = {curr.row, curr.col - 1};
            explored[curr.row][curr.col - 1] = true;
            q.add_to_back(loc);
            pred[curr.row][curr.col - 1] = curr;
        }
        // South
        if (curr.row + 1 < rows && maze[curr.row + 1][curr.col] != '#' &&
            !explored[curr.row + 1][curr.col]) {
            Location loc = {curr.row + 1, curr.col};
            explored[curr.row + 1][curr.col] = true;
            q.add_to_back(loc);
            pred[curr.row + 1][curr.col] = curr;
        }
        // East
        if (curr.col + 1 < cols && maze[curr.row][curr.col + 1] != '#' &&
            !explored[curr.row][curr.col + 1]) {
            Location loc = {curr.row, curr.col + 1};
            explored[curr.row][curr.col + 1] = true;
            q.add_to_back(loc);
            pred[curr.row][curr.col + 1] = curr;
        }
    }
    // walk pred array and update maze
    while (true) {
        Location p = pred[curr.row][curr.col];
        if (maze[p.row][p.col] == 'S') break;
        maze[p.row][p.col] = '*';
        curr = p;
    }
    for (int i = 0; i < rows; ++i) {
        delete[] explored[i];
        delete[] pred[i];
    }
    delete[] explored;
    delete[] pred;
    if (pathFound)
        return 1;
    return 0;
}
