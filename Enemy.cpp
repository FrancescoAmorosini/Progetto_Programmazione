//
// Created by Francesco Amorosini on 22/07/16.
//

#include "Enemy.h"

Enemy::Enemy(float x, float y, CharacterClass role, int HP, int atk, int evade, int critical ) :
        GameCharacter(role,HP,atk,evade,critical) {
    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Cyan);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    text.setString(std::to_string(HP));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Green);

}
void Enemy::updatePosition() {
    int speed = speedMovement - 1;

    switch(face) {
        case Face::Up:
            rect.move(0, -speed);
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32, 32 * 3, 32, 32));
            break;
        case Face::Down:
            rect.move(0, speed);
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32, 0, 32, 32));
            break;
        case Face::Left:
            rect.move(-speed, 0);
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32, 32 * 1, 32, 32));
            break;
        case Face::Right:
            rect.move(speed, 0);
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32, 32 * 2, 32, 32));
            break;
        }

    sprite.setPosition(rect.getPosition());
    text.setPosition(rect.getPosition().x, rect.getPosition().y -30);
    text.setString(std::to_string(getHP()));
    if(getHP() <= getmaxHP()/2)
        text.setFillColor(sf::Color(255,128,0));
    if(getHP() <= getmaxHP()/ 4)
        text.setFillColor(sf::Color::Red);

    walkingCounter++;

    if (walkingCounter == 2)
        walkingCounter = 0;

    }

Weapon* Enemy::dropWeapon() {
    int strenght = RNG::throwDice(getmaxHP() / 2);
    bool bonusORmalus = RNG::throwCoin(4);
    if (bonusORmalus)
        strenght = -strenght;
    strenght = getmaxHP()/2 + strenght; //calcola il danno della nuova arma

    bool rare = RNG::throwCoin(10);
    bool legendary = RNG::throwCoin(30);
    if (!rare)
        legendary = false;


    return WeaponFactory::createWeapon(rect.getPosition().x,rect.getPosition().y,strenght,rare,legendary);
}

void Enemy::fight(GameCharacter *hero) {
    int damage=getAtk();
    if(RNG::throwCoin(10 - hero->getEvade()))      //hero.evade=1 -> 10% evade chance
        damage=0;
    if(RNG::throwCoin((10- getCritical())))      // critical=1 -> 10% critical chance
        damage+=damage/2;
    hero->setHP(hero->getHP() - damage);
}

void Enemy::chaseHero(PlayableCharacter *hero) {
    // CHASE DOWN
    if (hero->rect.getPosition().y > rect.getPosition().y &&
        abs(static_cast<int>(hero->rect.getPosition().x - rect.getPosition().x)) <= 40)
        face = Face::Down;
        //CHASE UP
    else if ((hero->rect.getPosition().x > rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - rect.getPosition().y)) <= 40))
        face = Face::Right;
        //CHASE LEFT
    else if ((hero->rect.getPosition().x < rect.getPosition().x) &&
             (abs(static_cast<int>(hero->rect.getPosition().y - rect.getPosition().y)) <= 40))
        face = Face::Left;
        //CHASE UP
    else if ((hero->rect.getPosition().y < rect.getPosition().y) &&
             (abs(static_cast<int>(hero->rect.getPosition().x - rect.getPosition().x)) <= 40))
        face = Face::Up;

}

Spell* Enemy::shootSpell() {
    return new Spell(rect.getPosition().x + rect.getSize().x / 2 - 13,    //13= Half Spell Sprite
                     rect.getPosition().y + rect.getSize().y / 2 - rect.getSize().y / 2,
                     face);
}

int Enemy::dropChance= 3;
