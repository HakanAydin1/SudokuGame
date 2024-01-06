#include <fstream>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <numeric>

using namespace std;
using namespace std::chrono;

const int GRID_SIZE = 9;
const int SUBGRID_SIZE = 3;
const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;

void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    cout << "-------------------------\n";
    for (int i = 0; i < GRID_SIZE; i++) {
        cout << "| ";
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                cout << ". ";
            }
            else {
                cout << grid[i][j] << " ";
            }
            if ((j + 1) % SUBGRID_SIZE == 0) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((i + 1) % SUBGRID_SIZE == 0) {
            cout << "-------------------------\n";
        }
    }
}

bool isSafe(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % SUBGRID_SIZE;
    int startCol = col - col % SUBGRID_SIZE;

    for (int i = 0; i < SUBGRID_SIZE; i++) {
        for (int j = 0; j < SUBGRID_SIZE; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    int row = -1, col = -1;

    // Finding an unassigned cell and breaking out of the loop once found
    for (int i = 0; i < GRID_SIZE && row == -1; i++) {
        for (int j = 0; j < GRID_SIZE && row == -1; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
            }
        }
    }

    // If all cells are filled, the puzzle is solved
    if (row == -1)
        return true;

    for (int num = 1; num <= GRID_SIZE; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}

void generateSudoku(int grid[GRID_SIZE][GRID_SIZE], int difficulty) {
    while (true) {
        // Generate the grid
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                grid[i][j] = 0;
            }
        }

        // Fill the first row with a shuffled sequence of numbers
        vector<int> numbers;
        for (int i = 1; i <= GRID_SIZE; ++i) {
            numbers.push_back(i);
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(numbers.begin(), numbers.end(), g);

        for (int i = 0; i < GRID_SIZE; ++i) {
            grid[0][i] = numbers[i];
        }

        solveSudoku(grid);  // Solve the generated puzzle

        int numToRemove = 0;
        if (difficulty == EASY) {
            numToRemove = 35;  // Adjust the number of cells to remove for different difficulty levels
        }
        else if (difficulty == MEDIUM) {
            numToRemove = 45;
        }
        else if (difficulty == HARD) {
            numToRemove = 55;
        }

        for (int k = 0; k < numToRemove; ++k) {
            int randRow = rand() % GRID_SIZE;
            int randCol = rand() % GRID_SIZE;
            if (grid[randRow][randCol] != 0) {
                grid[randRow][randCol] = 0;
            }
            else {
                k--;  // Decrement k if we didn't remove a number
            }
        }

        // Check if the puzzle has a unique solution
        int tempGrid[GRID_SIZE][GRID_SIZE];
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                tempGrid[i][j] = grid[i][j];
            }
        }

        if (solveSudoku(tempGrid)) {
            // If the puzzle has a unique solution, break out of the loop
            break;
        }
    }
}









bool isFull(int grid[GRID_SIZE][GRID_SIZE]) {
    int emptyCells = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                emptyCells++;
                if (emptyCells > 1) // More than 1 empty cell indicates grid isn't full
                    return false;
            }
        }
    }
    return emptyCells == 0; // Return true only if there are no empty cells
}

void resetGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

bool validateInput(int row, int col, int num) {
    if (row < 1 || row > GRID_SIZE || col < 1 || col > GRID_SIZE || num < 1 || num > 9) {
        return false;
    }
    return true;
}

bool checkSolution(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int num = grid[i][j];
            grid[i][j] = 0; // Temporarily remove the number to check for uniqueness
            if (num != 0 && !isSafe(grid, i, j, num)) {
                grid[i][j] = num; // Restore the number
                return false;
            }
            grid[i][j] = num; // Restore the number
        }
    }
    return true;
}

long long int timer() {
    auto start = high_resolution_clock::now();
    // Perform the task
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    return duration.count();
}

bool solveWholeSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    int row = -1, col = -1;

    // Finding an unassigned cell and breaking out of the loop once found
    for (int i = 0; i < GRID_SIZE && row == -1; i++) {
        for (int j = 0; j < GRID_SIZE && row == -1; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
            }
        }
    }

    // If all cells are filled, the puzzle is solved
    if (row == -1)
        return true;

    for (int num = 1; num <= GRID_SIZE; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveWholeSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}

bool getHint(int grid[GRID_SIZE][GRID_SIZE], int& hintRow, int& hintCol, int& hintNum) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) {
                for (int num = 1; num <= GRID_SIZE; ++num) {
                    if (isSafe(grid, i, j, num)) {
                        hintRow = i;
                        hintCol = j;
                        hintNum = num;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}



void playGame(int grid[GRID_SIZE][GRID_SIZE], int difficulty, vector<int>& times) {
    int attempts = 0;
    int timeElapsed = 0;
    int row, col, num;
    int hintRow, hintCol, hintNum; // Variables to store hint details
    bool hintRequested = false; // Flag to control hint display
    cout << "Instructions: Enter row, column, and number (e.g., 1 2 3). Enter '0 0 0' to exit, '0 0 9' to reset, '0 0 8' to give up, '0 0 7' to let the computer solve it, or '0 0 6' to get a hint.\n";
    while (!isFull(grid)) {
        cout << "Enter move: ";
        cin >> row >> col >> num;

        if (row == 0 && col == 0 && num == 6) {
            if (getHint(grid, hintRow, hintCol, hintNum)) {
                hintRequested = true; // Set the flag for hint request
                cout << "Hint: Consider row " << hintRow + 1 << " and column " << hintCol + 1 << "\n";
                continue;
            }
            else {
                cout << "No possible hints available.\n";
                continue;
            }
        }

        //if (hintRequested) {
        //    cout << "Please use the provided hint or continue the game.\n";
        //    hintRequested = false; // Reset the hint request flag
        //    continue;
        //}

        if (row == 0 && col == 0 && num == 9) {
            resetGrid(grid);
            generateSudoku(grid, difficulty); // Regenerate a new puzzle after reset
            cout << "\nGrid reset.\n";
            printGrid(grid); // Display the new grid
            continue; // Continue the game loop
        }

        if (row == 0 && col == 0 && num == 7) {
            if (solveWholeSudoku(grid)) {
                cout << "\nSudoku Solved by the Computer:\n";
                printGrid(grid);
                return;
            }
            else {
                cout << "\nNo solution found.\n";
                return;
            }
        }

        if (row == 0 && col == 0 && num == 8) {
            cout << "\nExiting...\n";
            return;
        }

        if (row == 0 && col == 0 && num == 0) {
            cout << "\nExiting the game.\n";
            break; // Exit the game loop
        }

        if (row < 1 || row > GRID_SIZE || col < 1 || col > GRID_SIZE || num < 1 || num > 9) {
            cout << "Invalid input! Try again.\n";
            continue;
        }

        if (grid[row - 1][col - 1] != 0) {
            cout << "Cell is already filled! Try another.\n";
            continue;
        }

        if (!isSafe(grid, row - 1, col - 1, num)) {
            cout << "Invalid move! Try another number.\n";
            continue;
        }

        grid[row - 1][col - 1] = num;
        cout << "\nUpdated Grid:\n";
        printGrid(grid);
        attempts++;
    }

    timeElapsed = timer();
    if (checkSolution(grid)) {
        cout << "\nCongratulations! You've solved the puzzle in " << attempts << " attempts and " << timeElapsed << " seconds!\n";
    }
    else {
        cout << "\nThe solution is incorrect. Try again or give up.\n";
    }
}

void displayScoreboard(vector<int>& times) {
    if (times.empty()) {
        cout << "No completed games yet.\n";
        return;
    }
    cout << "Previous game times: ";
    for (int time : times) {
        cout << time << "s ";
    }
    cout << endl;
}

void displayStatistics(const vector<int>& times) {
    cout << "Game Statistics:\n";
    if (times.empty()) {
        cout << "No completed games yet.\n";
    }
    else {
        cout << "Previous game times: ";
        for (int time : times) {
            cout << time << "s ";
        }
        cout << "\nAverage time: " << accumulate(times.begin(), times.end(), 0) / times.size() << "s\n";
    }
}



int main() {
    int playAgain = 1;
    vector<int> gameTimes;

    while (playAgain == 1) {
        int grid[GRID_SIZE][GRID_SIZE];
        int difficulty;

        cout << "Select difficulty (1: Easy, 2: Medium, 3: Hard): ";
        cin >> difficulty;

        if (difficulty < 1 || difficulty > 3) {
            cout << "Invalid difficulty level. Exiting...\n";
            return 1;
        }

        generateSudoku(grid, difficulty);
        printGrid(grid);
        cout << "Let's play Sudoku!\n";

        auto start = high_resolution_clock::now(); // Start the timer
        playGame(grid, difficulty, gameTimes); // Passing gameTimes to store time taken
        auto stop = high_resolution_clock::now(); // Stop the timer

        int timeElapsed = duration_cast<seconds>(stop - start).count();
        gameTimes.push_back(timeElapsed);

        displayStatistics(gameTimes);

        cout << "New Game? (1: Yes, 0: No): ";
        cin >> playAgain;
    }

    return 0;
}