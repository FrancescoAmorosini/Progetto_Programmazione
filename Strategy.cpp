//
// Created by francesco amorosini on 24/10/16.
//

#include "Strategy.h"

void ChaseHero::movementBehavior(PlayableCharacter* hero, Enemy* enemy) {
    if(enemy->walkingTime.getElapsedTime().asSeconds() > 0.3) {
        float Ydiff = hero->rect.getPosition().y - enemy->rect.getPosition().y;
        float Xdiff = hero->rect.getPosition().x - enemy->rect.getPosition().x;

        if (abs(static_cast<int>(Ydiff)) < Xdiff && Xdiff > 0) {
            enemy->face = Face::Right;
            if (!enemy->canMoveRIGHT) {
                if (enemy->canMoveUP)
                    enemy->face = Face::Up;
                else if (enemy->canMoveDOWN)
                    enemy->face = Face::Down;
            }
        }
        if (abs(static_cast<int>(Xdiff)) < Ydiff && Ydiff > 0) {
            enemy->face = Face::Down;
            if (!enemy->canMoveDOWN) {
                if (enemy->canMoveRIGHT)
                    enemy->face = Face::Right;
                else if (enemy->canMoveLEFT)
                    enemy->face = Face::Left;
            }
        }
        if (abs(static_cast<int>(Ydiff)) < abs(static_cast<int>(Xdiff)) && Xdiff < 0) {
            enemy->face = Face::Left;
            if (!enemy->canMoveLEFT) {
                if (enemy->canMoveDOWN)
                    enemy->face = Face::Down;
                else if (enemy->canMoveUP)
                    enemy->face = Face::Up;
            }
        }
        if (abs(static_cast<int>(Xdiff)) < abs(static_cast<int>(Ydiff)) && Ydiff < 0) {
            enemy->face = Face::Up;
            if (!enemy->canMoveUP) {
                if (enemy->canMoveRIGHT)
                    enemy->face = Face::Right;
                else if (enemy->canMoveLEFT)
                    enemy->face = Face::Left;
            }
        }
    }

    if(enemy->walkingTime.getElapsedTime().asSeconds()>0.3)
        enemy->walkingTime.restart();
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

    if(abs(static_cast<int>(hero->rect.getPosition().x - enemy->rect.getPosition().x)) < 50 &&
            abs(static_cast<int>(hero->rect.getPosition().y - enemy->rect.getPosition().y)) < 50)
        enemy->setAggroed(true);
}

void Flee::movementBehavior(PlayableCharacter* hero, Enemy* enemy) {
    enemy->setAggroed(false);

    if(enemy->walkingTime.getElapsedTime().asSeconds() < 0.5) {
        float Ydiff = hero->rect.getPosition().y - enemy->rect.getPosition().y;
        float Xdiff = hero->rect.getPosition().x - enemy->rect.getPosition().x;

        if (abs(static_cast<int>(Ydiff)) < Xdiff && Xdiff > 0) {
            enemy->face = Face::Left;
            if (!enemy->canMoveLEFT) {
                if (enemy->canMoveUP)
                    enemy->face = Face::Up;
                else if (enemy->canMoveDOWN)
                    enemy->face = Face::Down;
            }
        }
        if (abs(static_cast<int>(Xdiff)) < Ydiff && Ydiff > 0) {
            enemy->face = Face::Up;
            if (!enemy->canMoveUP) {
                if (enemy->canMoveRIGHT)
                    enemy->face = Face::Right;
                else if (enemy->canMoveLEFT)
                    enemy->face = Face::Left;
            }
        }
        if (abs(static_cast<int>(Ydiff)) < abs(static_cast<int>(Xdiff)) && Xdiff < 0) {
            enemy->face = Face::Right;
            if (!enemy->canMoveRIGHT) {
                if (enemy->canMoveDOWN)
                    enemy->face = Face::Down;
                else if (enemy->canMoveUP)
                    enemy->face = Face::Up;
            }
        }
        if (abs(static_cast<int>(Xdiff)) < abs(static_cast<int>(Ydiff)) && Ydiff < 0) {
            enemy->face = Face::Down;
            if (!enemy->canMoveDOWN) {
                if (enemy->canMoveRIGHT)
                    enemy->face = Face::Right;
                else if (enemy->canMoveLEFT)
                    enemy->face = Face::Left;
            }
        }
    }

    if(enemy->walkingTime.getElapsedTime().asSeconds()>0.5)
        enemy->walkingTime.restart();
}
