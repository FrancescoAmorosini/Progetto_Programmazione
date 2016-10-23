//
// Created by Francesco Amorosini on 26/07/16.
//

#include "LevelCreator.h"
#include <iostream>

int LevelCreator::characterSelection(sf::RenderWindow* window) {

    bool choosen = false;

    sf::Texture splashTexture;
    if (!splashTexture.loadFromFile("splash.jpg"))
        return EXIT_FAILURE;

    sf::Texture swordTexture;
    if (!swordTexture.loadFromFile("splashSword.png"))
        return EXIT_FAILURE;
    sf::Texture daggerTexture;
    if (!daggerTexture.loadFromFile("splashDagger.png"))
        return EXIT_FAILURE;
    sf::Texture staffTexture;
    if (!staffTexture.loadFromFile("splashStaff.png"))
        return EXIT_FAILURE;
    sf::Font font;
    if (!font.loadFromFile("Berry Rotunda.ttf"))
        return EXIT_FAILURE;

    sf::Text text;
    text.setFont(font);
    text.setPosition(60, 20);
    text.setCharacterSize(40);
    text.setString("It's dangerous to go alone, take one of these!");
    text.setStyle(sf::Text::Bold);

    sf::Sprite splash;
    splash.setTexture(splashTexture);
    splash.setColor(sf::Color(255, 255, 255, 200));

    sf::Sprite sword;
    sf::Sprite staff;
    sf::Sprite dagger;
    sword.setTexture(swordTexture);
    staff.setTexture(staffTexture);
    dagger.setTexture(daggerTexture);
    sword.setPosition(200, 300);
    staff.setPosition(500, 300);
    dagger.setPosition(800, 300);

    while (!choosen) {
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window->close();
                return EXIT_FAILURE;
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window->close();
                return EXIT_FAILURE;
            }
        }
        // Clear screen
        window->clear();

        //Knight Choosen
        if (sf::Mouse::getPosition(*window).y > 465 && sf::Mouse::getPosition(*window).y < 830 &&
            sf::Mouse::getPosition(*window).x > 322 && sf::Mouse::getPosition(*window).x < 720) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                heroclass = CharacterClass::Knight;
                choosen = true;
            }
        }
        //Mage Choosen
        if (sf::Mouse::getPosition(*window).y > 465 && sf::Mouse::getPosition(*window).y < 830 &&
            sf::Mouse::getPosition(*window).x > 800 && sf::Mouse::getPosition(*window).x < 1200) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                heroclass = CharacterClass::Mage;
                choosen = true;
            }
        }
        //Thief Choosen
        if (sf::Mouse::getPosition(*window).y > 465 && sf::Mouse::getPosition(*window).y < 830 &&
            sf::Mouse::getPosition(*window).x > 1280 && sf::Mouse::getPosition(*window).x < 1670) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                heroclass = CharacterClass::Thief;
                choosen = true;
            }
        }

        window->draw(splash);
        window->draw(sword);
        window->draw(staff);
        window->draw(dagger);
        window->draw(text);

        // Update the window
        window->display();
    }

    //Matches weapons with hero class
        WeaponFactory::heroWeaponType=WeaponFactory::matchHeroWeapon(heroclass);

    return EXIT_SUCCESS;
}

int LevelCreator::characterName(sf::RenderWindow *window) {

    sf::Texture splashTexture;
    if (!splashTexture.loadFromFile("splash2.jpg"))
        return EXIT_FAILURE;
    sf::Font font;
    if (!font.loadFromFile("Berry Rotunda.ttf"))
        return EXIT_FAILURE;

    sf::Sprite splash;
    splash.setTexture(splashTexture);
    splash.setColor(sf::Color(255, 255, 255, 220));

    sf::RectangleShape line;
    line.setSize(sf::Vector2f(400, 2));
    line.setPosition(450, 650);
    line.setFillColor(sf::Color::White);

    sf::RectangleShape typeBar;
    typeBar.setSize(sf::Vector2f(1, 45));
    typeBar.setPosition(475, 600);
    typeBar.setFillColor(sf::Color::White);

    sf::Text text;
    text.setFont(font);
    text.setPosition(370, 500);
    text.setCharacterSize(50);
    text.setString("Enter your name!");
    text.setStyle(sf::Text::Bold);

    sf::Text textInput;
    textInput.setFont(font);
    textInput.setPosition(450, 600);
    textInput.setCharacterSize(40);
    textInput.setStyle(sf::Text::Bold);

    std::string str;

    while (window->isOpen()) {
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window->close();
                return EXIT_FAILURE;
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window->close();
                return EXIT_FAILURE;
            }
            //Return pressed: confirm
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                return EXIT_SUCCESS;
            }
            if (event.type == sf::Event::TextEntered) {   //Backspace pressed: erase a letter
                if (event.text.unicode == '\b') {
                    if (str.size() > 0) {
                        str.erase(str.size() - 1, 1);
                        typeBar.move(-30, 0);
                    }
                }
                    //Letter pressed: add a letter to the string
                else if (event.text.unicode < 128 && str.size() < 20) {
                    str += static_cast<char>(event.text.unicode);
                    typeBar.move(30, 0);
                }
                heroname = str;
                textInput.setString(str);
            }

            // Clear screen
            window->clear();

            window->draw(splash);
            window->draw(text);
            window->draw(textInput);
            window->draw(line);
            window->draw(typeBar);

            // Update the window
            window->display();
        }
    }
    return EXIT_SUCCESS;
}


int LevelCreator::loadLevelExample(GameLevel* level) {
    if (!level->healthFont.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }

    if(!level->heroTexture.loadFromFile("hero.png"))
        return EXIT_FAILURE;
    level->hero->sprite.setTexture(level->heroTexture);
    level->hero->text.setFont(level->healthFont);
    for(int i=0; i< level->enemies.size(); i++) {
        level->enemies[i]->sprite.setTexture(level->heroTexture);
        level->enemies[i]->text.setFont(level->healthFont);
    }

    if(!level->floor1.loadFromFile("Floor.png"))
        return EXIT_FAILURE;

    for(int i=0; i<level->map->getHeight(); i++) {
        for(int j=0; j<level->map->getWidth();j++){
            level->map->getTile(i,j)->sprite.setTexture(level->floor1);
        }
    }

    for(int i=0; i< level->map->wallBuffer.size(); i++)
        level->map->wallBuffer[i]->sprite.setTexture(level->floor1);

    if(!level->orbTexture.loadFromFile("stone-b1.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->orbs.size(); i++)
        level->orbs[i]->sprite.setTexture(level->orbTexture);

    if(!level->chestTexture.loadFromFile("chest2.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->chests.size(); i++) {
        level->chests[i]->sprite.setTexture(level->chestTexture);
        level->chests[i]->text.setFont(level->healthFont);
    }

    if(!level->heartTexture.loadFromFile("hearts.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->hearts.size(); i++)
        level->hearts[i]->sprite.setTexture(level->heartTexture);

    if(!level->fireballTexture.loadFromFile("fireball.png"))
        return EXIT_FAILURE;

    if(!level->weaponTexture.loadFromFile("weapons-and-equipment.png"))
        return EXIT_FAILURE;

    return 0;
}

GameLevel* LevelCreator::createExample() {
    PlayableCharacter* hero= CharacterFactory::createCharacter(400,650,heroclass,heroname);
    Map* map= new Map(100,100);
    Weapon* w= WeaponFactory::createWeapon(0,0,15);
    Weapon* ww= WeaponFactory::createWeapon(0,0,30,true,true);

    std::vector<Enemy*> witches = CharacterFactory::createEnemyArray(2,CharacterClass::Witch,80,12);
    witches[0]->rect.setPosition(100,550);
    witches[1]->rect.setPosition(400,400);

    std::vector<Enemy*> bigbaldguy= CharacterFactory::createEnemyArray(1,CharacterClass::BigBaldGuy,150,5);
    bigbaldguy[0]->rect.setPosition(700,700);

    hero->setWeapon(w);

    map->createHorizontalWall(6, 50, 600);
    map->createHorizontalWall(6,50,478);
    map->createVerticaWall(4, 50,478);
    map->wallBuffer.push_back(new Wall(60,150, true));

    Orb* orb1= new Orb(500,500,Color::blue);
    Orb* orb2= new Orb(250,500,Color::red);
    Orb* orb3= new Orb(250,25,Color::green);
    Orb* orb4= new Orb(50,250,Color::yellow);
    Orb* orb5= new Orb(100,100,Color::purple);
    Orb* orb6= new Orb(0,0,Color::blue);

    Chest* chest1=new Chest(450,300,orb6);
    Chest* chest2= new Chest(200,560, ww);
    Chest* chest3= new Chest(200,520, ww);

    std::vector<Heart*> hearts;
    hearts.push_back(new Heart(190,60));
    //Merges different enemies array
    std::vector<Enemy*> enemies;
    enemies.reserve(bigbaldguy.size() + witches.size());
    enemies.insert(enemies.end(), bigbaldguy.begin(), bigbaldguy.end());
    enemies.insert(enemies.end(),witches.begin(), witches.end());

    std::vector<Chest*> chests;
    chests.push_back(chest1);
    chests.push_back(chest2);
    chests.push_back(chest3);

    std::vector<Orb*> orbs;
    orbs.push_back(orb1);
    orbs.push_back(orb2);
    orbs.push_back(orb3);
    orbs.push_back(orb4);
    orbs.push_back(orb5);

    GameLevel* levelExample= new GameLevel(map, hero,chests,orbs, enemies, hearts);

    loadLevelExample(levelExample);

    return levelExample;
}

CharacterClass LevelCreator::heroclass;
std::string LevelCreator::heroname;