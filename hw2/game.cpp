// game.cpp
// Word guessing game illustrates C-strings, some C-string library functions,
//  functions and array passing.
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

// Prototype. we'll define this below.
int processGuess(char word[], const char targetWord[], char guess);

// Define an array of strings (since a string is just a char array)
//  and since string literals (e.g. "hi") evaluate to the starting address
//  of those characters, we really want an array of char *'s
const char *wordBank[] = {"computer", "president", "trojan",   "program",
                          "coffee",   "library",   "football", "popcorn",
                          "science",  "engineer"};

const int numWords = 10;

int main(int argc, char *argv[]) {
    //------------- Do not modify this code --------------
    if (argc < 2) {
        srand(time(0)); // use the time to get randomly chosen words each run
    } else {
        srand(atoi(argv[1])); // use the command line argument as the seed
    }

    // Pick a random word from the wordBank
    const char *targetWord = wordBank[rand() % numWords];

    int numTurns = 10; // variable to track how many turns remain

    char word[80]; // a blank array to use to build up the answer
                   // It should be initialized with *'s and then
                   //  change them to the actual letters when the
                   //  user guesses the letter

    // More initialization code as needed
    for (int i = 0; i < (int)strlen(targetWord); ++i) {
        strcpy(&word[i], "*");
    }
    // The game should continue until a word
    //  is guessed correctly, a '!' is entered,
    //  or 10 turns have elapsed without the word being guessed

    // Print out end of game status
    char guess;
    bool loss = false;
    bool win = false;
    while (!win && !loss) {
        std::cout << numTurns << " guesses remain: " << word << "\n";
        std::cout << "Enter a letter: \n";
        std::cin >> guess;
        if (!(guess >= 'a' && guess <= 'z')) {
            break;
        }
        if (processGuess(word, targetWord, guess) == 0) {
            if (numTurns-- == 1) {
                loss = true;
            }
        } else if (strcmp(word, targetWord) == 0) {
            win = true;
        }
    }
    if (win) {
        std::cout << "Win! " << numTurns << " guesses to spare.\n";
    } else if (loss) {
        std::cout << "Lose! " << word << "\n";
    } else {
        std::cout << "Quit!";
    }
    return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char word[], const char targetWord[], char guess) {
    if (strlen(word) != strlen(targetWord))
        exit(1);
    int occurrences = 0;
    for (int i = 0; i < (int)strlen(word); ++i) {
        if (guess == targetWord[i] && word[i] != guess) {
            word[i] = guess;
            occurrences++;
        }
    }
    return occurrences;
}
