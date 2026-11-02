#include <iostream>
#include <vector>
using namespace std;

int n;
int solutionCount = 0;
vector<int> queenColumn; // queenColumn[row] mein us row ki queen ka column hai.
vector<bool> usedColumn, usedDiagonalDown, usedDiagonalUp;

void printBoard() {
    ++solutionCount;
    cout << "\nSolution " << solutionCount << ":\n";
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col)
            cout << (queenColumn[row] == col ? "Q " : ". ");
        cout << '\n';
    }
}

void placeQueen(int row) {
    if (row == n) {
        printBoard();
        return;
    }

    // Har column try karo; occupied column/diagonal par queen nahi rakh sakte.
    for (int col = 0; col < n; ++col) {
        int downDiagonal = row - col + n - 1;
        int upDiagonal = row + col;
        if (usedColumn[col] || usedDiagonalDown[downDiagonal] || usedDiagonalUp[upDiagonal])
            continue;

        queenColumn[row] = col;
        usedColumn[col] = usedDiagonalDown[downDiagonal] = usedDiagonalUp[upDiagonal] = true;
        placeQueen(row + 1);
        // Backtracking: is placement ko hata kar agla column try karte hain.
        usedColumn[col] = usedDiagonalDown[downDiagonal] = usedDiagonalUp[upDiagonal] = false;
        queenColumn[row] = -1;
    }
}

int main() {
    int firstQueenColumn;
    cout << "Enter the board size N: ";
    if (!(cin >> n) || n <= 0 || n > 15) {
        cerr << "N must be between 1 and 15.\n";
        return 1;
    }
    cout << "Enter the fixed column for the first queen (row 1, from 1 to N): ";
    if (!(cin >> firstQueenColumn) || firstQueenColumn < 1 || firstQueenColumn > n) {
        cerr << "The column must be between 1 and N.\n";
        return 1;
    }

    queenColumn.assign(n, -1);
    usedColumn.assign(n, false);
    usedDiagonalDown.assign(2 * n - 1, false);
    usedDiagonalUp.assign(2 * n - 1, false);

    // Pehli queen user ke diye hue column mein pehle se placed hai.
    int col = firstQueenColumn - 1;
    queenColumn[0] = col;
    usedColumn[col] = true;
    usedDiagonalDown[n - 1 - col] = true;
    usedDiagonalUp[col] = true;

    placeQueen(1); // Ab baaki rows mein backtracking se queens place karo.
    if (solutionCount == 0)
        cout << "No solution exists with this fixed first-queen position.\n";
    else
        cout << "\nTotal solutions: " << solutionCount << '\n';
    return 0;
}
