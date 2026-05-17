#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
//
//3: strawberryfy the code
using namespace std;

void printTitle() {
    cout << "========================================================\n";
    cout << "      🔍 -=THE MYSTERY OF SHADOW MANOR=- 🔍\n";
    cout << "              -An Adventure Game-\n";
    cout << "========================================================\n\n";
}

void printGameOverArt() {
    cout << "      .------.\n";
    cout << "     /  _  _  \\\n";
    cout << "     | (o)(o) |\n";
    cout << "     \\   __   /\n";
    cout << "      '------'\n";
    cout << "      GAME OVER\n";
}

class Player {
public:
    string name;//free time?: make name multi-wordable
    int score;           // Changin variable1
    int health;          // Changing variable2
    vector<string> inventory; // Changing var 3

    Player() {
        name = "Unknown";//name inputed
        score = 0;
        health = 3;
    }

    void addItem(string item) {
        bool alreadyHave = false;
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i] == item) {
                alreadyHave = true;
            }
        }
        if (alreadyHave == false) {
            inventory.push_back(item);
            cout << ">>> Got new item: " << item << " <<<\n";
        }
    }//bool?

    bool hasItem(string item) {
        for (int i = 0; i < inventory.size(); i++) {//;
            if (inventory[i] == item) {
                return true;
            }
        }
        return false;
    }
};

class MiniGame {
public:
    int points;
    MiniGame() {
        points = 10;
    }
};
//find out how to crate correct class
class HangmanGame : public MiniGame {//resorted to chatgpt. Promted on how to continue
public:
    string word;
    string hint;
    vector<char> guessedLetters;
    int wrongGuesses;

    HangmanGame(string w, string h) {
        word = w;
        hint = h;
        wrongGuesses = 0;
        points = 15;
    }

    bool play() {
        cout << "\n--- HANGMAN PUZZLE ---\n";
        cout << "Hint: " << hint << "\n";
        
        while (wrongGuesses < 6) {
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
                cout << "You have solved the word: " << word << "!\n";
                return true;
            }

            cout << "Guess a letter: ";
            char guess;
            cin >> guess;

            guessedLetters.push_back(guess);

            bool correct = false;
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == guess) {
                    correct = true;
                }
            }

            if (correct == false) {
                cout << "NoOoOo Incorrecto!\n";
                wrongGuesses++;
            } else {
                cout << "YeEeEe Correcto!\n";
            }
        }
        cout << "DisInspector NoGadget, you have failed the hangman poozzle. The word was " << word << ".\n";
        return false;
    }
};

void showStatus(Player* p) {
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

void enterStudy(Player* p) {
    cout << "You enter the study. It is very dusty  and crusty.\n";
    p->score += 5;
}

void enterLibrary(Player* p) {
    cout << "You walk into a massive library filled with books.\n";
}

void enterKitchen(Player* p) {
    cout << "You step into the kitchen. It smells like auntie's old sandwhich (*~~*).\n";
}

void searchDesk(Player* p) {
    cout << "You look through the desk drawers.\n";
    p->addItem("Mysterious Letter");
    p->score += 5;
}

void takeClue(Player* p, string clue) {
    p->addItem(clue);
    p->score += 10;
    cout << "This clue is very much important!\n";
}

void showNotes() {
    cout << "\n*** YOUR NOTES ***\n";
    cout << "Suspect 1: The Butler\n";
    cout << "Suspect 2: The Heir\n";
    cout << "Suspect 3: The Maid\n";
    cout << "******************\n";
}

void countdown(int n) {
    if (n == 0) {
        cout << "CLICK! The safe has been opened like McDonalds!\n";
    } else {
        cout << n << "...\n";
        countdown(n - 1); // calls itself
    }
}

// rand() attempt
void playSafeGame(Player* p) {
    cout << "\n--- SAFE CRACKING GAME ---\n";
    cout << "Guess the 4-digit code (1000 - 9999).\n";
    
    int code = rand() % 9000 + 1000;
    int attempts = 5;
    bool cracked = false;

    while (attempts > 0 && !cracked) {
        cout << "Enter guess (" << attempts << " tries left): ";
        int guess;
        cin >> guess;

        if (guess == code) {
            cracked = true;
        } else if (guess < code) {
            cout << "Too low you goldfish!\n";
            attempts--;
        } else {
            cout << "SpongeRobert, thats too high!\n";
            attempts--;
        }
    }

    if (cracked) {
        countdown(3);
        p->score += 20;
        takeClue(p, "Safe Documents");
    } else {
        cout << "The safe locks you out. Guaghawawawa!\n";
        p->health -= 1;
    }
}

void finalAccusation(Player* p, int guess) {
    int actualThief = 2; // heair will be theif

    cout << "You point your finger at Suspect " << guess << "!\n";
    
    if (guess == actualThief) {
        cout << "CORRECT!!! The heir cries like a baby. You have solved it!!\n";
        p->score += 100;
    } else {
        cout << "NEINNN DAS ISSS WRONG!! The real thief gets away!!\n";
        p->health = 0; // player dies x_x
    }
}


int main() {
    srand(time(0)); //random number generator

    printTitle();

    Player mainPlayer;
    cout << "Enter your detective's one worded name: "; //try making it more words(save to end)
    cin >> mainPlayer.name;

    // trying ints for locations
    int location = 1; 

    while (mainPlayer.health > 0 && location != 20) {//min: 20, 20 =game over?
              
        showStatus(&mainPlayer);

        switch (location) {
            case 1: // case1= Location 1, case 2= location2, etc.
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

            case 2:
                cout << "LOCATION: File Room\n";
                cout << "Youuuu massst decode the file.\n";
                {
                    HangmanGame h("necklace", "the stolen item");
                    if (h.play()) {
                        mainPlayer.score += 10;
                    } else {
                        mainPlayer.health -= 1;
                    }
                }
                location = 1; //back to officeice
                break;

            case 3:
                cout << "LOCATION: Shadow Manor Estate Entrance\n";
                cout << "1. Go to Study\n";
                cout << "2. Go to Library\n";
                cout << "3. Go to Kitchen\n";
                cout << "4. Go to Garden\n";
                int choice3;
                cin >> choice3;
                if (choice3 == 1) location = 4;//check for errors
                else if (choice3 == 2) location = 7;
                else if (choice3 == 3) location = 10;
                else if (choice3 == 4) location = 12;
                break;

            case 4:
                cout << "LOCATION: The Study\n";
                enterStudy(&mainPlayer);
                cout << "1. Examine tha safe\n";
                cout << "2. Search desk\n";
                cout << "3. Go up to Attic, don't be scared\n";
                cout << "4. Leave\n";
                int choice4;
                cin >> choice4;
                if (choice4 == 1) location = 5;//check also
                else if (choice4 == 2) searchDesk(&mainPlayer);
                else if (choice4 == 3) location = 17;
                else if (choice4 == 4) location = 3;
                break;

            case 5:
                cout << "LOCATION: Safe Puzzle\n";
                cout << "1. Try to open it turkey lover\n";
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

            case 6:
                cout << "LOCATION: Safe Opened\n";
                cout << "You got everything from the safe.\n";
                cout << "1. Return to Study\n";
                int choice6;
                cin >> choice6;
                location = 4;
                break;

            case 7:
                cout << "LOCATION: The Library\n";
                enterLibrary(&mainPlayer);
                cout << "1. Look at Le journal\n";
                cout << "2. Search room\n";
                cout << "3. Leave at once!\n";
                int choice7;
                cin >> choice7;
                if (choice7 == 1) location = 8;
                else if (choice7 == 2) { cout << "Bad luck scallywagon, nothing found.\n"; }
                else if (choice7 == 3) location = 3;
                break;

            case 8:
                cout << "LOCATION: Journal Puzzle\n";
                {
                    HangmanGame h2("GUILTYY", "admission of a crime");
                    if(h2.play()) {
                        location = 9;
                    } else {
                        mainPlayer.health -= 1;
                        location = 7;
                    }
                }
                break;

            case 9:
                cout << "LOCATION: Journal Unlocked\n";
                takeClue(&mainPlayer, "Journal Confession");
                cout << "1. Go back\n";
                int choice9; cin >> choice9;
                location = 7;
                break;

            case 10:
                cout << "LOCATION: Kitchen\n";
                enterKitchen(&mainPlayer);
                cout << "1. Check thy schedule\n";
                cout << "2. Go down to spooky basement\n";
                cout << "3. Leave\n";
                int choice10; cin >> choice10;
                if (choice10 == 1) location = 11;
                else if (choice10 == 2) location = 15;
                else if (choice10 == 3) location = 3;
                break;

            case 11:
                cout << "LOCATION: Schedule Found\n";
                takeClue(&mainPlayer, "Maid Schedule");
                location = 10;
                break;

            case 12:
                cout << "LOCATION: Dark Garden\n";
                cout << "1. Go to the shed\n";
                cout << "2. Go insideee\n";
                int choice12; cin >> choice12;
                if(choice12 == 1) location = 13;
                else location = 3;
                break;

            case 13:
                cout << "LOCATION: Tool Shed\n";
                cout << "1. Search tools\n";
                cout << "2. Leave\n";
                int choice13; cin >> choice13;
                if (choice13 == 1) location = 14;
                else location = 12;
                break;

            case 14:
                cout << "LOCATION: Shed search\n";
                cout << "Nothing here but a rusted shovel ***(Sad mario noises)***\n";
                location = 13;
                break;

            case 15:
                cout << "LOCATION: Basement\n";
                cout << "It's super dark, I can no seeee.\n";
                cout << "1. Try the fusebox\n";
                cout << "2. Hamburger Hudini, go upstairs!\n";
                int choice15; cin >> choice15;
                if (choice15 == 1) location = 16;
                else location = 10;
                break;

            case 16:
                cout << "LOCATION: Fusebox Puzzle\n";
                cout << "ZAPPITY WAZZITY ZAP! You touched a live wire you MINION.\n";
                mainPlayer.health -= 1;
                location = 15;
                break;

            case 17:
                cout << "LOCATION: Attic\n";
                cout << "1. Make Final Accusation\n";
                cout << "2. Go downstairs you oscillating pancake\n";
                int choice17; cin >> choice17;
                if (choice17 == 1) location = 18;
                else location = 4;
                break;

            case 18:
                cout << "LOCATION: Confrontation Menu\n";
                showNotes();
                cout << "Who did it? Hmmmm (1, 2, or 3): ";
                int guess;
                cin >> guess;
                finalAccusation(&mainPlayer, guess);
                
                if (mainPlayer.health > 0) {
                    location = 19; // (Win screen) :]
                } else {
                    location = 20; // (Game over screen) :C
                }
                break;

            case 19: //WIN
                cout << "\n*** YOU WIN! ***\n";
                cout << "Final Score: " << mainPlayer.score << "\n";
                return 0;

            default:
                cout << "UUMMM EXCUSIE MOI??? Invalid location!\n";
                break;
        }
    }

    printGameOverArt();
    cout << "You failed the case! Womp Wompp Womppp :C\n";

    return 0;
}