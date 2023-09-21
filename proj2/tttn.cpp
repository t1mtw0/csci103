// NxN tic-tac-toes
#include <cstdlib>
#include <iostream>
#include <unordered_map>

std::unordered_map<char, int> playerToInt = {{'X', 1}, {'O', 2}};
std::unordered_map<char, int> intToPlayer = {{1, 'X'}, {2, 'O'}};

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);

/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);

/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * @brief Get the Ai Choice for the current player and update grid object
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If an error occurred or a choice was unable to be made
 * @return false If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**
 * @brief Picks a random location for the current player and update grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If no viable location to be played
 * @return false If a play was successfully made
 */
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player);

/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c) {
    return grid[dim * r + c];
}

int idxToRow(int idx, int dim) { return idx / dim; }

int idxToCol(int idx, int dim) { return idx % dim; }

void printTTT(char grid[], int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            std::cout << " ";
            std::cout << getEntryAtRC(grid, dim, i, j);
            std::cout << " ";
            if (j != dim - 1)
                std::cout << "|";
        }
        std::cout << "\n";
        if (i == dim - 1)
            break;
        for (int k = 0; k < dim * 3 + (dim - 1); ++k) {
            std::cout << "-";
        }
        std::cout << "\n";
    }
}

int checkForWinner(char grid[], int dim) {
    char winner;
    // diagonals
    bool diag1 = true;
    winner = getEntryAtRC(grid, dim, 0, 0);
    for (int i = 1; i < dim; ++i) {
        if (winner == '?' || getEntryAtRC(grid, dim, i, i) == '?') {
            diag1 = false;
            break;
        }
        if (getEntryAtRC(grid, dim, i, i) != winner) {
            diag1 = false;
            break;
        }
    }
    if (diag1)
        return playerToInt[winner];

    bool diag2 = true;
    winner = getEntryAtRC(grid, dim, 0, dim - 1);
    for (int i = 1; i < dim; ++i) {
        if (winner == '?' || getEntryAtRC(grid, dim, i, dim - i - 1) == '?') {
            diag2 = false;
            break;
        }
        if (getEntryAtRC(grid, dim, i, dim - i - 1) != winner) {
            diag2 = false;
            break;
        }
    }
    if (diag2)
        return playerToInt[winner];

    // rows
    bool row = true;
    for (int i = 0; i < dim; ++i) {
        winner = getEntryAtRC(grid, dim, i, 0);
        for (int j = 1; j < dim; ++j) {
            if (winner == '?' || getEntryAtRC(grid, dim, i, j) == '?') {
                row = false;
                break;
            }
            if (getEntryAtRC(grid, dim, i, j) != winner)
                row = false;
        }
        if (row)
            return playerToInt[winner];
        row = true;
    }

    // columns
    bool column = true;
    for (int i = 0; i < dim; ++i) {
        winner = getEntryAtRC(grid, dim, 0, i);
        for (int j = 1; j < dim; ++j) {
            if (winner == '?' || getEntryAtRC(grid, dim, j, i) == '?') {
                column = false;
                break;
            }
            if (getEntryAtRC(grid, dim, j, i) != winner)
                column = false;
        }
        if (column)
            return playerToInt[winner];
        column = true;
    }

    return 0;
}

bool checkForDraw(char grid[], int dim) {
    // diagonals
    bool fromDiag1 = true;
    char current1 = getEntryAtRC(grid, dim, 0, 0);
    for (int i = 1; i < dim; ++i) {
        if (current1 == '?') {
            if (getEntryAtRC(grid, dim, i, i) != '?')
                current1 = getEntryAtRC(grid, dim, i, i);
            continue;
        } else {
            if (getEntryAtRC(grid, dim, i, i) != '?') {
                if (getEntryAtRC(grid, dim, i, i) != current1) {
                    fromDiag1 = false;
                    break;
                }
            }
        }
    }
    bool fromDiag2 = true;
    char current2 = getEntryAtRC(grid, dim, 0, dim - 1);
    for (int i = 1; i < dim; ++i) {
        if (current2 == '?') {
            if (getEntryAtRC(grid, dim, i, dim - i - 1) != '?')
                current2 = getEntryAtRC(grid, dim, i, dim - i - 1);
            continue;
        } else {
            if (getEntryAtRC(grid, dim, i, dim - i - 1) != '?') {
                if (getEntryAtRC(grid, dim, i, dim - i - 1) != current2) {
                    fromDiag2 = false;
                    break;
                }
            }
        }
    }

    // rows
    bool fromRow = true;
    for (int i = 0; i < dim; ++i) {
        fromRow = true;
        char current = getEntryAtRC(grid, dim, i, 0);
        for (int j = 1; j < dim; ++j) {
            if (current == '?') {
                if (getEntryAtRC(grid, dim, i, j) != '?')
                    current = getEntryAtRC(grid, dim, i, j);
            } else {
                if (getEntryAtRC(grid, dim, i, j) != '?') {
                    if (getEntryAtRC(grid, dim, i, j) != current)
                        fromRow = false;
                }
            }
        }
        if (fromRow)
            break;
    }
    // columns
    bool fromCol = true;
    for (int i = 0; i < dim; ++i) {
        fromCol = true;
        char current = getEntryAtRC(grid, dim, 0, i);
        for (int j = 1; j < dim; ++j) {
            if (current == '?') {
                if (getEntryAtRC(grid, dim, j, i) != '?')
                    current = getEntryAtRC(grid, dim, j, i);
            } else {
                if (getEntryAtRC(grid, dim, j, i) != '?') {
                    if (getEntryAtRC(grid, dim, j, i) != current)
                        fromCol = false;
                }
            }
        }
        if (fromCol)
            break;
    }

    if (!fromDiag1 && !fromDiag2 && !fromRow && !fromCol)
        return true;

    return false;
}

/**
 * minimax recursiely searches through all the possible
 * moves, alternating between the maximizer and the minimizer.
 * minimax returns either the maximum score or the minimum score
 * for the current player.
 */
int minimax(char grid[], int dim, char player, int depth, bool maximizing) {
    if (depth == dim) return 0;
    int winner = checkForWinner(grid, dim);
    if (winner != 0) {
        if (playerToInt[player] == winner) {
            // we remove the depth from score to account for winning later in the game
            // versus winning earlier
            return 11 - depth;
        } else {
            return -11;
        }
    }
    if (checkForDraw(grid, dim))
        return 0;
    bool filled = true;
    for (int i = 0; i < dim * dim; ++i) {
        if (grid[i] == '?')
            filled = false;
    }
    if (filled)
        return 0;

    if (maximizing) {
        int maxScore = INT32_MIN;
        for (int i = 0; i < dim * dim; ++i) {
            if (grid[i] == 'X' || grid[i] == 'O')
                continue;
            grid[i] = player;
            int score = minimax(grid, dim, player, depth + 1, false);
            if (score > maxScore)
                maxScore = score;
            grid[i] = '?';
        }
        return maxScore;
    } else {
        int minScore = INT32_MAX;
        for (int i = 0; i < dim * dim; ++i) {
            if (grid[i] == 'X' || grid[i] == 'O')
                continue;
            grid[i] = player == 'X' ? 'O' : 'X';
            int score = minimax(grid, dim, player, depth + 1, true);
            if (score < minScore)
                minScore = score;
            grid[i] = '?';
        }
        return minScore;
    }
    return -1;
}

/**
 * Gets a choice based on the minimax algorithm.
 * Searches through each of the possible next moves for
 * the current player and calls minimax for each move.
 * The AI chooses the move that would maximize its own score.
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player) {
    char g[dim * dim];
    for (int i = 0; i < dim * dim; ++i) {
        g[i] = grid[i];
    }
    int bestMove = -1;
    int maxScore = INT32_MIN;
    for (int i = 0; i < dim * dim; ++i) {
        if (g[i] == 'X' || g[i] == 'O')
            continue;
        g[i] = player;
        int score = minimax(g, dim, player, 0, false);
        if (score == -1)
            break;
        if (bestMove == -1 || score >= maxScore) {
            bestMove = i;
            maxScore = score;
        }
        g[i] = '?';
    }
    if (bestMove == -1)
        return true;
    grid[bestMove] = player;
    return false;
}

// Complete...Do not alter
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player) {
    int start = rand() % (dim * dim);
    // look for an open location to play based on random starting location.
    // If that location is occupied, move on sequentially until wrapping and
    // trying all locations
    for (int i = 0; i < dim * dim; i++) {
        int loc = (start + i) % (dim * dim);
        if (grid[loc] == '?') {
            grid[loc] = player;
            return false;
        }
    }
    // No viable location
    return true;
}

/**********************************************************
 *  Complete the indicated parts of main(), below.
 **********************************************************/
int main() {
    // This array holds the actual board/grid of X and Os. It is sized
    // for the biggest possible case (11x11), but you should only
    // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
    char tttdata[121];

    // dim stands for dimension and is the side length of the
    // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
    int dim;
    int seed;
    // Get the dimension from the user
    std::cin >> dim >> seed;
    srand(seed);

    int dim_sq = dim * dim;

    for (int i = 0; i < dim_sq; i++) {
        tttdata[i] = '?';
    }

    // Print one of these messages when the game is over
    // and before you quit
    const char xwins_msg[] = "X player wins!";
    const char owins_msg[] = "O player wins!";
    const char draw_msg[] = "Draw...game over!";

    bool done = false;
    char player = 'X';
    // Show the initial starting board
    printTTT(tttdata, dim);

    while (!done) {
        //**********************************************************
        // Get the current player's input (i.e. the location they want to
        // choose to place their mark [X or O]) or choice of AI or Random
        // location and update the tttdata array.
        // Be sure to follow the requirements defined in the guide/writeup
        // for quitting immediately if the user input is out-of-bounds
        // (i.e. not in the range 0 to dim_sq-1 nor -1 nor -2) as well as
        // continuing to prompt for an input if the user chooses locations
        // that have already been chosen (already marked with an X or O).
        //**********************************************************

        // Add your code here for getting input
        std::cout << "Player " << player << " enter your square choice [0-"
                  << dim_sq - 1 << "], -1 (AI), or -2 (Random):\n";
        int move;
        while (true) {
            if (!(std::cin >> move))
                exit(1);
            if (move == -2) {
                getRandChoiceAndUpdateGrid(tttdata, dim, player);
                break;
            } else if (move == -1) {
                getAiChoiceAndUpdateGrid(tttdata, dim, player);
                break;
            }
            if (move < 0 || move > dim_sq - 1)
                exit(0);
            char entryAt = tttdata[move];
            if (entryAt == 'O' || entryAt == 'X') {
                continue;
            } else {
                tttdata[move] = player;
                break;
            }
        }
        // Show the updated board if the user eventually chose a valid location
        // (i.e. you should have quit the loop and program by now without any
        //  other output message if the user chosen an out-of-bounds input).
        printTTT(tttdata, dim);

        //**********************************************************
        // Complete the body of the while loop to process the input that was
        // just
        //  received to check for a winner or draw and update other status, as
        //  needed.
        //
        // To match our automated checkers' expected output, you must output
        // one of the messages defined above using *one* of the cout commands
        // (under the appropriate condition) below:
        //   cout << xwins_msg << endl;  OR
        //   cout << owins_msg << endl;  OR
        //   cout << draw_msg << endl;
        //
        // Note: Our automated checkers will examine a specific number of lines
        //  at the end of the program's output and expect to see the updated
        //  board and game status message.  You may certainly add some debug
        //  print statements during development but they will need to be removed
        //  to pass the automated checks.
        //**********************************************************
        if (checkForWinner(tttdata, dim) != 0) {
            if (player == 'X') {
                std::cout << xwins_msg << "\n";
            } else {
                std::cout << owins_msg << "\n";
            }
            done = true;
        }

        if (checkForDraw(tttdata, dim)) {
            std::cout << draw_msg << "\n";
            done = true;
        }

        if (player == 'X') {
            player = 'O';
        } else {
            player = 'X';
        }
    } // end while
    return 0;
}
