//
// Created by Francesco Amorosini on 28/09/16.
//

#include <gtest/gtest.h>

#include "../Chest.h"

TEST(Chest,Chest_Constructor_Test) {
    Orb* o= new Orb(0, 0, Color::green);
    Weapon* w= new Weapon(0, 0, 15, WeaponType::Dagger, false, true);
    Chest* c= new Chest(0, 0, w);
    Chest* ch= new Chest(1, 1, o);

    ASSERT_EQ(0, c->rect.getPosition().x);
    ASSERT_EQ(1, ch->rect.getPosition().y);
    ASSERT_EQ(Color::green, ch->getOrb()->getOrbColor());
    ASSERT_TRUE(c->getWeapon()->isLegendary());

}

TEST(Chest,Chest_Setting_Test){
    Orb* o= new Orb(0, 0, Color::green);
    Weapon* w= new Weapon(0, 0, 15, WeaponType::Dagger, false, true);
    Chest* c=new Chest(0, 0, w);
    Chest* ch= new Chest(1, 1, o);

    c->setOrb(o);
    ch->setWeapon(w);

    ASSERT_EQ(Color::green,c->getOrb()->getOrbColor());
    ASSERT_TRUE(ch->getWeapon()->isLegendary());

}

TEST(Chest, Chest_Opening_Test){
    Orb* o= new Orb(0, 0, Color::green);
    Weapon* w= new Weapon(0, 0, 15, WeaponType::Dagger, false, true);
    Weapon* ww= new Weapon(5, 6, 100, WeaponType::Dagger, false, false);
    PlayableCharacter hero(1,2,CharacterClass::Knight,"Giorgio", ww);
    Chest* c=new Chest(0, 0, w);
    Chest* ch= new Chest(1, 1, o);

    c->openChest(&hero);
    ch->openChest(&hero);

    ASSERT_EQ(hero.getWeapon()->getStrenght(),15);
    ASSERT_EQ(hero.getInventory(0)->getOrbColor(), Color::green);
    ASSERT_EQ(c->getWeapon()->getStrenght(), 100);

}