//
// Created by Francesco Amorosini on 30/09/16.
//

#include "Spell.h"

Spell::Spell(float x, float y, Face face) : face(face) {

    rect.setSize(sf::Vector2f(27, 27));
    rect.setPosition(x,y);
    rect.setFillColor(sf::Color::Green);
    switch (face) {
        case Face::Left:
            sprite.setTextureRect(sf::IntRect(0, 30, 32, 32));
            break;
        case Face::Up:
            sprite.setTextureRect(sf::IntRect(0, 90, 32, 32));
            break;
        case Face::Right:
            sprite.setTextureRect(sf::IntRect(0, 60, 32, 32));
            break;
        case Face::Down:
            sprite.setTextureRect(sf::IntRect(0,0,32, 32));
            break;

    }


}

void Spell::updateSpell() {
    int spellPath=spellRange % 3;
    switch (face) {
        case Face::Up:
            rect.move(0, -spellSpeed);
            sprite.setTextureRect(sf::IntRect(30*spellPath, 95, 32, 32));
            break;
        case Face::Down:
            rect.move(0, spellSpeed);
            sprite.setTextureRect(sf::IntRect(30*spellPath,0,32, 32));
            break;
        case Face::Left:
            rect.move(-spellSpeed, 0);
            sprite.setTextureRect(sf::IntRect(30*spellPath, 33, 32, 32));
            break;
        case Face::Right:
            rect.move(spellSpeed, 0);
            sprite.setTextureRect(sf::IntRect(30*spellPath, 65, 32, 32));
            break;
    }
    sprite.setPosition(rect.getPosition());

}

int Spell::maxSpellRange=240;
sf::Clock Spell::projectileLife;
sf::Time Spell::projectileLifeSpan= sf::seconds(0.4);