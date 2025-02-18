#include <random>
#include "../hpp/board.hpp"

GameBoard::GameBoard() : GameBoard(0, 0, 0) {}

GameBoard::GameBoard(size_t row, size_t col, size_t mine_count) {
    reload_game(row, col, mine_count);
}

void GameBoard::reload_game(size_t row, size_t col, size_t mine_count) {
    this->row = row;
    this->col = col;
    this->mine_count = mine_count;

    board = std::vector(row, std::vector(col, 0));

    fill_bombs();
    proccess_counts();
    close_all_cells();  
}


void GameBoard::fill_bombs() {
    int mines = mine_count;

    std::random_device dev;
    std::mt19937 ran(dev());

    std::uniform_int_distribution<size_t> rand_row(0, row - 1);
    std::uniform_int_distribution<size_t> rand_col(0, col - 1);

    while (mines > 0) {
        size_t i = rand_row(ran);
        size_t j = rand_col(ran);

        if (board[i][j] != -1) {
            board[i][j] = -1;
            --mines;
        }
    }
}



void GameBoard::proccess_counts() {

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            if (board[i][j] == 0) {
                for (int l = std::max(int(i-1),0); l <= std::min(i+1,row-1); ++l) {
                    for (int m = std::max(int(j-1),0); m <= std::min(j+1,col-1); ++m) {
                        if (board[l][m] == -1) {
                            ++board[i][j];
                        }
                    }
                }
            }
        }
    }    
}

void GameBoard::close_all_cells() {

    for (auto& row : board) {
        for (auto& col : row) {
            col += 100;
        }
    }
}

void GameBoard::open_all_cells() {

    for (auto& row : board) {
        for (auto& col : row) {
            if (col > 10) {
                col -= 100;
            }
        }
    }
}


void GameBoard::open_cell_helper(size_t i, size_t j) {

    if (i >= row || j >= col) {
        return;
    }

    if (board[i][j] >= -1 && board[i][j] <= 8) {
        return;
    }

    if (board[i][j] >= 101 && board[i][j] <= 108) {
        board[i][j] -= 100;
        ++opened_count;
        return;
    }

    board[i][j] -= 100;
    ++ opened_count;
    for (int l = std::max(int(i-1),0); l <= i + 1; ++l) {
        for (int m = std::max(int(j-1),0); m <= j + 1; ++m) {
            open_cell_helper(l, m);
        }
    }    
}

GameBoard::Status GameBoard::open_cell(size_t i, size_t j) {

    if (i >= row || j >= col) {
        return Status::Fail;
    }

    if (board[i][j] == 99) {
        open_all_cells();
        return Status::GameOver;
    }

    if (board[i][j] >= 0 && board[i][j] <= 8) {
        return Status::Fail;
    }

    open_cell_helper(i, j);

    if (row * col == mine_count + opened_count) {
        open_all_cells();
        return Status::Victory;
    }
    
    return Status::Success;
}