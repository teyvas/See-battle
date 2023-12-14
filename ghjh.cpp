#include <iostream>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 7;
const int SHIP_LENGTHS[] = {3, 2, 2, 1, 1, 1, 1};
const char SHIP_SYMBOL = 'S';
const char EMPTY_CELL = 'O';
const char HIT_CELL = 'X';
const char MISS_CELL = '-';

char playerBoard[BOARD_SIZE][BOARD_SIZE];
char computerBoard[BOARD_SIZE][BOARD_SIZE];

void clearScreen() {
    system("cls");
}

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = EMPTY_CELL;
        }
    }
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "   A B C D E F G\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isValidPosition(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool isAdjacent(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (isValidPosition(board, x + i, y + j) && board[y + j][x + i] == SHIP_SYMBOL) {
                return true;
            }
        }
    }
    return false;
}

bool placeShip(char board[BOARD_SIZE][BOARD_SIZE], int size) {
    std::string orientation = (rand() % 2 == 0) ? "horizontal" : "vertical";
    int x, y;

    if (orientation == "horizontal") {
        x = rand() % (BOARD_SIZE - size + 1);
        y = rand() % BOARD_SIZE;
    } else {
        x = rand() % BOARD_SIZE;
        y = rand() % (BOARD_SIZE - size + 1);
    }

    if (isAdjacent(board, x, y)) {
        return false;
    }

    if (orientation == "horizontal") {
        for (int i = x; i < x + size; ++i) {
            if (board[y][i] != EMPTY_CELL) {
                return false;
            }
        }
        for (int i = x; i < x + size; ++i) {
            board[y][i] = SHIP_SYMBOL;
        }
    } else {
        for (int i = y; i < y + size; ++i) {
            if (board[i][x] != EMPTY_CELL) {
                return false;
            }
        }
        for (int i = y; i < y + size; ++i) {
            board[i][x] = SHIP_SYMBOL;
        }
    }
    return true;
}

void placeShips(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < sizeof(SHIP_LENGTHS) / sizeof(SHIP_LENGTHS[0]); ++i) {
        while (true) {
            if (placeShip(board, SHIP_LENGTHS[i])) {
                break;
            }
        }
    }
}

void updateBoard(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    if (board[y][x] == SHIP_SYMBOL) {
        board[y][x] = HIT_CELL;
    } else {
        board[y][x] = MISS_CELL;
    }
}

bool checkGameOver(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == SHIP_SYMBOL) {
                return false;
            }
        }
    }
    return true;
}

void playGame() {
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "Welcome to Battleship!\n";
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    int shots = 0;

    initializeBoard(playerBoard);
    initializeBoard(computerBoard);
    placeShips(computerBoard);

    while (true) {
        clearScreen();
        std::cout << "Player: " << playerName << "\n";
        std::cout << "Your Board:\n";
        printBoard(playerBoard);

        int x, y;
        while (true) {
            char xInput;
            std::cout << "\nEnter X coordinate (A-G): ";
            std::cin >> xInput;
            x = toupper(xInput) - 'A';
            std::cout << "Enter Y coordinate (1-7): ";
            std::cin >> y;
            y--;

            if (isValidPosition(playerBoard, x, y) && playerBoard[y][x] != HIT_CELL && playerBoard[y][x] != MISS_CELL) {
                break;
            } else {
                std::cout << "Invalid input or already shot at this location. Try again.\n";
            }
        }

        shots++;
        updateBoard(computerBoard, x, y);

        clearScreen();
        std::cout << "Player: " << playerName << "\n";
        if (computerBoard[y][x] == HIT_CELL) {
            std::cout << "Your Board After Your Shot:\n";
            printBoard(playerBoard);
            std::cout << "\nHit!";
        } else {
            std::cout << "Your Board After Your Shot:\n";
            printBoard(playerBoard);
            std::cout << "\nMiss!";
        }

        if (checkGameOver(computerBoard)) {
            std::cout << "\nCongratulations! You sank all the ships!\n";
            std::cout << "You made " << shots << " shots.\n";
            break;
        }

        std::cin.ignore();
        std::cin.get();
    }
}

int main() {
    playGame();
    return 0;
}
