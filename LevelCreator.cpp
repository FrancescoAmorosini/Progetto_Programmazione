//
// Created by Francesco Amorosini on 26/07/16.
//

#include "LevelCreator.h"
#include <fstream>


int LevelCreator::characterSelection(sf::RenderWindow* window) {
    if(!menuTheme.openFromFile("Resources/menuTheme.ogg"))
        return EXIT_FAILURE;
    menuTheme.play();

    bool choosen = false;

    sf::Texture splashTexture;
    if (!splashTexture.loadFromFile("Resources/splash.jpg"))
        return EXIT_FAILURE;

    sf::Texture axeTexture;
    if (!axeTexture.loadFromFile("Resources/splashAxe.png"))
        return EXIT_FAILURE;
    sf::Texture daggerTexture;
    if (!daggerTexture.loadFromFile("Resources/splashDagger.png"))
        return EXIT_FAILURE;
    sf::Texture staffTexture;
    if (!staffTexture.loadFromFile("Resources/splashStaff.png"))
        return EXIT_FAILURE;
    sf::Font font;
    if (!font.loadFromFile("Resources/Berry Rotunda.ttf"))
        return EXIT_FAILURE;

    sf::Text text;
    text.setFont(font);
    text.setPosition(60, 20);
    text.setCharacterSize(32);
    text.setString("It's dangerous to go alone, take one of these!");
    text.setStyle(sf::Text::Bold);

    sf::Sprite splash;
    splash.setTexture(splashTexture);
    splash.setColor(sf::Color(255, 255, 255, 200));

    sf::RectangleShape weapons;
    weapons.setSize(sf::Vector2f(256, 256));
    weapons.setFillColor(sf::Color::White);

    sf::Sprite axe;
    sf::Sprite staff;
    sf::Sprite dagger;
    axe.setTexture(axeTexture);
    staff.setTexture(staffTexture);
    dagger.setTexture(daggerTexture);
    axe.setPosition(70, 300);
    staff.setPosition(370, 300);
    dagger.setPosition(670, 300);

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
            sf::Mouse::getPosition(*window).x > 140 && sf::Mouse::getPosition(*window).x < 600) {
            weapons.setPosition(70,300);
            window->draw(weapons);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                heroclass = CharacterClass::Warrior;
                choosen = true;
            }
        }
        //Mage Choosen
        if (sf::Mouse::getPosition(*window).y > 465 && sf::Mouse::getPosition(*window).y < 830 &&
            sf::Mouse::getPosition(*window).x > 700 && sf::Mouse::getPosition(*window).x < 1160) {
            weapons.setPosition(370,300);
            window->draw(weapons);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                heroclass = CharacterClass::Mage;
                choosen = true;
            }
        }
        //Thief Choosen
        if (sf::Mouse::getPosition(*window).y > 465 && sf::Mouse::getPosition(*window).y < 830 &&
            sf::Mouse::getPosition(*window).x > 1260 && sf::Mouse::getPosition(*window).x < 1725) {
            weapons.setPosition(670,300);
            window->draw(weapons);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                heroclass = CharacterClass::Thief;
                choosen = true;
            }
        }

        window->draw(splash);
        window->draw(axe);
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
    if (!splashTexture.loadFromFile("Resources/splash2.jpg"))
        return EXIT_FAILURE;
    sf::Font font;
    if (!font.loadFromFile("Resources/Berry Rotunda.ttf"))
        return EXIT_FAILURE;

    sf::Sprite splash;
    splash.setTexture(splashTexture);
    splash.setColor(sf::Color(255, 255, 255, 220));

    sf::RectangleShape line;
    line.setSize(sf::Vector2f(400, 2));
    line.setPosition(280, 650);
    line.setFillColor(sf::Color::White);

    sf::RectangleShape typeBar;
    typeBar.setSize(sf::Vector2f(1, 45));
    typeBar.setPosition(300, 600);
    typeBar.setFillColor(sf::Color::White);

    sf::Text text;
    text.setFont(font);
    text.setPosition(200, 500);
    text.setCharacterSize(50);
    text.setString("Enter your name!");
    text.setStyle(sf::Text::Bold);

    sf::Text textInput;
    textInput.setFont(font);
    textInput.setPosition(280, 600);
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
                //stops music
                for(int vol=0; vol<100; vol++){
                    menuTheme.setVolume(100 - vol);
                }
                menuTheme.stop();
                return EXIT_SUCCESS;
            }
            if (event.type == sf::Event::TextEntered) {   //Backspace pressed: erase a letter
                if (event.text.unicode == '\b') {
                    if (str.size() > 0) {
                        str.erase(str.size() - 1, 1);
                        typeBar.move(-25, 0);
                    }
                }
                    //Letter pressed: add a letter to the string
                else if (event.text.unicode < 128 && str.size() < 20) {
                    str += static_cast<char>(event.text.unicode);
                    typeBar.move(25, 0);
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
    //FONT
    if (!level->healthFont.loadFromFile("Resources/sansation.ttf")) {
        return EXIT_FAILURE;
    }
    //TEXTURES AND SPRITES
    if(!level->heroTexture.loadFromFile("Resources/hero.png"))
        return EXIT_FAILURE;
    level->hero->sprite.setTexture(level->heroTexture);
    level->hero->text.setFont(level->healthFont);

    if(!level->enemyTexture.loadFromFile("Resources/enemies.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->enemies.size(); i++) {
        level->enemies[i]->sprite.setTexture(level->enemyTexture);
        level->enemies[i]->text.setFont(level->healthFont);
    }

    if(!level->floor1.loadFromFile("Resources/Floor.png"))
        return EXIT_FAILURE;
    if(!level->stairs.loadFromFile("Resources/stairs.png"))
        return EXIT_FAILURE;

    for(int i=0; i<level->map->buffer.size(); i++) {
            level->map->buffer[i]->sprite.setTexture(level->floor1);
    } level->map->exit->sprite.setTexture(level->stairs);

    for(int i=0; i< level->map->wallBuffer.size(); i++)
        level->map->wallBuffer[i]->sprite.setTexture(level->floor1);

    if(!level->orbTexture.loadFromFile("Resources/stone-b1.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->orbs.size(); i++)
        level->orbs[i]->sprite.setTexture(level->orbTexture);

    if(!level->chestTexture.loadFromFile("Resources/chest2.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->chests.size(); i++) {
        level->chests[i]->sprite.setTexture(level->chestTexture);
        level->chests[i]->text.setFont(level->healthFont);
    }

    if(!level->heartTexture.loadFromFile("Resources/hearts.png"))
        return EXIT_FAILURE;
    for(int i=0; i< level->hearts.size(); i++)
        level->hearts[i]->sprite.setTexture(level->heartTexture);

    if(!level->fireballTexture.loadFromFile("Resources/fireball.png"))
        return EXIT_FAILURE;

    if(!level->weaponTexture.loadFromFile("Resources/weapons-and-equipment.png"))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

GameLevel* LevelCreator::createExample() {
    PlayableCharacter* hero= CharacterFactory::createCharacter(32* 15,32* 116,heroclass,heroname);
    Map* map= new Map(120,130);
    map->exit->rect.setPosition(32*83,32*65);
    map->exit->sprite.setPosition(map->exit->rect.getPosition());
    Weapon* w= WeaponFactory::createWeapon(0,0,15);
    hero->setWeapon(w);

    std::vector<Enemy*> witches = CharacterFactory::createEnemyArray(7,CharacterClass::Witch,80,15);
    witches[0]->rect.setPosition(32*90,32*116);
    witches[1]->rect.setPosition(32*89,32*116);
    witches[2]->rect.setPosition(32*89,32*117);
    witches[3]->rect.setPosition(32*88,32*117);
    witches[4]->rect.setPosition(32*88,32*115);
    witches[5]->rect.setPosition(32*25,32*88);
    witches[6]->rect.setPosition(32*29,32*88);
    std::vector<Enemy*> witchesStrong = CharacterFactory::createEnemyArray(5,CharacterClass::Witch,100,25);
    witchesStrong[0]->rect.setPosition(32*84,32*70);
    witchesStrong[1]->rect.setPosition(32*86,32*73);
    witchesStrong[2]->rect.setPosition(32*85,32*75);
    witchesStrong[3]->rect.setPosition(32*86,32*68);
    witchesStrong[4]->rect.setPosition(32*85,32*77);
    witches.reserve(witchesStrong.size());
    witches.insert(witches.end(), witchesStrong.begin(), witchesStrong.end());

    std::vector<Enemy*> bigbaldguy= CharacterFactory::createEnemyArray(6,CharacterClass::BigBaldGuy,100,12);
    bigbaldguy[0]->rect.setPosition(32*15, 32*95);
    bigbaldguy[1]->rect.setPosition(32*18, 32*95);
    bigbaldguy[2]->rect.setPosition(32*20, 32*95);
    bigbaldguy[3]->rect.setPosition(32*27, 32*91);
    std::vector<Enemy*> BBBStrong=CharacterFactory::createEnemyArray(7,CharacterClass::BigBaldGuy,150,15);
    BBBStrong[0]->rect.setPosition(32*75, 32*68);
    BBBStrong[1]->rect.setPosition(32*74, 32*67);
    BBBStrong[2]->rect.setPosition(32*70, 32*65);
    BBBStrong[3]->rect.setPosition(32*74, 32*64);
    BBBStrong[4]->rect.setPosition(32*70, 32*62);
    BBBStrong[3]->rect.setPosition(32*74, 32*70);
    BBBStrong[4]->rect.setPosition(32*70, 32*71);

    bigbaldguy.reserve(BBBStrong.size());
    bigbaldguy.insert(bigbaldguy.end(), BBBStrong.begin(), BBBStrong.end());

    std::vector<Enemy*> skeletons= CharacterFactory::createEnemyArray(6,CharacterClass::Undead,50,10);
    skeletons[0]->rect.setPosition(32*15, 32*110);
    skeletons[1]->rect.setPosition(32*20, 32*117);
    skeletons[2]->rect.setPosition(32*27, 32*90);
    skeletons[3]->rect.setPosition(32*27, 32*89);
    std::vector<Enemy*> SkeletonsStrong = CharacterFactory::createEnemyArray(3,CharacterClass::Undead,80,12);
    SkeletonsStrong[0]->rect.setPosition(32*75, 32*64);
    SkeletonsStrong[1]->rect.setPosition(32*75, 32*65);
    skeletons.reserve(SkeletonsStrong.size());
    skeletons.insert(skeletons.end(), SkeletonsStrong.begin(), SkeletonsStrong.end());

    std::vector<Enemy*> bats= CharacterFactory::createEnemyArray(15,CharacterClass::Bat,20,5);
    bats[0]->rect.setPosition(32*48,32*110);
    bats[1]->rect.setPosition(32*50,32*110);
    bats[2]->rect.setPosition(32*55,32*110);
    bats[3]->rect.setPosition(32*52,32*110);
    bats[4]->rect.setPosition(32*17,32*70);
    bats[5]->rect.setPosition(32*17,32*71);
    bats[6]->rect.setPosition(32*17,32*72);
    bats[7]->rect.setPosition(32*17,32*73);
    bats[8]->rect.setPosition(32*17,32*74);
    bats[9]->rect.setPosition(32*17,32*75);
    bats[10]->rect.setPosition(32*17,32*71);
    bats[11]->rect.setPosition(32*17,32*72);
    bats[12]->rect.setPosition(32*17,32*73);
    bats[13]->rect.setPosition(32*17,32*74);
    bats[14]->rect.setPosition(32*17,32*75);
    std::vector<Enemy*>batStrong= CharacterFactory::createEnemyArray(6,CharacterClass::Bat,40,15);
    batStrong[0]->rect.setPosition(32*84,32*56);
    batStrong[1]->rect.setPosition(32*85,32*56);
    batStrong[2]->rect.setPosition(32*83,32*56);
    batStrong[3]->rect.setPosition(32*83,32*56);
    batStrong[4]->rect.setPosition(32*86,32*56);
    batStrong[5]->rect.setPosition(32*87,32*56);
    bats.reserve(batStrong.size());
    bats.insert(bats.end(),batStrong.begin(),batStrong.end());


    std::vector<Heart*> hearts;
    hearts.push_back(new Heart(32*36,32*110));
    hearts.push_back(new Heart(32*36,32*114));
    hearts.push_back(new Heart(32*61,32*88));
    hearts.push_back(new Heart(32*78,32*83));
    hearts.push_back(new Heart(32*28,32*42));
    hearts.push_back(new Heart(32*32,32*42));
    hearts.push_back(new Heart(32*68,32*52));
    //Merges different enemies array
    std::vector<Enemy*> enemies;
    enemies.reserve(bigbaldguy.size() + witches.size() + skeletons.size() + bats.size());
    enemies.insert(enemies.end(), bigbaldguy.begin(), bigbaldguy.end());
    enemies.insert(enemies.end(),witches.begin(), witches.end());
    enemies.insert(enemies.end(),skeletons.begin(), skeletons.end());
    enemies.insert(enemies.end(),bats.begin(), bats.end());

    enemies.push_back(new Enemy(200,230,CharacterClass::Undead,50,12));
    enemies.push_back(new Enemy(100,100,CharacterClass::Bat,20,5));

    std::vector<Chest*> chests;
    chests.push_back(new Chest(32*14,32*104,new Orb(32*14,32*104,Color::red)));
    chests.push_back(new Chest(32*17,32*70, new Orb(32*17,32*71,Color::yellow)));
    chests.push_back(new Chest(32*15,32*69, new Orb(32*15,32*69,Color::green)));
    chests.push_back(new Chest(32*19,32*69, new Orb(32*19,32*69,Color::purple)));
    chests.push_back(new Chest(32*27,32*88,WeaponFactory::createWeapon(32*27,32*88,35,true)));
    chests.push_back(new Chest(32*36,32*112, WeaponFactory::createWeapon(32*30,32*117,10,true)));
    chests.push_back(new Chest(32*90,32*117,WeaponFactory::createWeapon(32*100,32*110,20,true, true)));
    chests.push_back(new Chest(32*15,32*88, WeaponFactory::createWeapon(32*15,32*88,50)));

    std::vector<Orb*> orbs;
    orbs.push_back(new Orb(32*30, 32*112,Color::green));
    orbs.push_back(new Orb(32*40, 32*112,Color::blue));
    orbs.push_back(new Orb(32*50, 32*112,Color::red));
    orbs.push_back(new Orb(32*60, 32*80,Color::purple));
    orbs.push_back(new Orb(32*50, 32*90,Color::blue));
    orbs.push_back(new Orb(32*50, 32*70,Color::red));
    orbs.push_back(new Orb(32*70, 32*90,Color::purple));
    orbs.push_back(new Orb(32*60, 32*95,Color::green));
    orbs.push_back(new Orb(32*32, 32*86,Color::blue));
    orbs.push_back(new Orb(32*23, 32*86,Color::red));
    int tilePositionX = 0;
    int tilePositionY = 0;

    std::ifstream openfile("Resources/LEVEL1.txt");
    if(openfile.is_open()){
        while(!openfile.eof()){
            std::string str;
            openfile >> str;
            char x = str[0];
            if(isdigit(x))
                map->wallBuffer.push_back(new Wall(tilePositionX, tilePositionY, str));
            if(x == 'X')
                map->buffer.push_back(new Tile(tilePositionX, tilePositionY, str));

            if(openfile.peek() == '\n'){
                tilePositionX =0;
                tilePositionY+=32;
            }
            else
                tilePositionX+=32;
        }
    }
    leveldeleted=false;

    GameLevel* levelExample= new GameLevel(map, hero,chests,orbs, enemies, hearts);

    loadLevelExample(levelExample);

    return levelExample;
}

void LevelCreator::deleteLevel(GameLevel *level) {
    if(!leveldeleted)
        delete level;
    leveldeleted=true;
}

CharacterClass LevelCreator::heroclass;
std::string LevelCreator::heroname;
sf::Music LevelCreator::menuTheme;
bool LevelCreator::leveldeleted;