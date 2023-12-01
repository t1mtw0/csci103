#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
const int NCOL = 8;
const int NROW = 6;

const char *wordBank[] = {
    "cat",   "dog",  "bear",   "wolf",   "pig",    "bird",   "fish",   "duck",
    "apple", "pear", "orange", "berry",  "grape",  "banana", "lychee", "mango",
    "blue",  "red",  "green",  "yellow", "purple", "pink",   "black",  "white"};

// Prototypes
void scramble(int vals[], int len);

void scramble(int vals[], int len) {
    // Fisher-Yates shuffle algorithm
    for (int i = len - 1; i >= 0; i--) {
        // random Value being chosen
        int r = rand() % (i + 1);
        // if(i==0) { cout << "Random i=0: " << r << endl; }
        int temp = vals[i];
        vals[i] = vals[r];
        vals[r] = temp;
    }
}

/*
   GameBoard class here
   */
class GameBoard {
    /*
       what should our member functions be?
       */

  public:
    GameBoard(int r, int c) {
        nr = r;
        nc = c;
        initGameBoard();
    }

    void printGameBoard() {
        for (int r = 0; r < nr; r++) {
            for (int c = 0; c < nc; c++) {
                if (guessed[r][c]) {
                    cout << right << setw(8) << board[r][c];
                } else {
                    cout << right << setw(8) << "<---->";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    bool checkMatch(int r1, int c1, int r2, int c2) {
        // if choice is out of bounds, turn is over
        if (r1 < 0 || r1 >= nr) {
            return false;
        }
        if (c1 < 0 || c1 >= nc) {
            return false;
        }
        if (r2 < 0 || r2 >= nr) {
            return false;
        }
        if (c2 < 0 || c2 >= nc) {
            return false;
        }
        // if a player chooses an already guessed location,
        // their turn is over
        if (guessed[r1][c1] || guessed[r2][c2]) {
            return false;
        }
        // remember `string`s can be compared with ==
        if (board[r1][c1] == board[r2][c2]) {
            cout << "Match!" << endl;
            guessed[r1][c1] = true;
            guessed[r2][c2] = true;
            return true;
        } else {
            cout << "No match!" << endl << endl;
            cout << "At " << r1 << "," << c1 << ": " << board[r1][c1] << endl;
            cout << "At " << r2 << "," << c2 << ": " << board[r2][c2] << endl;
            return false;
        }
    }

    bool isGameOver() {
        for (int r = 0; r < nr; r++) {
            for (int c = 0; c < nc; c++) {
                if (guessed[r][c] == false) {
                    return false;
                }
            }
        }
        return true;
    }
    /*
       what should our data members be?
       */
  private:
    void initGameBoard() {
        // At most we support NROW*NCOL/2 PAIR locations
        int wordIndexes[NROW * NCOL];
        for (int i = 0; i < nr * nc / 2; i++) {
            wordIndexes[2 * i] = i;
            wordIndexes[2 * i + 1] = i;
        }

        // Scramble the indexes which we will then convert
        //  to the strings to show on the game board
        scramble(wordIndexes, nr * nc);

        // Now put the selected words into the game board
        for (int r = 0; r < nr; r++) {
            for (int c = 0; c < nc; c++) {
                int index1D = r * nc + c;
                // board is an array of `string` type which
                // can use assignment `=` to make a copy of the
                // C-string we choose from the wordBank
                board[r][c] = wordBank[wordIndexes[index1D]];
                guessed[r][c] = false;
            }
        }
    }

    string board[NROW][NCOL];
    bool guessed[NROW][NCOL];
    int nr, nc;
};

int main() {
    srand(time(0));

    // *** User input **************************************

    // Ask user for the board dimension they really want
    int nr, nc, np;
    cout << "Enter the two dimensions for the board: " << endl;
    cin >> nr >> nc;

    // Error checking
    if (nr >= NROW || nc >= NCOL || (nr * nc) % 2 == 1) {
        cout << "Bad dimensions...exiting" << endl;
        return 1;
    }

    cout << "Enter the number of players: " << endl;
    cin >> np;

    int *playerScores = new int[np];
    string *playerNames = new string[np];
    for (int i = 0; i < np; i++) {
        cout << "Enter player " << i + 1 << "'s name: " << endl;
        cin >> playerNames[i];
        playerScores[i] = 0;
    }

    /*
            Copy-paste main code from memory-func.cpp
            Edit things to use GameBoard.
    1. Initialize GameBoard
    2. Replace functions from memory-func.cpp to use
        the approriate member functions of GameBoard
        (if they translate to member functions)
    */
    GameBoard board{nr, nc};
    bool done = false;
    int currPlayer = 0;
    int maxPlayer = 0;
    while (!done) {
        // take 1 turn in each iteration
        board.printGameBoard();
        int r1, c1, r2, c2;
        cout << playerNames[currPlayer]
             << " enter R1 C1 then R2 C2 indexes: " << endl;
        cin >> r1;
        // Quit if negative first number
        if (r1 < 0) {
            break;
        }
        // Get the remaining inputs
        cin >> c1 >> r2 >> c2;
        bool status = board.checkMatch(r1, c1, r2, c2);
        if (status) {
            // Update scores and which player has the most matches
            playerScores[currPlayer]++;
            if (playerScores[currPlayer] > playerScores[maxPlayer]) {
                maxPlayer = currPlayer;
            }
            // Make a match, go again.  Don't update player.
        } else {
            // use mod to start back at player 1
            // after we give all players a turn
            currPlayer = (currPlayer + 1) % np;
        }
        cout << endl;
        cout << left << setw(12) << "Name" << setw(8) << "Score" << endl;
        for (int i = 0; i < np; i++) {
            cout << left << setw(12) << playerNames[i] << setw(8)
                 << playerScores[i] << endl;
        }
        cout << endl;
        done = board.isGameOver();
    }
    board.printGameBoard();
    cout << "Game over!" << endl;
    cout << "Winner: " << playerNames[maxPlayer] << endl;

    delete[] playerScores;
    delete[] playerNames;
    return 0;
}
