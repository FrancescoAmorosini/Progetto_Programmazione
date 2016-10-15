//
// Created by Francesco Amorosini on 26/07/16.
//

#include "LevelCreator.h"


GameLevel* LevelCreator::loadLevel(Map* map, PlayableCharacter *hero, std::vector<Chest *> chests,
                                         std::vector<Orb *> orbs, std::vector<Enemy *> enemies, std::vector<Heart *> hearts) {
     GameLevel* level= new GameLevel (map, hero,chests,orbs, enemies, hearts);
    return level;
}

GameLevel* LevelCreator::createExample() {
    Map* map= new Map(100,100);
    Weapon* w= new Weapon(0,0,15,WeaponType::Staff);
    Weapon* ww= new Weapon(0,0,30,WeaponType::Staff, true, true);
    PlayableCharacter* hero= new PlayableCharacter (400,500,CharacterClass::Mage,"FierFranco", w);
    Enemy* enemy= new Enemy (100,550,CharacterClass::Witch,100,10,3);
    Enemy* enemy2= new Enemy (400,400,CharacterClass::Witch,100,10,3);

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

    std::vector<Enemy*> enemies;
    enemies.push_back(enemy);
    enemies.push_back(enemy2);

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



    return loadLevel(map, hero,chests,orbs, enemies, hearts);


}
