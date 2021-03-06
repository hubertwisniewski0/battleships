//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GAME_HPP
#define BATTLESHIPS_GAME_HPP

#include <cstdint>
#include <unordered_map>
#include <random>
#include "General.hpp"

class Game {
public:
    enum class FieldType {
        Empty,
        Ship,
        Miss,
        Hit,
        Sunk
    };

    enum class ShootingResult {
        Invalid,
        Miss,
        Hit,
        Sunk
    };

    enum class BoardOwner {
        Player,
        Enemy
    };

    struct Position {
        uint8_t x;
        uint8_t y;
    };

private:
    std::unordered_map<BoardOwner, std::array<std::array<FieldType, boardSize>, boardSize>> boards;
    std::random_device rd;
    std::minstd_rand rng;

    void clearBoards();

    void generateBoards();

    bool sunk(BoardOwner boardOwner, Position position, Position prevPosition, bool mark);

    bool tryPlaceShip(BoardOwner boardOwner, Position position, bool vertical, uint8_t length);

    inline bool sunk(BoardOwner boardOwner, Position position, bool mark) {
        return sunk(boardOwner, position, position, mark);
    }

    inline void setField(BoardOwner boardOwner, Position position, FieldType fieldType) {
        boards[boardOwner][position.x][position.y] = fieldType;
    }

public:
    void newGame();

    Game();

    ShootingResult shot(BoardOwner boardOwner, Position position);

    FieldType getField(BoardOwner boardOwner, Position position);

    FieldType getFieldObscured(BoardOwner boardOwner, Position position);

    bool victory(BoardOwner boardOwner);

    static bool positionWithinLimits(Position position);
};

#endif //BATTLESHIPS_GAME_HPP
