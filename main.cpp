
#include <iostream>
#include "PlayableCharacter.h"
#include "LevelCreator.h"



int main() {

    //Winwow
    sf::RenderWindow window(sf::VideoMode(1240, 720), "Progetto Programmazione");
    window.setFramerateLimit(60);

    // View
    sf::View view1(sf::FloatRect(200, 200, 300, 200));
    view1.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    view1.setCenter(sf::Vector2f(view1.getSize().x/2, view1.getSize().y/2));
    window.setView(view1);


    GameLevel* level= LevelCreator::createExample();

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Texture Herotexture;
    if(!Herotexture.loadFromFile("hero.png"))
        return EXIT_FAILURE;
    level->hero->sprite.setTexture(Herotexture);
    level->hero->text.setFont(font);
    for(int i=0; i< level->enemies.size(); i++) {
        level->enemies[i]->sprite.setTexture(Herotexture);
        level->enemies[i]->text.setFont(font);
    }

    sf::Texture floor;
    if(!floor.loadFromFile("Floor.png"))
        return EXIT_FAILURE;

        for(int i=0; i<level->map->getHeight(); i++) {
            for(int j=0; j<level->map->getWidth();j++){
                level->map->getTile(i,j)->sprite.setTexture(floor);
            }
        }
    for(int i=0; i< level->map->wallBuffer.size(); i++)
        level->map->wallBuffer[i]->sprite.setTexture(floor);

    sf::Texture fireball;
    if(!fireball.loadFromFile("fireball.png"))
        return EXIT_FAILURE;

    sf::Texture Orbtexture;
    if(!Orbtexture.loadFromFile("stone-b1.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->orbs.size(); i++)
        level->orbs[i]->sprite.setTexture(Orbtexture);

    sf::Texture Chestexture;
    if(!Chestexture.loadFromFile("chest2.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->chests.size(); i++) {
        level->chests[i]->sprite.setTexture(Chestexture);
        level->chests[i]->text.setFont(font);
    }

    sf::Texture heartexture;
    if(!heartexture.loadFromFile("hearts.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->hearts.size(); i++)
        level->hearts[i]->sprite.setTexture(heartexture);

    sf::Texture weapontexture;
    if(!weapontexture.loadFromFile("weapons-and-equipment.png"))
        return EXIT_FAILURE;


    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        // Clear screen
        window.clear();

        //Draws Map and Walls
       for(int i=0; i<level->map->getHeight(); i++) {
           for (int j = 0; j < level->map->getWidth(); j++) {
               level->map->getTile(i, j)->sprite.setPosition((32 * i), (32 * j));
               window.draw(level->map->getTile(i, j)->sprite);
           }
       }
        for(int i=0; i< level->map->wallBuffer.size(); i++)
            window.draw(level->map->wallBuffer[i]->sprite);

        //LEVEL UPDATE
        level->updateLevel();

        // Player View
        window.setView(view1);
        view1.setCenter(level->hero->rect.getPosition());

        //Draws Orbs
        for(int i=0; i< level->orbs.size(); i++)
            window.draw(level->orbs[i]->sprite);

        //Draws Spells
        for(int i=0; i< level->spells.size(); i++){
            level->spells[i]->sprite.setTexture(fireball);
            window.draw(level->spells[i]->sprite);
        }
        //Draws Hero
        window.draw(level->hero->sprite);
        window.draw(level->hero->text);

        //Draws Enemies
        for(int i=0; i< level->enemies.size(); i++){
            window.draw(level->enemies[i]->sprite);
            window.draw(level->enemies[i]->text);
        }
        //Draws Chests
        for(int i=0; i< level->chests.size(); i++){
            window.draw(level->chests[i]->sprite);
            window.draw(level->chests[i]->text);
        }
        //Draws Hearts
        for(int i=0; i< level->hearts.size(); i++){
            window.draw(level->hearts[i]->sprite);
        }
        //Draws Weapon
        for(int i=0; i< level->weapons.size(); i++) {
            level->weapons[i]->sprite.setTexture(weapontexture);
            window.draw(level->weapons[i]->sprite);
            level->weapons[i]->text.setFont(font);
            window.draw(level->weapons[i]->text);
        }

        std::cout<< level->hero->getHP() << std::endl;
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}


//TODO: scalette, AI, textureLoader