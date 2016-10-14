//
// Created by Francesco Amorosini on 28/09/16.
//

#include "gtest/gtest.h"

#include "../Weapon.h"

TEST(Weapon,Weapon_Construct_Test){
    Weapon w(1,2,15,WeaponType::Sword);

    ASSERT_EQ(1,w.rect.getPosition().x);
    ASSERT_EQ(2,w.rect.getPosition().y);
    ASSERT_EQ(15,w.getStrenght());
    ASSERT_FALSE(w.isRare());
    ASSERT_FALSE(w.isLegendary());
    ASSERT_EQ(WeaponType::Sword,w.getWeapon());
}

TEST(Weapon,Weapon_setting_Test){
    Weapon w(0,0,18,WeaponType::Dagger);
    w.setStrenght(13);
    w.setRare(true);
    w.setLegendary(true);

    ASSERT_EQ(13,w.getStrenght());
    ASSERT_TRUE(w.isRare());
    ASSERT_TRUE(w.isLegendary());
    ASSERT_EQ(WeaponType::Dagger,w.getWeapon());
}

TEST(Weapon,Weapon_Using_Test) {
    Weapon *w = new Weapon(1, 2, 15, WeaponType::Sword, true, true);

    int damage = w->useWeapon();
    if(damage > w->getStrenght() - 13 && damage< w->getStrenght() + 13)
        SUCCEED();
    else if(damage == 0)
        SUCCEED();
    else
        FAIL();

}