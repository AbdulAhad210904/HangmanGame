//Created By:
//https://github.com/AbdulAhad210904
//https://github.com/HuzaifaAzhar

#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <iostream> // for console input/output
#include <fstream> // for file handling

using namespace std;

const int MAX_TRIES = 6; // Maximum number of tries allowed

struct Word {
  string easy_words[10];
  string medium_words[10];
  string hard_words[10];
  string easy_filename = "easy.txt";
  string medium_filename = "medium.txt";
  string hard_filename = "hard.txt";

  void loadWords(string words[], int size, string filename) {
    ifstream file(filename);
    if (file.is_open()) {
      for (int i = 0; i < size; i++) {
        if (!getline(file, words[i])) {
          break;
        }
      }
      file.close();
    }
  }

  Word() {
    loadWords(easy_words, 10, easy_filename);
    loadWords(medium_words, 10, medium_filename);
    loadWords(hard_words, 10, hard_filename);
  }
};

class Hangman {
  private: int tries;
  string word;
  string hidden;
  bool gameover;
  bool used_letters[26];

  public: Hangman() {
    system("cls");
    tries = 0;
    gameover = false;
    Word w;
    int level;
    cout << "Welcome to Hangman!" << endl;
    ifstream load_file("hangman_save.txt");
    if (!load_file) {
      cout << "Choose a level (1 for easy, 2 for medium, 3 for hard): ";
      cin >> level;
      while (level < 1 || level > 3) {
        cout << "Invalid input. Please enter a valid level (1 for easy, 2 for "
        "medium, 3 for hard): ";
        cin >> level;
      }
      srand(time(NULL)); // Seed random number generator
      int index = rand() % 10; // Choose a random index
      switch (level) {
      case 1:
        word = w.easy_words[index];
        break;
      case 2:
        word = w.medium_words[index];
        break;
      case 3:
        word = w.hard_words[index];
        break;
      }
    }
    load_file.close();
    hidden = string(word.length(), '_'); // Initialize hidden word with underscores
    for (int i = 0; i < 26; i++) {
      used_letters[i] = false; // Initialize used letters array to all false
    }
  }

  void saveGame() {
    ofstream save_file("hangman_save.txt");
    save_file << tries << "\n" <<
      word << "\n" <<
      hidden << "\n" <<
      gameover << "\n";
    for (int i = 0; i < 26; i++) {
      save_file << used_letters[i] << " ";
    }
    save_file << "\n";
    save_file.close();
    cout << "Game saved successfully." << endl;
  }

  void loadGame() {
    ifstream load_file("hangman_save.txt");
    if (!load_file) {
      return;
    }
    load_file >> tries >> word >> hidden >> gameover;
    for (int i = 0; i < 26; i++) {
      load_file >> used_letters[i];
    }
    load_file.close();
    cout << "Game loaded successfully." << endl;
  }

  void drawHangman() {
    cout << endl;
    switch (tries) {
    case 0:
      cout << endl;
      break;
    case 1:
      cout << endl;
      break;
    case 2:
      cout << endl;
      cout << "  |----------" << endl;
      cout << "  |      O   " << endl;
      cout << "  |           " << endl;
      cout << "  |           " << endl;
      break;
    case 3:
      cout << endl;
      cout << "  |----------" << endl;
      cout << "  |      O   " << endl;
      cout << "  |      |   " << endl;
      cout << "  |           " << endl;
      break;
    case 4:
      cout << endl;
      cout << "  |----------" << endl;
      cout << "  |      O   " << endl;
      cout << "  |      |   " << endl;
      cout << "  |     /     " << endl;
      break;
    case 5:
      cout << endl;
      cout << "  |----------" << endl;
      cout << "  |      O   " << endl;
      cout << "  |      |   " << endl;
      cout << "  |     /|    " << endl;
      break;
    case 6:
      cout << endl;
      cout << "  |----------" << endl;
      cout << "  |      O   " << endl;
      cout << "  |      |   " << endl;
      cout << "  |     /|\\  " << endl;
      break;
    }
  }

  void displayStatus() {
    system("cls");
    cout << "Word: " << hidden << endl;
    cout << "Wrong Tries: " << tries << endl;
    cout << "Remaining Wrong Tries: " << (6 - tries) << endl;
    cout << "Used Letters: ";
    for (int i = 0; i < 26; i++) {
      if (used_letters[i]) {
        cout << (char)('a' + i) << " ";
      }
    }
    cout << endl;
    drawHangman();
  }

  void checkLetter(char letter) {
    if (used_letters[letter - 'a'] != true) {
      bool correct = false;
      for (int i = 0; i < word.length(); i++) {
        if (word[i] == letter) {
          hidden[i] = letter;
          correct = true;
        }
      }
      if (!correct) {
        tries++;
      }
      used_letters[letter - 'a'] = true; // Mark the letter as used
    } else {
      cout << "You have already used this letter" << endl;
      system("pause");
    }

  }

  bool checkGameOver() {
    if (tries == MAX_TRIES) {
      gameover = true;
      displayStatus();
      cout << "Game over! The word was " << word << "." << endl;
      remove("hangman_save.txt");
    } else if (word == hidden) {
      gameover = true;
      displayStatus();
      cout << "Congratulations! You guessed the word " << word << "!" << endl;
      remove("hangman_save.txt");
    }
    return gameover;
  }

  void play() {
    loadGame();
    while (!checkGameOver()) {
      saveGame();
      displayStatus();
      char letter;
      cout << "Guess a letter: ";
      cin >> letter;
      letter = tolower(letter);
      checkLetter(letter);
    }
  }
};

int main() {
  Hangman game;
  game.play();
  return 0;
}
