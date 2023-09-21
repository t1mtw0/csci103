// Add other #includes if you need
#include <cstdlib>
#include <iostream>

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You
 */
const char suit[4] = {'H', 'S', 'D', 'C'};
const char* type[13] = {"2", "3",  "4", "5", "6", "7", "8",
                        "9", "10", "J", "Q", "K", "A"};
const int value[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[]) {
  /******** You complete ****************/

  for (int i = NUM_CARDS - 1; i >= 1; --i) {
    int j = rand() % (i + 1);
    int temp = cards[j];
    cards[j] = cards[i];
    cards[i] = temp;
  }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id) {
  /******** You complete ****************/

  std::cout << type[id % 13] << "-" << suit[id / 13];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id) {
  /******** You complete ****************/

  return value[id % 13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards) {
  /******** You complete ****************/

  for (int i = 0; i < numCards; ++i) {
    printCard(hand[i]);
    std::cout << " ";
  }
  std::cout << "\n";
}

/**
 * Should return the total score of the provided hand.
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards) {
  /******** You complete ****************/

  int totalScore = 0;
  int aces = 0;
  for (int i = 0; i < numCards; ++i) {
    int cv = cardValue(hand[i]);
    if (cv == 11) {
      aces++;
    } else {
      totalScore += cv;
    }
  }
  while (aces > 0) {
    if (totalScore + 11 <= 21) {
      totalScore += 11;
      aces--;
    } else {
      totalScore++;
      aces--;
    }
  }
  return totalScore;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[]) {
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if (argc < 2) {
    std::cout << "Error - Please provide the seed value." << std::endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/

  while (true) {
    for (int i = 0; i < NUM_CARDS; ++i) {
      cards[i] = i;
    }

    shuffle(cards);

    int numPlayerCards = 0;
    int numDealerCards = 0;
    int randI = 0;

    phand[numPlayerCards++] = cards[randI++];
    dhand[numDealerCards++] = cards[randI++];
    phand[numPlayerCards++] = cards[randI++];
    dhand[numDealerCards++] = cards[randI++];

    std::cout << "Dealer: ? ";
    printCard(dhand[1]);
    std::cout << "\n";
    std::cout << "Player: ";
    printHand(phand, numPlayerCards);

    bool won = false;
    if (getBestScore(phand, numPlayerCards) == 21) {
      won = true;
    }

    bool busted = false;
    while (!busted && !won) {
      std::cout << "Type 'h' to hit and 's' to stay:\n";
      char move;
      std::cin >> move;

      if (move != 'h' && move != 's') {
        exit(1);
      }

      if (move == 'h') {
        phand[numPlayerCards++] = cards[randI++];
        std::cout << "Player: ";
        printHand(phand, numPlayerCards);
        int playerScore = getBestScore(phand, numPlayerCards);
        if (playerScore > 21) {
          std::cout << "Player busts\n";
          int dealerScore = getBestScore(dhand, numDealerCards);
          std::cout << "Lose " << playerScore << " " << dealerScore << "\n";
          busted = true;
        } else if (playerScore == 21) {
          break;
        }
      } else {
        break;
      }
    }

    bool dealerBusted = false;
    if (!busted) {
      int dealerScore = getBestScore(dhand, numDealerCards);
      while (dealerScore < 17) {
        dhand[numDealerCards++] = cards[randI++];
        dealerScore = getBestScore(dhand, numDealerCards);
      }
      std::cout << "Dealer: ";
      printHand(dhand, numDealerCards);
      if (dealerScore > 21) {
        int playerScore = getBestScore(phand, numPlayerCards);
        std::cout << "Dealer busts\n";
        std::cout << "Win " << playerScore << " " << dealerScore << "\n";
        dealerBusted = true;
      }
    }

    if (!busted && !dealerBusted) {
      int playerScore = getBestScore(phand, numPlayerCards);
      int dealerScore = getBestScore(dhand, numDealerCards);
      if (playerScore > dealerScore) {
        std::cout << "Win " << playerScore << " " << dealerScore << "\n";
      } else if (playerScore < dealerScore) {
        std::cout << "Lose " << playerScore << " " << dealerScore << "\n";
      } else {
        std::cout << "Tie " << playerScore << " " << dealerScore << "\n";
      }
    }

    std::cout << "\nPlay again? [y/n]\n";
    char pa;
    std::cin >> pa;

    if (pa != 'y') break;
  }

  return 0;
}
