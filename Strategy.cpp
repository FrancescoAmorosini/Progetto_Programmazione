//
// Created by francesco amorosini on 24/10/16.
//

#include "Strategy.h"

void ChaseHero::movementBehavior(PlayableCharacter* hero, Enemy* enemy) {
    // CHASE DOWN
    if (hero->rect.getPosition().y > enemy->rect.getPosition().y &&
        abs(static_cast<int>(hero->rect.getPosition().x - enemy->rect.getPosition().x)) <= 32) {
        if(enemy->canMoveDOWN)
            enemy->face = Face::Down;
        else if(enemy->canMoveRIGHT)
            enemy->face = Face::Right;
        else if(enemy->canMoveLEFT)
            enemy->face = Face::Left;
    }
        //CHASE RIGHT
    else if ((hero->rect.getPosition().x > enemy->rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - enemy->rect.getPosition().y)) <= 32)) {
        if (enemy->canMoveRIGHT)
            enemy->face = Face::Right;
        else if (enemy->canMoveUP)
            enemy->face = Face::Up;
        else if (enemy->canMoveDOWN)
            enemy->face = Face::Down;
    }
        //CHASE LEFT
    else if ((hero->rect.getPosition().x < enemy->rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - enemy->rect.getPosition().y)) <= 32)) {
        if (enemy->canMoveLEFT)
            enemy->face = Face::Left;
        else if (enemy->canMoveDOWN)
            enemy->face = Face::Down;
        else if (enemy->canMoveUP)
            enemy->face = Face::Up;
    }
        //CHASE UP
    else if ((hero->rect.getPosition().y < enemy->rect.getPosition().y) &&
             (abs(static_cast<int>(hero->rect.getPosition().x - enemy->rect.getPosition().x)) <= 32)) {
        if (enemy->canMoveUP)
            enemy->face = Face::Up;
        else if (enemy->canMoveLEFT)
            enemy->face = Face::Left;
        else if (enemy->canMoveRIGHT)
            enemy->face = Face::Right;
    }
}

void TurnAround::movementBehavior(PlayableCharacter* hero, Enemy* enemy) {
    if (enemy->walkingTime.getElapsedTime().asSeconds() >= 0.5) {
        //Changes facing direction
        bool ammitted = false;
        while (!ammitted) {
            enemy->face = static_cast<Face>(RNG::throwDice(9) - 1);

            switch (enemy->face) {
                case Face::Down:
                    if (enemy->canMoveDOWN)
                        ammitted = true;
                    break;
                case Face::Up:
                    if (enemy->canMoveUP)
                        ammitted = true;
                    break;

                case Face::Left:
                    if (enemy->canMoveLEFT)
                        ammitted = true;
                    break;

                case Face::Right:
                    if (enemy->canMoveDOWN)
                        ammitted = true;
                    break;

            }
            enemy->walkingTime.restart();
        }
    }
}

void Flee::movementBehavior(PlayableCharacter* hero, Enemy* enemy) {
    // FLEE UP
    if (hero->rect.getPosition().y > enemy->rect.getPosition().y &&
        abs(static_cast<int>(hero->rect.getPosition().x - enemy->rect.getPosition().x)) <= 32) {
        if(enemy->canMoveUP)
            enemy->face = Face::Up;
        else if(enemy->canMoveRIGHT)
            enemy->face = Face::Right;
        else if(enemy->canMoveLEFT)
            enemy->face = Face::Left;
    }
        //FLEE LEFT
    else if ((hero->rect.getPosition().x > enemy->rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - enemy->rect.getPosition().y)) <= 32)) {
        if (enemy->canMoveLEFT)
            enemy->face = Face::Left;
        else if (enemy->canMoveUP)
            enemy->face = Face::Up;
        else if (enemy->canMoveDOWN)
            enemy->face = Face::Down;
    }
        //FLEE RIGHT
    else if ((hero->rect.getPosition().x < enemy->rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - enemy->rect.getPosition().y)) <= 32)) {
        if (enemy->canMoveRIGHT)
            enemy->face = Face::Right;
        else if (enemy->canMoveDOWN)
            enemy->face = Face::Down;
        else if (enemy->canMoveUP)
            enemy->face = Face::Up;
    }
        //FLEE DOWN
    else if ((hero->rect.getPosition().y < enemy->rect.getPosition().y) &&
             (abs(static_cast<int>(hero->rect.getPosition().x - enemy->rect.getPosition().x)) <= 32)) {
        if (enemy->canMoveDOWN)
            enemy->face = Face::Down;
        else if (enemy->canMoveLEFT)
            enemy->face = Face::Left;
        else if (enemy->canMoveRIGHT)
            enemy->face = Face::Right;
    }
}
