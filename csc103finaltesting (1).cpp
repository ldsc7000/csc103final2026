#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

// ---------------------------------------------------------
// ASCII ART (Requirement: 2 instances of ASCII art)
// ---------------------------------------------------------

// Function 1
void printTitle() {
    cout << "========================================================\n";
    cout << "      🔍 THE MYSTERY OF SHADOW MANOR 🔍\n";
    cout << "             A Text Adventure Game\n";
    cout << "========================================================\n\n";
}

// Function 2
void printGameOverArt() {
    cout << "      .------.\n";
    cout << "     /  _  _  \\\n";
    cout << "     | (o)(o) |\n";
    cout << "     \\   __   /\n";
    cout << "      '------'\n";
    cout << "      GAME OVER\n";
}


// ---------------------------------------------------------
// CLASSES & INHERITANCE (Topics: Objects/Classes, Inheritance)
// ---------------------------------------------------------

class Player {
public:
    string name;
    int score;           // Changing variable 1
    int health;          // Changing variable 2
    vector<string> inventory; // Changing variable 3

    Player() {
        name = "Unknown";
        score = 0;
        health = 3;
    }

    // Function 3 (Inside class counts as a function)
    void addItem(string item) {
        bool alreadyHave = false;
        // Topic: Loops & Vectors
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i] == item) {
                alreadyHave = true;
            }
        }
        if (alreadyHave == false) {
            inventory.push_back(item);
            cout << ">>> Got new item: " << item << " <<<\n";
        }
    }

    // Function 4
    bool hasItem(string item) {
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i] == item) {
                return true;
            }
        }
        return false;
    }
};

// Base class for mini games
class MiniGame {
public:
    int points;
    MiniGame() {
        points = 10;
    }
};

// Hangman inherits from MiniGame (Topic: Inheritance)
class HangmanGame : public MiniGame {
public:
    string word;
    string hint;
    vector<char> guessedLetters;
    int wrongGuesses;

    HangmanGame(string w, string h) {
        word = w;
        hint = h;
        wrongGuesses = 0;
        points = 15; // changing inherited variable
    }

    // Function 5
    bool play() {
        cout << "\n--- HANGMAN PUZZLE ---\n";
        cout << "Hint: " << hint << "\n";
        
        while (wrongGuesses < 6) {
            // Topic: Strings and Arrays
            bool won = true;
            string display = "";
            for (int i = 0; i < word.length(); i++) {
                char current = word[i];
                bool found = false;
                for (int j = 0; j < guessedLetters.size(); j++) {
                    if (guessedLetters[j] == current) {
                        found = true;
                    }
                }
                if (found) {
                    display += current;
                    display += " ";
                } else {
                    display += "_ ";
                    won = false;
                }
            }

            cout << "Word: " << display << "\n";
            cout << "Wrong guesses: " << wrongGuesses << "/6\n";

            if (won) {
                cout << "You solved the word: " << word << "!\n";
                return true;
            }

            cout << "Guess a letter: ";
            char guess;
            cin >> guess;

            guessedLetters.push_back(guess);

            // Check if correct
            bool correct = false;
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == guess) {
                    correct = true;
                }
            }

            if (correct == false) {
                cout << "Wrong!\n";
                wrongGuesses++;
            } else {
                cout << "Correct!\n";
            }
        }
        cout << "You failed the hangman puzzle. The word was " << word << ".\n";
        return false;
    }
};


// ---------------------------------------------------------
// USER-DEFINED FUNCTIONS & POINTERS (Topic: Pointers, Functions)
// ---------------------------------------------------------

// Function 6
void showStatus(Player* p) {
    // Topic: Pointers (using -> to access members)
    cout << "\n==============================\n";
    cout << "Detective: " << p->name << " | Health: " << p->health << " | Score: " << p->score << "\n";
    cout << "Inventory: ";
    if (p->inventory.size() == 0) {
        cout << "Empty\n";
    } else {
        for (int i = 0; i < p->inventory.size(); i++) {
            cout << p->inventory[i] << " ";
        }
        cout << "\n";
    }
    cout << "==============================\n";
}

// Function 7
void enterStudy(Player* p) {
    cout << "You enter the study. It is very dusty.\n";
    p->score += 5;
}

// Function 8
void enterLibrary(Player* p) {
    cout << "You walk into a massive library filled with books.\n";
}

// Function 9
void enterKitchen(Player* p) {
    cout << "You step into the kitchen. It smells like old food.\n";
}

// Function 10
void searchDesk(Player* p) {
    cout << "You look through the desk drawers.\n";
    p->addItem("Mysterious Letter");
    p->score += 5;
}

// Function 11
void takeClue(Player* p, string clue) {
    p->addItem(clue);
    p->score += 10;
    cout << "This clue is important!\n";
}

// Function 12
void showNotes() {
    cout << "\n*** YOUR NOTES ***\n";
    cout << "Suspect 1: The Butler\n";
    cout << "Suspect 2: The Heir\n";
    cout << "Suspect 3: The Maid\n";
    cout << "******************\n";
}

// Function 13 - Topic: Recursion!
void countdown(int n) {
    if (n == 0) {
        cout << "CLICK! The safe is open!\n";
    } else {
        cout << n << "...\n";
        countdown(n - 1); // calls itself
    }
}

// Function 14 - Requirement: Game within a game using rand()
void playSafeGame(Player* p) {
    cout << "\n--- SAFE CRACKING GAME ---\n";
    cout << "Guess the 4-digit code (1000 - 9999).\n";
    
    int code = rand() % 9000 + 1000;
    int attempts = 5;
    bool cracked = false;

    // Topic: Loops
    while (attempts > 0 && !cracked) {
        cout << "Enter guess (" << attempts << " tries left): ";
        int guess;
        cin >> guess;

        // Topic: Branches
        if (guess == code) {
            cracked = true;
        } else if (guess < code) {
            cout << "Too low!\n";
            attempts--;
        } else {
            cout << "Too high!\n";
            attempts--;
        }
    }

    if (cracked) {
        countdown(3); // using my recursive function
        p->score += 20;
        takeClue(p, "Safe Documents");
    } else {
        cout << "The safe locks you out!\n";
        p->health -= 1;
    }
}

// Function 15
void finalAccusation(Player* p, int guess) {
    int actualThief = 2; // It was the heir

    cout << "You point your finger at Suspect " << guess << "!\n";
    
    if (guess == actualThief) {
        cout << "CORRECT! The heir breaks down and cries. You solved it!\n";
        p->score += 100;
    } else {
        cout << "WRONG! The real thief gets away!\n";
        p->health = 0; // kill player
    }
}


// ---------------------------------------------------------
// MAIN FUNCTION & GAME LOOP
// ---------------------------------------------------------

int main() {
    srand(time(0)); // Seed random number generator

    printTitle();

    Player mainPlayer;
    cout << "Enter your detective's name: ";
    cin >> mainPlayer.name;

    // We will use an integer to track the 20 locations
    // 1 = Office, 2 = File Room, 3 = Estate, etc.
    int location = 1; 

    // Main Game Loop
    while (mainPlayer.health > 0 && location != 20) {
        
        showStatus(&mainPlayer); // pass pointer

        // Topic: Massive Branching (Standard beginner way to make a map)
        switch (location) {
            case 1: // Location 1
                cout << "LOCATION: Detective Office\n";
                cout << "1. Read case files\n";
                cout << "2. Check notes\n";
                cout << "3. Drive to Shadow Manor\n";
                int choice1;
                cin >> choice1;
                if (choice1 == 1) location = 2;
                else if (choice1 == 2) showNotes();
                else if (choice1 == 3) location = 3;
                break;

            case 2: // Location 2
                cout << "LOCATION: File Room\n";
                cout << "You must decode the file.\n";
                {
                    // Create object
                    HangmanGame h("necklace", "the stolen item");
                    if (h.play()) {
                        mainPlayer.score += 10;
                    } else {
                        mainPlayer.health -= 1;
                    }
                }
                location = 1; // Go back to office
                break;

            case 3: // Location 3
                cout << "LOCATION: Shadow Manor Estate Entrance\n";
                cout << "1. Go to Study\n";
                cout << "2. Go to Library\n";
                cout << "3. Go to Kitchen\n";
                cout << "4. Go to Garden\n";
                int choice3;
                cin >> choice3;
                if (choice3 == 1) location = 4;
                else if (choice3 == 2) location = 7;
                else if (choice3 == 3) location = 10;
                else if (choice3 == 4) location = 12;
                break;

            case 4: // Location 4
                cout << "LOCATION: The Study\n";
                enterStudy(&mainPlayer);
                cout << "1. Examine the safe\n";
                cout << "2. Search desk\n";
                cout << "3. Go up to Attic\n";
                cout << "4. Leave\n";
                int choice4;
                cin >> choice4;
                if (choice4 == 1) location = 5;
                else if (choice4 == 2) searchDesk(&mainPlayer);
                else if (choice4 == 3) location = 17;
                else if (choice4 == 4) location = 3;
                break;

            case 5: // Location 5
                cout << "LOCATION: Safe Puzzle\n";
                cout << "1. Try to open it\n";
                cout << "2. Go back\n";
                int choice5;
                cin >> choice5;
                if (choice5 == 1) {
                    playSafeGame(&mainPlayer);
                    location = 6;
                } else {
                    location = 4;
                }
                break;

            case 6: // Location 6
                cout << "LOCATION: Safe Opened\n";
                cout << "You got everything from the safe.\n";
                cout << "1. Return to Study\n";
                int choice6;
                cin >> choice6;
                location = 4;
                break;

            case 7: // Location 7
                cout << "LOCATION: The Library\n";
                enterLibrary(&mainPlayer);
                cout << "1. Look at journal\n";
                cout << "2. Search room\n";
                cout << "3. Leave\n";
                int choice7;
                cin >> choice7;
                if (choice7 == 1) location = 8;
                else if (choice7 == 2) { cout << "Found nothing.\n"; }
                else if (choice7 == 3) location = 3;
                break;

            case 8: // Location 8
                cout << "LOCATION: Journal Puzzle\n";
                {
                    HangmanGame h2("guilty", "admission of a crime");
                    if(h2.play()) {
                        location = 9;
                    } else {
                        mainPlayer.health -= 1;
                        location = 7;
                    }
                }
                break;

            case 9: // Location 9
                cout << "LOCATION: Journal Unlocked\n";
                takeClue(&mainPlayer, "Journal Confession");
                cout << "1. Go back\n";
                int choice9; cin >> choice9;
                location = 7;
                break;

            case 10: // Location 10
                cout << "LOCATION: Kitchen\n";
                enterKitchen(&mainPlayer);
                cout << "1. Check schedule\n";
                cout << "2. Go down to basement\n";
                cout << "3. Leave\n";
                int choice10; cin >> choice10;
                if (choice10 == 1) location = 11;
                else if (choice10 == 2) location = 15;
                else if (choice10 == 3) location = 3;
                break;

            case 11: // Location 11
                cout << "LOCATION: Schedule Found\n";
                takeClue(&mainPlayer, "Maid Schedule");
                location = 10;
                break;

            case 12: // Location 12
                cout << "LOCATION: Dark Garden\n";
                cout << "1. Go to shed\n";
                cout << "2. Go inside\n";
                int choice12; cin >> choice12;
                if(choice12 == 1) location = 13;
                else location = 3;
                break;

            case 13: // Location 13
                cout << "LOCATION: Tool Shed\n";
                cout << "1. Search tools\n";
                cout << "2. Leave\n";
                int choice13; cin >> choice13;
                if (choice13 == 1) location = 14;
                else location = 12;
                break;

            case 14: // Location 14
                cout << "LOCATION: Shed Search\n";
                cout << "Nothing here but a rusted shovel.\n";
                location = 13;
                break;

            case 15: // Location 15
                cout << "LOCATION: Basement\n";
                cout << "It's super dark.\n";
                cout << "1. Try fusebox\n";
                cout << "2. Go upstairs\n";
                int choice15; cin >> choice15;
                if (choice15 == 1) location = 16;
                else location = 10;
                break;

            case 16: // Location 16
                cout << "LOCATION: Fusebox Puzzle\n";
                cout << "ZAP! You touched a live wire.\n";
                mainPlayer.health -= 1;
                location = 15;
                break;

            case 17: // Location 17
                cout << "LOCATION: Attic\n";
                cout << "1. Make Final Accusation\n";
                cout << "2. Go downstairs\n";
                int choice17; cin >> choice17;
                if (choice17 == 1) location = 18;
                else location = 4;
                break;

            case 18: // Location 18
                cout << "LOCATION: Confrontation Menu\n";
                showNotes();
                cout << "Who did it? (1, 2, or 3): ";
                int guess;
                cin >> guess;
                finalAccusation(&mainPlayer, guess);
                
                if (mainPlayer.health > 0) {
                    location = 19; // Win screen
                } else {
                    location = 20; // Game over screen
                }
                break;

            case 19: // Location 19 (Win State)
                cout << "\n*** YOU WIN! ***\n";
                cout << "Final Score: " << mainPlayer.score << "\n";
                return 0; // End program

            default:
                cout << "Invalid location!\n";
                break;
        }
    }

    // Location 20 (Game Over State, hit when health drops to 0)
    printGameOverArt();
    cout << "You failed the case!\n";

    return 0;
}