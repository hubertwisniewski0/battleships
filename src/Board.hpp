//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_BOARD_HPP
#define BATTLESHIPS_BOARD_HPP

#include <SDL.h>
#include "Game.hpp"
#include "MessageService.hpp"

class Board {
private:
    SDL_Surface *board = nullptr;
public:
    explicit Board(MessageService *messageService);

    ~Board();

    void update(Game::Position position, Game::FieldType fieldType);

    void draw(SDL_Surface *target, uint16_t x, uint16_t y);
};

#endif //BATTLESHIPS_BOARD_HPP
