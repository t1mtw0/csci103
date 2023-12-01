// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, and dynamic allocation, etc.
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
// TODO 1: Include needed headers for filestreams
#include <fstream>
// Scramble the letters of this string randomly
void permute(char items[], int len);

// Seed the random number generator (RNG) with user-provided seed or
//  current time.
// @param [in] seedarg - NULL, if no seed was provided on the command line
//                       or pointer to the C-string containing the seed.
void seedRNG(char *seedarg);

// TODO 2: Delete the integer and array below to no longer be a global,
// but instead declare them in main() and set the array elements
// to point at the words read in from the input file

// TODO 3a: Modify the signature of main to allow for command line args.
int main(int argc, char *argv[]) {
    // TODO 3b: Add argc check as described in the writeup and
    //          call seedRNG() with appropriate argument
    if (argc != 3 && argc != 2) exit(1);
    if (argc == 2) seedRNG(NULL);
    if (argc == 3) seedRNG(argv[2]);
    // TODO 4-9: Add code to declare the wordBank array and
    //       read in each word from the file specified by argv[1]
    //       and store them appropriately.  If the file cannot
    //       be opened, return 2.
    std::ifstream file{argv[1]};
    if (file.fail()) {
        std::cerr << "Could not open file\n";
        exit(2);
    }
    int numWords;
    file >> numWords;
    char **wordBank = new char*[numWords];
    char charBuf[41];
    for (int i = 0; i < numWords; ++i) {
        file >> charBuf;
        int wordLen = strlen(charBuf);
        wordBank[i] = new char[wordLen];
        strncpy(wordBank[i], charBuf, wordLen);
    }
    file.close();
    // Complete: More variables for later
    char guess[80] = ""; // blank array for user input
    bool wordGuessed = false;
    int numTurns = 10;

    // Complete: Pick a random word from the wordBank
    int target = rand() % numWords;
    int targetLen = strlen(wordBank[target]);
    std::cout << "Sol: " << wordBank[target] << "\n";
    char *word = NULL; // pointer to target word

    // TODO 10: Change word to point at a dynamically-allocated copy
    // of the target word that you create and then
    // scramble the letters of the array word points to by
    // calling permute() on it
    word = new char[targetLen];
    strcpy(word, wordBank[target]);
    permute(word, targetLen);
    // An individual game continues until '!' is entered, a word
    //  is guessed correctly or 10 turns have elapsed
    while (guess[0] != '!' && !wordGuessed && numTurns > 0) {
        std::cout << "Scrambled word: " << word << "\n";
        std::cout << "What do you guess the original word is? " << "\n";
        std::cin >> guess;
        // TODO 11: Add code to check if the guess is equal to the chosen word.
        // Update wordGuessed to be true if they are equal, and false otherwise.
        if (strcmp(wordBank[target], guess) == 0) {
            wordGuessed = true;
        } else {
            wordGuessed = false;
        }
        numTurns--; // Every guess counts as a turn
    }
    if (guess[0] == '!') {
        std::cout << "Quit!" << "\n";
    } else if (wordGuessed) {
        std::cout << "Win! " << numTurns << " guesses to spare." << "\n";
    } else {
        std::cout << "Lose! " << wordBank[target] << "\n";
    }

    // TODO 12: Add any necessary cleanup code to avoid memory leaks/errors
    delete[] word;

    return 0;
}

// Scramble the letters. Uses "Knuth shuffle" algorithm.
void permute(char items[], int len) {
    for (int i = len - 1; i > 0; --i) {
        int r = rand() % i;
        char temp = items[i];
        items[i] = items[r];
        items[r] = temp;
    }
}

// Seed the RNG
void seedRNG(char *seedarg) {
    if (NULL == seedarg) {
        srand(time(0)); // use the time to get randomly chosen words each run
    } else {
        srand(atoi(seedarg)); // use the command line argument as the seed
    }
}
