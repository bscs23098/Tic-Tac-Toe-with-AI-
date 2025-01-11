#include<iostream>
using namespace std;
const int SIZE = 3;

void initialize_move(char board[SIZE][SIZE], int row, int column) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            board[i][j] = '-';
        }
    }
}

void display_board(char board[SIZE][SIZE], int row, int column) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (j == column - 1) {
                cout << board[i][j];
            }
            else {
                cout << board[i][j] << " |";
            }
        }
        cout << endl;
        if (i < row - 1) {
            cout << "--------" << endl;
        }
    }
    cout << endl << endl << endl;
}

void player_turn(bool& turn) {
    if (turn) {
        cout << "Player 2 should enter (r,c): ";
        turn = false;
    }
    else {
        cout << "Player 1 should neter (r,c): ";
        turn = true;
    }
}

bool CheckDraw(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

bool winner(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-') {
            return true;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-') {
            return true;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-') {
        return true;
    }
    return false;
}

bool valid_move(char board[SIZE][SIZE], int rows, int column) {
    if (rows >= 0 && rows < SIZE && column >= 0 && column < SIZE) {
        if (board[rows][column] == '-') {
            return true;
        }
    }
    return false;
}

void MakeMove(char board[3][3], char player, int row, int col) {
    board[row][col] = player;
}

bool Replay(char board[3][3]) {
    char choice;
    cout << "Do you want to play again (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        initialize_move(board, SIZE, SIZE);
        return true;
    }
    else {
        return false;
    }
}


bool wining_move(char board[SIZE][SIZE], char player, int rows, int column) {
    board[rows][column] = player;
    bool win = winner(board);
    board[rows][column] = '-';
    return win;
}

void  computerMove(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (valid_move(board, i, j) && wining_move(board, 'O', i, j) ){
                MakeMove(board, 'O', i, j);
                return;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (valid_move(board, i, j) && wining_move(board, 'X', i, j)) {
                MakeMove(board, 'O', i, j);
                return;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (valid_move(board, i, j)) {
                        MakeMove(board, 'O', i, j);
                        return;
                    }
                }
            }
}

int main() {
    const int size = 3;
    char board[size][size];
    char player;
    bool turn;
    int rows, column;
    bool gameOver;

    do {
        initialize_move(board, size, size);
        gameOver = false;
        turn = 0;

        while (!gameOver) {
            display_board(board, size, size);

            if (turn == 0) {
                cout << "Enter row and colum: ";
                cin >> rows >> column;
                if (valid_move(board, rows, column)) {
                    MakeMove(board, 'X', rows, column);
                }
                else {
                    cout << "Invald move. Try again: ";
                    continue;
                }
            }
            else {
                computerMove(board);
                cout << "Computer made its move." << endl;
            }

            if (winner(board)) {
                display_board(board, size, size);
                cout << (turn == 0 ? "Human wins" : "Comuter wins") << endl;
                gameOver = true;
            }
            else if (CheckDraw(board)) {
                display_board(board, size, size);
                cout << "The game is  draw" << endl;
                gameOver = true;
            }

            turn = 1 - turn;
        }
    } while (Replay(board));

    cout << "Thank you for playng" << endl;

    return 0;
}