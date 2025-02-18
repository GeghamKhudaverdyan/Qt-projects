#include <iostream>
#include <vector>
#include <iomanip>
#include "../hpp/logger.hpp"

Logger::Logger(const GameBoard& b) : game_board{b} {}

std::string Logger::get_symbol(int val) const {

    switch (val) {
        case -1:
            return "🧨";
        case 0:
            return "⬛";
        case 1:
            return "1️⃣ ";
        case 2:
            return "2️⃣ ";
        case 3:
            return "3️⃣ ";
        case 4:
            return "4️⃣ ";
        case 5:
            return "5️⃣ ";
        case 6:
            return "6️⃣ ";
        case 7:
            return "7️⃣";
        case 8:
            return "8️⃣";
        default:
            return "⬜";
    }
}

void Logger::print() const {

    system("clear");
    size_t row = game_board.get_row();
    size_t col = game_board.get_col();
    const std::vector<std::vector<int>>& board = game_board.get_board();

    std::cout << "   ";
    for (size_t i = 0; i < col; ++i) {
        std::cout << std::setw(2) << std::left << i << " ";
    }
    std::cout << std::endl;
    
    for (size_t i = 0; i < row; ++i) {
        std::cout << std::setw(2) << std::right << i << " ";
        for (size_t j = 0; j < col; ++j) {
            std::cout << std::setw(2) << std::left << get_symbol(board[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Logger::game_over() const {

    std::cout << 
    R"(
    ****************
    **** LOOSER ****
    ****************
    )" 
    << std::endl;    
}

void Logger::victory() const {

    std::cout << 
    R"(
    *****************
    **** !LOOSER ****
    *****************
    )" 
    << std::endl;    }

void Logger::fail() const {

    std::cout << 
    R"(
    **** wrong cordinates ****
    )" 
    << std::endl;
}

void Logger::new_game_request() const {

    std::cout << 
    R"(
    Game is over: Start new game: y ? n
    )" 
    << std::endl;
    
}

void Logger::choose_difficulty() const {

    system("clear");
    std::cout << 
    R"(
    Choose game Difficulty: 0 [easy] ? 1 [medium] ? 2 [hard]
    )" 
    << std::endl;
    
}

void Logger::good_bye() const {

    std::cout << 
    R"(
    *****************************
            See you again
    )" 
    << std::endl;
    
    
}