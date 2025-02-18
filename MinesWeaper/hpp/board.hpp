#ifndef __BOARD__
#define __BOARD__

#include <vector>
#include <cstddef>

class MinesWeeper;

class GameBoard {
public:
    enum class Status {Fail, Success, Victory, GameOver};

private:
    std::vector<std::vector<int>> board;
    size_t row;
    size_t col;
    size_t mine_count;
    size_t opened_count;

public:
    GameBoard();
    GameBoard(size_t row, size_t col, size_t mine_count);
    void reload_game(size_t row, size_t col, size_t mine_count);

private:
    void fill_bombs();
    void proccess_counts();
    void close_all_cells();
    void open_all_cells();
    void open_cell_helper(size_t i, size_t j);

public:
    const std::vector<std::vector<int>>& get_board() const {return board;};
    size_t get_mine_count() const {return mine_count;};
    size_t get_row() const {return row;};
    size_t get_col() const {return col;};
    Status open_cell(size_t i, size_t j);
};

#endif //__BOARD__