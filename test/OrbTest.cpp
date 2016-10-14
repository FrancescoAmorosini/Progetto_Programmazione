//
// Created by Francesco Amorosini on 28/09/16.
//

#include "gtest/gtest.h"

#include "../Orb.h"

TEST(Orb, Orb_Construct_Test){
    Orb o(1,2,Color::red);

    ASSERT_EQ(1,o.rect.getPosition().x);
    ASSERT_EQ(2,o.rect.getPosition().y);
    ASSERT_EQ(Color::red, o.getOrbColor());
}

TEST(Orb, Orb_Using_test){
    Orb o(1,2,Color::red);
    PlayableCharacter hero(1,2,CharacterClass::Knight,"Giorgio", nullptr);
    hero.setInventory(&o);
    o.useOrb(&hero);

    ASSERT_EQ(15,hero.getAtk());
}