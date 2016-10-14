//
// Created by Francesco Amorosini on 22/07/16.
//

#include "Enemy.h"
Enemy::Enemy(float x, float y, CharacterClass role, int HP, int atk, int sightRadius, float evade, float critical ) :
        GameCharacter(role,HP,atk,evade,critical), sightRadius(sightRadius) {
    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Cyan);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

}
void Enemy::updatePosition() {
    int speed = speedMovement;

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

    walkingCounter++;

    if (walkingCounter == 2)
        walkingCounter = 0;

    }

Weapon* Enemy::dropWeapon(WeaponType weaponType) {
    int strenght = RNG::throwDice(getmaxHP() / 2);
    bool bonusORmalus = RNG::throwCoin(4);
    if (bonusORmalus)
        strenght = -strenght;
    strenght = getmaxHP()/2 + strenght; //calcola il danno della nuova arma

    bool rare = RNG::throwCoin(10);
    bool legendary = RNG::throwCoin(30);
    if (!rare)
        legendary = false;


    return new Weapon(rect.getPosition().x, rect.getPosition().y, strenght, weaponType, rare, legendary);
}

void Enemy::fight(GameCharacter *hero) {
    int damage=getAtk();
    if(RNG::throwCoin(10 - hero->getEvade()))      //hero.evade=1 -> 10% evade chance
        damage=0;
    if(RNG::throwCoin((10- getCritical())))      // critical=1 -> 10% critical chance
        damage+=damage/2;
    hero->setHP(hero->getHP() - damage);
}

int Enemy::dropChance= 3;
