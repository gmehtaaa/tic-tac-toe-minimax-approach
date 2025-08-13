#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct BoardPosition {
    vector<char> board;                    // 9-element board
    vector<BoardPosition> nextPositions;   // possible next positions
    int rating;                            // evaluation score
};

// Utility to print the board
void printBoard(const vector<char>& board) {
    for (int i = 0; i < 9; i++) {
        cout << (board[i] == ' ' ? '.' : board[i]) << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

// Check if a player has won
bool isWin(const vector<char>& board, char player) {
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    for (auto& p : winPatterns) {
        if (board[p[0]] == player &&
            board[p[1]] == player &&
            board[p[2]] == player)
            return true;
    }
    return false;
}

// Check if the board is full
bool isDraw(const vector<char>& board) {
    for (char c : board)
        if (c == ' ') return false;
    return true;
}

// Generate all next positions for the given player
void generateNextPositions(BoardPosition& pos, char player) {
    pos.nextPositions.clear();
    for (int i = 0; i < 9; i++) {
        if (pos.board[i] == ' ') {
            BoardPosition nextPos;
            nextPos.board = pos.board;
            nextPos.board[i] = player;
            pos.nextPositions.push_back(nextPos);
        }
    }
}

// Recursive minimax evaluation based on the Program 3 description
int evaluatePosition(BoardPosition& pos, char currentPlayer) {
    // Step 1: If it's a win for someone, assign rating
    if (isWin(pos.board, 'X')) {
        pos.rating = 1;  // Human wins
        return pos.rating;
    }
    if (isWin(pos.board, 'O')) {
        pos.rating = -1; // Computer wins
        return pos.rating;
    }
    if (isDraw(pos.board)) {
        pos.rating = 0;  // Draw
        return pos.rating;
    }

    // Step 2: Generate next positions
    generateNextPositions(pos, currentPlayer);

    if (currentPlayer == 'X') {
        // Human (maximizing)
        int bestRating = numeric_limits<int>::min();
        for (auto& nextPos : pos.nextPositions) {
            int rating = evaluatePosition(nextPos, 'O');
            bestRating = max(bestRating, rating);
        }
        pos.rating = bestRating;
    } else {
        // Computer (minimizing)
        int bestRating = numeric_limits<int>::max();
        for (auto& nextPos : pos.nextPositions) {
            int rating = evaluatePosition(nextPos, 'X');
            bestRating = min(bestRating, rating);
        }
        pos.rating = bestRating;
    }
    return pos.rating;
}

// Choose best move for Computer (O)
int findBestMove(BoardPosition& pos) {
    generateNextPositions(pos, 'O');
    int bestRating = numeric_limits<int>::max();
    int bestIndex = -1;

    for (int i = 0; i < pos.nextPositions.size(); i++) {
        evaluatePosition(pos.nextPositions[i], 'X');
        if (pos.nextPositions[i].rating < bestRating) {
            bestRating = pos.nextPositions[i].rating;
            bestIndex = i;
        }
    }

    if (bestIndex != -1) {
        pos.board = pos.nextPositions[bestIndex].board;
    }
    return bestIndex;
}

int main() {
    BoardPosition game;
    game.board = vector<char>(9, ' ');

    cout << "Tic Tac Toe - You (X) vs Computer (O)\n";
    printBoard(game.board);

    while (true) {
        // Human move
        int humanMove;
        cout << "Enter your move (0-8): ";
        cin >> humanMove;
        if (humanMove < 0 || humanMove > 8 || game.board[humanMove] != ' ') {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        game.board[humanMove] = 'X';

        if (isWin(game.board, 'X')) {
            printBoard(game.board);
            cout << "You win!\n";
            break;
        }
        if (isDraw(game.board)) {
            printBoard(game.board);
            cout << "It's a draw!\n";
            break;
        }

        // Computer move
        cout << "Computer thinking...\n";
        findBestMove(game);
        printBoard(game.board);

        if (isWin(game.board, 'O')) {
            cout << "Computer wins!\n";
            break;
        }
        if (isDraw(game.board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
