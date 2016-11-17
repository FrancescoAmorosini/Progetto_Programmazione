//
// Created by Francesco Amorosini on 28/09/16.
//

#include "gtest/gtest.h"

#include "../PlayableCharacter.h"
#include "../Chest.h"

TEST(PlayableCharacter,PlayableCharacter_Constructor_Test) {
    Weapon *weapon = new Weapon(0, 0, 57, WeaponType::Axe);
    PlayableCharacter *c = new PlayableCharacter(0, 0, CharacterClass::Thief, "Aragorn", weapon);

    ASSERT_EQ(0, c->rect.getPosition().x);
    ASSERT_EQ(0, c->rect.getPosition().y);
    ASSERT_EQ(100, c->getHP());
    ASSERT_EQ(10, c->getAtk());
    ASSERT_EQ(CharacterClass::Thief, c->getRole());
    ASSERT_EQ("Aragorn", dynamic_cast<PlayableCharacter *>(c)->getName());
    ASSERT_EQ(weapon, dynamic_cast<PlayableCharacter *>(c)->getWeapon());
    ASSERT_FLOAT_EQ(1, c->getEvade());
    ASSERT_FLOAT_EQ(1, c->getCritical());
}

TEST(PlayableCharacter,PlayableCharacter_Setting_Test){
    Weapon* w=new Weapon (0,0,13,WeaponType::Staff);
    Orb* o=new Orb (0,0,Color::green);
    PlayableCharacter* g= new PlayableCharacter (0,0,CharacterClass::Mage,"GreyGandalf",0);

    g->setmaxHP(200);
    g->setHP(200);
    g->setAtk(35);
    g->setEvade(2);
    g->setCritical(2);
    g->setName("WhiteGandalf");
    g->setWeapon(w);
    g->setInventory(o);

    ASSERT_EQ(200,g->getHP());
    ASSERT_EQ(35,g->getAtk());
    ASSERT_EQ(2,g->getEvade());
    ASSERT_EQ(2,g->getCritical());
    ASSERT_EQ(CharacterClass::Mage,g->getRole());
    ASSERT_EQ("WhiteGandalf",g->getName());
    ASSERT_EQ(w,g->getWeapon());
    ASSERT_EQ(o,g->getInventory(0));

    ASSERT_FALSE(g->getInventory(12));
    ASSERT_FALSE(g->getInventory(-1));

}

TEST(PlayableCharacter,PlayableCharacter_move_Test){
    Weapon *weapon = new Weapon(0, 0, 57, WeaponType::Axe);
    PlayableCharacter* a=new PlayableCharacter(0,0,CharacterClass::Warrior,"Aragorn",weapon);
    a->rect.move(1,4);
    a->updatePosition();

    ASSERT_EQ(1,a->rect.getPosition().x);
    ASSERT_EQ(4,a->rect.getPosition().y);
    ASSERT_EQ(1,a->getWeapon()->rect.getPosition().x);
    ASSERT_EQ(4,a->getWeapon()->rect.getPosition().y);
}

TEST(PlayableCharacter, PlayableCharacter_Fight_Test) {
    Weapon *weapon = new Weapon(0, 0, 10, WeaponType::Dagger, false, false);
    PlayableCharacter *c = new PlayableCharacter(1, 2, CharacterClass::Warrior, "Aragorn", weapon);
    PlayableCharacter *e = new PlayableCharacter(1, 2, CharacterClass::Mage, "Saruman", weapon);
    c->fight(e);
    if (e->getHP() < e->getmaxHP() - (c->getAtk() - weapon->getStrenght() - weapon->getStrenght() % 13) &&
            e->getHP() > e->getmaxHP() - (weapon->getStrenght() + weapon->getStrenght() % 13 + c->getAtk())) // possible damage range
        SUCCEED();
    else if (e->getHP() == 100)
        SUCCEED();
    else
        FAIL();
}

TEST(PlayableCharacter, PlayableCharacter_heal_test){
    GameCharacter* c= new PlayableCharacter(0,0,CharacterClass::Warrior,"Giorgio", nullptr);
    c->setHP(60);
    c->heal(30);
    ASSERT_EQ(90,c->getHP());
    c->heal(30);
    ASSERT_EQ(100,c->getHP());
    delete c;
}
