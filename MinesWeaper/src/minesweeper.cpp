#include "../hpp/minesweeper.hpp"
#include "../hpp/board.hpp"
#include <cstdlib>
#include <iostream>

MinesWeeper::MinesWeeper() : game_board{}, logger{game_board} {
    start_new_game();
}

void MinesWeeper::start_new_game() {
    logger.choose_difficulty();

    int diff;
    std::cin >> diff;

    Dificulty arr[] = {Dificulty::Easy, Dificulty::Medium, Dificulty::Hard};

    switch (arr[diff]) {
        case Dificulty::Easy:
            game_board.reload_game(9, 9, 10);
        case Dificulty::Medium:
            game_board.reload_game(12, 12, 25);
        case Dificulty::Hard:
            game_board.reload_game(16, 16, 40);
    }
  
    logger.print();
}

void MinesWeeper::run() {
    while (true) {
        size_t i{};
        size_t j{};

        bool game_over = false;

        std::cin >> i >> j;

        GameBoard::Status status = game_board.open_cell(i, j);

        if (status == GameBoard::Status::Fail) {
            logger.fail();
            continue;
        }
        
        logger.print();
        if (status == GameBoard::Status::GameOver) {
            logger.game_over();
            game_over = true;
        }
        if (status == GameBoard::Status::Victory) {
            logger.victory();
            game_over = true;
        }

        if (game_over) {
            logger.new_game_request();

            char sym;
            std::cin >> sym;

            if ((sym | 32) == 'y') {
                start_new_game();
            }
            else {
                logger.good_bye();
                return;
            }
        }
    }
}