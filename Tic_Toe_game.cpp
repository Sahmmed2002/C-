#include <iostream>
using namespace std;

char board[3][3];           // 3x3 board
char currentPlayer = 'X';   // Starting player

// Function to initialize the board with spaces
void initializeBoard() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
}

// Function to display the board
void displayBoard() {
    cout << "\n  1   2   3\n";
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n ---+---+---\n";
    }
    cout << "\n\n";
}

// Check if a player has won
bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer &&
                board[1][i] == currentPlayer &&
                board[2][i] == currentPlayer)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer &&
            board[1][1] == currentPlayer &&
            board[2][0] == currentPlayer)) {
        return true;
    }
    return false;
}

// Check for a draw
bool checkDraw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// Function to switch player
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Handle a player's move
void playerMove() {
    int row, col;
    while (true) {
        cout << "Player " << currentPlayer << ", enter your move (row and column: 1-3): ";
        cin >> row >> col;

        if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
            if (board[row - 1][col - 1] == ' ') {
                board[row - 1][col - 1] = currentPlayer;
                break;
            }
            else {
                cout << "❌ Cell already taken. Try again.\n";
            }
        }
        else {
            cout << "❌ Invalid input. Please enter numbers between 1 and 3.\n";
        }
    }
}

// Main function
int main() {
    initializeBoard();
    displayBoard();

    while (true) {
        playerMove();
        displayBoard();

        if (checkWin()) {
            cout << "🎉 Player " << currentPlayer << " wins!\n";
            break;
        }

        if (checkDraw()) {
            cout << "🤝 It's a draw!\n";
            break;
        }

        switchPlayer();
    }

    return 0;
}
