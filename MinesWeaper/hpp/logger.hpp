#ifndef __LOGGER__
#define __LOGGER__

#include <string>
#include <vector>

#include "board.hpp"

class Logger {

    const GameBoard& game_board;

public:
    Logger(const GameBoard& b);

    void print() const;
    void game_over() const;
    void victory() const;
    void fail() const;
    void new_game_request() const;
    void choose_difficulty() const;
    void good_bye() const;

private:
    std::string get_symbol(int val) const;
};

#endif //__LOGGER__