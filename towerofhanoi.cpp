// The Tower of Hanoi, by Al Sweigart
// A stack-moving puzzle game.
// This code is available at https://nostarch.com/big-book-small-python-programming
// #77 TOWER OF HANOI

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int TOTAL_DISKS = 5; // More disks means a more difficult puzzle.
void displayDisk(int width);
void displayTowers(map<char, vector<int>> towers);
void askForPlayerMove(map<char, vector<int>> towers, char& fromTower, char& toTower);

int main() {
    cout << "The Tower of Hanoi, by Al Sweigart\n";
    cout << "Move the tower of disks, one disk at a time, to another tower.Larger\n";
    cout << "disks cannot rest on top of a smaller disk.\n";
    cout << "More info at https://en.wikipedia.org/wiki/Tower_of_Hanoi\n";

    // Start with all disks on tower A:
    vector <int> COMPLETE_TOWER(TOTAL_DISKS);
    for (int i = 0; i < TOTAL_DISKS; ++i) {
        COMPLETE_TOWER[i] = TOTAL_DISKS - i;
    }

    // Set up the towers.The end of the list is the top of the tower.
    map<char, vector<int>> towers = {
        {'A', COMPLETE_TOWER}, {'B', {}}, {'C', {}}
    };

    while (1) { // Run a single turn.
        // Display the towers and disks:
        displayTowers(towers);

        // Ask the user for a move:
        char fromTower, toTower;
        askForPlayerMove(towers, fromTower, toTower);

        // Move the top disk from fromTower to toTower:
        int disk = towers[fromTower][towers[fromTower].size() - 1];
        towers[fromTower].pop_back();
        towers[toTower].push_back(disk);

        // Check if the user has solved the puzzle:
        if (towers['B'] == COMPLETE_TOWER || towers['C'] == COMPLETE_TOWER) {
            displayTowers(towers); // Display the towers one last time.
            cout << "You have solved the puzzle! Well done!\n";
            return 0;
        }
    }

    return 0;
}

void displayDisk(int width) {
    // Display a disk of the given width. A width of 0 means no disk.
    string emptySpace(TOTAL_DISKS - width, ' ');
    if (width == 0) {
        // Display a pole segment without a disk:
        cout << emptySpace << "||" << emptySpace;
    } else {
        // Display the disk:
        string disk(width, '@');
        string numLabel = "_" + to_string(width);
        cout << emptySpace << disk << numLabel << disk << emptySpace;
    }
}

void displayTowers(map<char, vector<int>> towers) {
    // Display the current state.
    // Display the three towers:
    for (int i = TOTAL_DISKS; i != -1; --i) {
        for (auto tower : towers) {
            if (i >= tower.second.size()) {
                displayDisk(0); // Display the bare pole with no disk.
            } else {
                displayDisk(tower.second[i]); // Display the disk.
            }
        }
        cout << "\n";
    }

    // Display the tower labels A, B, and C.
    string emptySpace(TOTAL_DISKS, ' ');
    cout << emptySpace << " A" << emptySpace << emptySpace << " B" << emptySpace << emptySpace << " C\n";
}

void askForPlayerMove(map<char, vector<int>> towers, char& fromTower, char& toTower) {
    // Asks the player for a move. Returns (fromTower, toTower).
    while (1) { // Keep asking player until they enter a valid move.
        std::cout << "Enter the letters of 'from' and 'to' towers, or QUIT.\n";
        std::cout << "(e.g. AB to moves a disk from tower A to tower B.)\n";
        std::cout << "> ";
        string response;
        cin >> response;
        transform(response.begin(), response.end(), response.begin(), ::toupper);

        if (response == "QUIT") {
            cout << "Thanks for playing!\n";
            exit(0);
        }

        // Make sure the user entered valid tower letters:
        if (!(response == "AB" || response == "AC" || response == "BA" || response == "BC" || response == "CA" || response == "CB")) {
            cout << "Enter one of AB, AC, BA, BC, CA, or CB.\n";
            continue; // Ask player again for their move.
        }
            
        // Syntactic sugar - Use more descriptive variable names:
        fromTower = response[0];
        toTower = response[1];

        if (towers[fromTower].size() == 0) {
            // The "from" tower cannot be an empty tower:
            cout << "You selected a tower with no disks.\n";
            continue; // Ask player again for their move.
        } else if (towers[toTower].size() == 0) {
            // Any disk can be moved onto an empty "to" tower:
            break;
        } else if (towers[toTower][towers[toTower].size() - 1] < towers[fromTower][towers[fromTower].size() - 1]) {
            cout << "Can\'t put larger disks on top of smaller ones.";
            continue; // Ask player again for their move.
        } else {
            // This is a valid move, so return the selected towers:
            break;
        }
    }
}
