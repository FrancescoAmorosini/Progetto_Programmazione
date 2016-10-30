//
// Created by francesco amorosini on 24/10/16.
//

#include "Enemy.h"


void Enemy::move() {
    //moves in the choosen direction
    int race=0;
    if(getRole() == CharacterClass::Witch)
        race=3;
    if(getRole() == CharacterClass::BigBaldGuy)
        race=6;
    if(getRole() == CharacterClass::Undead)
        race=9;
        switch (face) {
            case Face::Up:
                rect.move(0, -speed);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race + 5, 32 * 3, 32, 32));
                break;
            case Face::Down:
                rect.move(0, speed);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race + 5, 0, 32, 32));
                break;
            case Face::Left:
                rect.move(-speed, 0);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race + 5, 32 * 1, 32, 32));
                break;
            case Face::Right:
                rect.move(speed, 0);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race + 5, 32 * 2, 32, 32));
                break;
        }
    updatePosition();
}
void Enemy::turnAround(PlayableCharacter* hero) {
    if (aggroed)
        chaseHero(hero);
        // 1/2 chance of moving in a random direction if not aggroed
    else if (walkingTime.getElapsedTime().asSeconds() >= 0.5){
        //Changes facing direction
        face = static_cast<Face>(RNG::throwDice(9) - 1);
        walkingTime.restart();
    }
}

void Enemy::chaseHero(PlayableCharacter *hero) {
    // CHASE DOWN
    if (hero->rect.getPosition().y > rect.getPosition().y &&
        abs(static_cast<int>(hero->rect.getPosition().x - rect.getPosition().x)) <= 32)
        face = Face::Down;
        //CHASE UP
    else if ((hero->rect.getPosition().x > rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - rect.getPosition().y)) <= 32))
        face = Face::Right;
        //CHASE LEFT
    else if ((hero->rect.getPosition().x < rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - rect.getPosition().y)) <= 32))
        face = Face::Left;
        //CHASE UP
    else if ((hero->rect.getPosition().y < rect.getPosition().y) &&
             (abs(static_cast<int>(hero->rect.getPosition().x - rect.getPosition().x)) <= 32))
        face = Face::Up;

}

Spell* Enemy::shootSpell() {
    //if witch && aggroed enemy has chance of shooting a spell each 2 seconds
    if(RNG::throwCoin(120) && getRole() == CharacterClass::Witch && aggroed) {
        return new Spell(rect.getPosition().x + rect.getSize().x / 2 - 13,    //13= Half Spell Sprite
                         rect.getPosition().y + rect.getSize().y / 2 - rect.getSize().y / 2,
                         face);
    }
    else
        return nullptr;
}
