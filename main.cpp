#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <vector>

using namespace std;

//Greeting, Rules, Notes, and Warnings

//Difficulty
int Diff(){
    int maxNum = 20;
    int difficulty = 0;

    while (true){
        cout << "Choose your difficulty:";
        cout << "[1. Normal (1-10) | 2. Hard (1-50) | 3. A bit harder than hard (1-100)]" << endl;
        cout << "choice: ";
        cin >> difficulty;
        
        if (cin.fail() || difficulty < 1 || difficulty > 3) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Choose a number between 1-3... idiot" << endl;
        } else{
            break;
        }

    }
    
    if (difficulty == 1) {
        maxNum = 10;
    } else if(difficulty == 2) {
        maxNum = 50;
    } else if(difficulty == 3) {
        maxNum = 100;
    }

    //Need maxNum to transfer to RanNumGen
    return maxNum;

}

//Random Number Generator
int RanNumGen(int min = 1, int max = 20){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    int randomValue = distrib(gen);

    return randomValue;
}

//Player ID Generator
string PlayerIDGen(){
    int playerID = RanNumGen(1, 999999);
    return "player" + to_string(playerID) + "";
}

//Greeting for player
void greet(string username){
    cout << "Welcome " << username << endl;
    
    //string username = PlayerIDGen();
    ifstream fileRules("rules.txt");
    if (!fileRules.is_open()) {
        cout << "Error: Could not load 'rules.txt', please make sure its in the same folder as './guess_game'. " << endl;
        return;
    }

    string line;
    while (getline(fileRules, line)) {
        cout << line << endl;
    };

    fileRules.close();
}

//Player Guess history
void PrintHistory(const vector<int> &guessHistory) {
            cout << "Your Guess Timeline: [";

            for (size_t g=0; g < guessHistory.size(); g++) {
                cout << guessHistory[g];
                if (g < guessHistory.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
}

//Actual Game
int main() {

    int userChoice = 21;

    while (userChoice == 21) {
        //1. Welcome
        string player = PlayerIDGen();
        greet(player);

        //B1. Secret number to guess
        int tries = 1;
        int activeMax = Diff();
        int sn = RanNumGen(1, activeMax);
        int user;
        vector<int> guessHistory;
        
        //2. Ask
        cout << "Guess the number" << endl;
    

        //3. Check
        do {
            cout << "type your guess: "; 
            cin >> user;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter a number! Your going to break the system and your RAM trying to do that letter bs." << endl;
                cout << "type your guess: ";
                cin >> user;
            }

            guessHistory.push_back(user);

            if (user == sn) {
                cout << "correct" << endl << "" << endl;
                cout << "Attempt:" << tries << endl << "" << endl;
                PrintHistory(guessHistory);
                break;
            } else if (user > sn) {
                /*says low and high*/
                cout << "high" << endl << "" << endl;
                cout << "Attempt:" << tries++ << endl << "" << endl;
                continue;
            } else if (user < sn) {
                cout << "low" << endl << "" << endl;
                cout << "Attempt:" << tries++ << endl << "" << endl;
                continue;
            }
        }
        while (user != sn);
    
        // --RESTART MENU--
        cout << "would you like to restart?" << endl;
        cout << "[Y = 21 | N = 22 ]" << endl;
        cout << "user: ";
        cin >> userChoice;
        //If they chose yes, Restart the game (loop)

        if (userChoice == 22) {
            cout << "come back soon!";
            break;
        }
    }

    return 0;
}

