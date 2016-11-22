//
// Created by Francesco Amorosini on 22/07/16.
//

#include "Enemy.h"

Enemy::Enemy(float x, float y, CharacterClass role, int HP, int atk, int evade, int critical ) :
        GameCharacter(role,HP,atk,evade,critical), behavior(new TurnAround()) {
    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Cyan);
    text.setString(std::to_string(HP));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Green);

}
void Enemy::updatePosition() {
    //Updates sprites
    sprite.setPosition(rect.getPosition());
    text.setPosition(rect.getPosition().x, rect.getPosition().y -30);
    text.setString(std::to_string(getHP()));
    if(getHP() <= getmaxHP()/2)
        text.setFillColor(sf::Color(255,128,0));
    if(getHP() <= getmaxHP()/ 4)
        text.setFillColor(sf::Color::Red);

    walkingCounter++;

    if (walkingCounter >= 2)
        walkingCounter = 0;

    canMoveUP=true;
    canMoveLEFT=true;
    canMoveRIGHT=true;
    canMoveDOWN=true;
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

void Enemy::move(PlayableCharacter* hero) {
    //chooses direction
    behavior->movementBehavior(hero, this);

    //moves in that direcition
    int race=0;
    if(getRole() == CharacterClass::Bat)
        race=3;
    if(getRole() == CharacterClass::Witch)
        race=6;
    if(getRole() == CharacterClass::BigBaldGuy)
        race=9;
    switch (face) {
        case Face::Up:
            if(canMoveUP) {
                rect.move(0, -speed);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race - 8, 32 * 3, 32, 32));
            }
            break;
        case Face::Down:
            if(canMoveDOWN) {
                rect.move(0, speed);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race - 8, 0, 32, 32));
            }
            break;
        case Face::Left:
            if(canMoveLEFT) {
                rect.move(-speed, 0);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race - 8, 32 * 1, 32, 32));
            }
            break;
        case Face::Right:
            if(canMoveRIGHT) {
                rect.move(speed, 0);
                sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * race - 8, 32 * 2, 32, 32));
            }
            break;
    }
    updatePosition();
}

Spell* Enemy::shootSpell() {
    //if witch && aggroed enemy has chance of shooting a spell each 2 seconds
    if (RNG::throwCoin(120) && getRole() == CharacterClass::Witch && aggroed) {
        Spell *spell = new Spell(rect.getPosition().x + rect.getSize().x / 2 - 13,    //13= Half Spell Sprite
                                 rect.getPosition().y + rect.getSize().y / 2 - rect.getSize().y / 2,
                                 face);
        spell->sprite.setColor(sf::Color(255, 100, 255));
        return spell;
    } else
        return nullptr;
}

void Enemy::setAggroed(bool aggroed){
    this->aggroed=aggroed;
    if(this->aggroed)
        setStrategy(new ChaseHero());
}

void Enemy::setHP(int HP) {
    GameCharacter::setHP(HP);
    if(getHP() < 30)
        setStrategy(new Flee());
}

void Enemy::setStrategy(Strategy* s){
    delete behavior;
    behavior= s;
}

int Enemy::dropChance= 3;
