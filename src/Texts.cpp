//
// Created by hubert25632 on 01.07.22.
//

#include "Texts.hpp"
#include "General.hpp"

Texts::Texts(MessageService *messageService, Text *text) {
    minOffset = text->getMinOffset();
    texts[0] = text->renderText("Player's sea");
    texts[1] = text->renderText("Enemy's sea");
    texts[2] = text->renderText("Player");
    texts[3] = text->renderText("Enemy");
    texts[4] = text->renderText("Victory");
    texts[5] = text->renderText("Miss");
    texts[6] = text->renderText("Hit");
    texts[7] = text->renderText("Sunk");
    for (uint8_t i = 0; i < 8; i++) {
        if (texts[i] == nullptr)
            messageService->showMessage(MessageService::MessageType::Error,
                                        "Rendering text n" + std::to_string((int) i) + std::string(": ") +
                                        std::string(TTF_GetError()));
    }
    char t[2];
    char c[3];
    char w[4];
    for (uint8_t i = 0; i < 10; i++) {
        t[0] = 0x41 + i;
        t[1] = 0;
        letters[i] = text->renderText(t);
        for (uint8_t j = 0; j < 10; j++) {
            if (j < 9) {
                c[0] = 0x31 + j;
                c[1] = 0;
            }
            else {
                c[0] = '1';
                c[1] = '0';
                c[2] = 0;
            }
            if (i == 0) {
                numbers[j] = text->renderText(c);
                if (numbers[j] == nullptr)
                    messageService->showMessage(MessageService::MessageType::Error,
                                                "Rendering text c" + std::to_string((int) j) + std::string(": ") +
                                                std::string(TTF_GetError()));
            }
            w[0] = 0;
            strcat(w, t);
            strcat(w, c);
            readings[i][j] = text->renderText(w);
            if (readings[i][j] == nullptr)
                messageService->showMessage(MessageService::MessageType::Error,
                                            "Rendering text w" + std::to_string((int) i) + std::to_string((int) j) +
                                            std::string(": ") + std::string(TTF_GetError()));
        }
        if (letters[i] == nullptr)
            messageService->showMessage(MessageService::MessageType::Error,
                                        "Rendering text t" + std::to_string((int) i) + std::string(": ") +
                                        std::string(TTF_GetError()));
    }
}

Texts::~Texts() {
    for (uint8_t i = 0; i < 10; i++) {
        if (letters[i] != nullptr)
            SDL_FreeSurface(letters[i]);
        if (numbers[i] != nullptr)
            SDL_FreeSurface(numbers[i]);
        for (uint8_t j = 0; j < 10; j++)
            if (readings[i][j] != nullptr)
                SDL_FreeSurface(readings[i][j]);
    }
    for (auto &text_s: texts)
        if (text_s != nullptr)
            SDL_FreeSurface(text_s);
}

void Texts::draw(SDL_Surface *target) {
    Text::drawText(texts[0], target, 180 - texts[0]->w / 2 + boardXOffset, 15 - texts[0]->h / 2);
    Text::drawText(texts[1], target, 540 - texts[1]->w / 2 + boardXOffset, 15 - texts[1]->h / 2);
    Text::drawText(texts[2], target, 30 + boardXOffset, 375 - texts[2]->h / 2);
    Text::drawText(texts[3], target, 30 + boardXOffset, 375 - texts[3]->h / 2 + minOffset);
    if (playerReading != nullptr)
        Text::drawText(playerReading, target, 90 + boardXOffset, 375 - playerReading->h / 2);
    if (enemyReading != nullptr)
        Text::drawText(enemyReading, target, 90 + boardXOffset, 375 - enemyReading->h / 2 + minOffset);
    if (sPlayer != nullptr)
        Text::drawText(sPlayer, target, 150 + boardXOffset, 375 - sPlayer->h / 2);
    if (sEnemy != nullptr)
        Text::drawText(sEnemy, target, 150 + boardXOffset, 375 - sEnemy->h / 2 + minOffset);
    for (uint8_t i = 0; i < 10; i++) {
        Text::drawText(letters[i], target, 45 + (30 * i) - letters[i]->w / 2 + boardXOffset, 45 - letters[i]->h / 2);
        Text::drawText(letters[i], target, 405 + (30 * i) - letters[i]->w / 2 + boardXOffset, 45 - letters[i]->h / 2);
        Text::drawText(numbers[i], target, 15 - numbers[i]->w / 2 + boardXOffset, 75 + (30 * i) - numbers[i]->h / 2);
        Text::drawText(numbers[i], target, 375 - numbers[i]->w / 2 + boardXOffset, 75 + (30 * i) - numbers[i]->h / 2);
    }
}

void Texts::updateTexts(Game::BoardOwner boardOwner, Game::Position position, Game::ShootingResult shootingResult) {
    (boardOwner == Game::BoardOwner::Player ? playerReading : enemyReading) = readings[position.x][position.y];

    switch (shootingResult) {
        case Game::ShootingResult::Miss: {
            (boardOwner == Game::BoardOwner::Player ? sPlayer : sEnemy) = texts[5];
            break;
        }
        case Game::ShootingResult::Hit: {
            (boardOwner == Game::BoardOwner::Player ? sPlayer : sEnemy) = texts[6];
            break;
        }
        case Game::ShootingResult::Sunk: {
            (boardOwner == Game::BoardOwner::Player ? sPlayer : sEnemy) = texts[7];
            break;
        }
    }
}

void Texts::resetTexts() {
    playerReading = nullptr;
    enemyReading = nullptr;
    sPlayer = nullptr;
    sEnemy = nullptr;
}
