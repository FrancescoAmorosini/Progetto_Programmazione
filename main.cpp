
#include <iostream>
#include "LevelDrawer.h"


int main() {

    //Winwow
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Progetto Programmazione");
    window.setFramerateLimit(60);

    // View
    sf::View view1(sf::FloatRect(200, 200, 300, 200));
    view1.setSize(1024, 720);
    view1.setCenter(sf::Vector2f(view1.getSize().x / 2, view1.getSize().y / 2));
    window.setView(view1);

    //CHARACTER SELECTION
    if (LevelCreator::characterSelection(&window) == EXIT_FAILURE)
        return EXIT_FAILURE;
    //NAME SELECTION
    if (LevelCreator::characterName(&window) == EXIT_FAILURE)
        return EXIT_FAILURE;

    GameLevel *level = LevelCreator::createExample();
    LevelDrawer *drawer = new LevelDrawer(level);

    //DRAWS TUTORIAL
    drawer->drawInstructions(&window);

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
        //Game Over
        if (level->hero->gameover) {
            drawer->drawGameOver(&window);
        }//Level Completed
        else if (level->map->levelCompleted) {
            drawer->drawVictoriousSplash(&window);
        }
        else if (!level->hero->gameover && !level->map->levelCompleted) {

            //LEVEL UPDATE
            level->updateLevel();

            //DRAW LEVEL
            drawer->drawLevel(&window);
            std::cout << level->hero->rect.getPosition().x / 32 << " " << level->hero->rect.getPosition().y / 32
                      << std::endl;
        }

        // Update the window
        window.display();
    }
    LevelCreator::deleteLevel(level);
    return EXIT_SUCCESS;
}
