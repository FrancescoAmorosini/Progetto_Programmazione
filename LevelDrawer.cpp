//
// Created by Francesco Amorosini on 19/10/16.
//

#include "LevelDrawer.h"

void drawLevel(GameLevel* level, sf::RenderWindow* window){

    //Draws Map and Walls
    for(int i=0; i<level->map->buffer.size(); i++) {
            window->draw(level->map->buffer[i]->sprite);
    }
    for(int i=0; i< level->map->wallBuffer.size(); i++)
        window->draw(level->map->wallBuffer[i]->sprite);

    //Draws Orbs
    for(int i=0; i< level->orbs.size(); i++)
        window->draw(level->orbs[i]->sprite);

    //Draws Spells
    for(int i=0; i< level->spells.size(); i++){
        level->spells[i]->sprite.setTexture(level->fireballTexture);
        window->draw(level->spells[i]->sprite);
    }
    for(int i=0; i< level->enemySpells.size(); i++) {
        level->enemySpells[i]->sprite.setTexture(level->fireballTexture);
        window->draw(level->enemySpells[i]->sprite);
    }
    //Draws Hero
    window->draw(level->hero->sprite);
    window->draw(level->hero->text);

    //Draws Enemies
    for(int i=0; i< level->enemies.size(); i++){
        window->draw(level->enemies[i]->sprite);
        window->draw(level->enemies[i]->text);
    }
    //Draws Chests
    for(int i=0; i< level->chests.size(); i++){
        window->draw(level->chests[i]->sprite);
        window->draw(level->chests[i]->text);
    }
    //Draws Hearts
    for(int i=0; i< level->hearts.size(); i++){
        window->draw(level->hearts[i]->sprite);
    }
    //Draws Weapon
    for(int i=0; i< level->weapons.size(); i++) {
        level->weapons[i]->sprite.setTexture(level->weaponTexture);
        window->draw(level->weapons[i]->sprite);
        level->weapons[i]->text.setFont(level->healthFont);
        window->draw(level->weapons[i]->text);
    }
}

