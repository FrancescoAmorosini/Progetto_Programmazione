
#include <iostream>
#include "LevelCreator.h"
#include "LevelDrawer.h"



int main() {

    //Winwow
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Progetto Programmazione");
    window.setFramerateLimit(60);

    // View
    sf::View view1(sf::FloatRect(200, 200, 300, 200));
    view1.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    view1.setCenter(sf::Vector2f(view1.getSize().x/2, view1.getSize().y/2));
    window.setView(view1);

    //CHARACTER SELECTION
    LevelCreator::characterSelection(&window);

    GameLevel* level= LevelCreator::createExample();

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

        //LEVEL UPDATE
        level->updateLevel();

        //DRAW LEVEL
        drawLevelExample(level, &window);

        //PLAYER VIEW
        window.setView(view1);
        view1.setCenter(level->hero->rect.getPosition());

        std::cout<< level->hero->getHP() << std::endl;

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}


//TODO: scalette