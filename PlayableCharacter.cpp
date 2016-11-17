//
// Created by Francesco Amorosini on 22/06/16.
//

#include "PlayableCharacter.h"


PlayableCharacter::PlayableCharacter(float x, float y, CharacterClass r, std::string name, Weapon* w,int HP, int atk, int evade, int critical) throw(std::invalid_argument) :
        GameCharacter(r,HP,atk,evade,critical),name(name), weapon(w){
    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Red);
    switch(r){
        case CharacterClass::Mage:
            sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        case CharacterClass::Thief:
            sprite.setTextureRect(sf::IntRect(32*6, 0, 32, 32));
        case CharacterClass::Warrior:
            sprite.setTextureRect(sf::IntRect(32*3, 0, 32, 32));
        default:
            break;
    }

    text.setString(name);
    text.setCharacterSize(16);
}

PlayableCharacter::~PlayableCharacter() {
    if(weapon!= nullptr)
        delete weapon;
    inventory.erase(inventory.begin(),inventory.end());
}

void PlayableCharacter::updatePosition() {
    sprite.setPosition(rect.getPosition());
    int long delay = name.length() * 2;
    if (name.length() < 5)
        delay = -name.length();
    text.setPosition(rect.getPosition().x - delay, rect.getPosition().y - 20);
    if (weapon)
        weapon->rect.setPosition(rect.getPosition());
}

void PlayableCharacter::fight(GameCharacter* enemy) {
    int damage= getAtk() + weapon->useWeapon();
    if(RNG::throwCoin(10 - getCritical()) && !weapon->isLegendary())                     // critical=1 -> 10% critical chance
        damage+= damage/2;
    if(RNG::throwCoin(10 - enemy->getEvade()))                                          //enemy.evade=1 -> 10% evade chance
        damage=0;
    if(damage){
        enemy->setHP(enemy->getHP()-damage);
        if(weapon->isRare())
            heal(damage/3);
    }
    if(!enemy->getHP())
        addEnemyKilled();
}
void PlayableCharacter::updateDirection() {
    walkingCounter++;
    int role = 0;
    int fightCounter = 0;
    if (getRole() == CharacterClass::Warrior)
        role = 3;
    if (getRole() == CharacterClass::Thief)
        role = 6;
    if (isFighting)
        fightCounter = 4;
    switch (face) {
        case Face::Up:
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * role, 32 * 3 + 32 * fightCounter, 32, 32));
            break;
        case Face::Down:
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * role, 32 * 0 + 32 * fightCounter, 32, 32));
            break;
        case Face::Left:
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * role, 32 * 1 + 32 * fightCounter, 32, 32));
            break;
        case Face::Right:
            sprite.setTextureRect(sf::IntRect(walkingCounter * 32 + 32 * role, 32 * 2 + 32 * fightCounter, 32, 32));
            break;
    }
    if(walkingCounter==2) {
        walkingCounter=0;
        isFighting = false;
    }
}

const std::string PlayableCharacter::getName() const {
    return this->name;
}

void PlayableCharacter::setName(const std::string &name) {
    PlayableCharacter::name = name;
}
void PlayableCharacter::setHP(int HP) {
    GameCharacter::setHP(HP);
    if(!getHP())
        setGameOver();
}

Weapon* PlayableCharacter::getWeapon() const {
    return weapon;
}

void PlayableCharacter::setWeapon(Weapon *weapon) {
    weapon->rect.setPosition(rect.getPosition());
    this->weapon = weapon;
}

Orb* PlayableCharacter::getInventory(int index) const throw(RangeException) {
    if (index>=0 && index<inventory.size()) {
        return inventory[index];
    }
    else
        return nullptr;

}

void PlayableCharacter::setInventory(Orb* o){
    inventory.push_back(o);
}

void PlayableCharacter::addChestOpened() {
    chestOpened=true;
    notify();
}

void PlayableCharacter::addHeartPicked() {
    heartpicked=true;
    notify();
}

void PlayableCharacter::addSpellShot() {
    spellshot=true;
    notify();
}

void PlayableCharacter::addOrbUsed() {
    orbUsed=true;
    notify();
}

void PlayableCharacter::addEnemyKilled() {
    enemykilled=true;
    notify();
}

void PlayableCharacter::setGameOver() {
    gameover=true;
    notify();
}
void PlayableCharacter::registerObserver(Observer *O) {
    observers.push_back(O);
}

void PlayableCharacter::unregisterObserver(Observer *O) {
    observers.remove(O);
}

void PlayableCharacter::notify() const {
    for (auto itr = std::begin(observers); itr != std::end(observers); itr++) {
        (*itr)->update();
    }
}