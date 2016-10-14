//
// Created by Francesco Amorosini on 28/09/16.
//

#include "gtest/gtest.h"
#include "../Map.h"

TEST(Map, Map_Constructor_Test){
    Map map (10,30);

    ASSERT_EQ(map.getWidth(),10);
    ASSERT_EQ(map.getHeight(),30);
    ASSERT_THROW(Map map(0,40), std::invalid_argument);
    ASSERT_THROW(Map map(-13,50), std::invalid_argument);
}

TEST(Map, Map_Setting_Test){
    Map map(10,30);
    map.setTile(9,20,false);

    ASSERT_EQ(map.getHeight(),30);
    ASSERT_EQ(map.getWidth(),10);
    ASSERT_FALSE(map.getTile(9,20)->isWalkable());
    ASSERT_THROW(map.setTile(22,-3,true),RangeException);
    ASSERT_NO_THROW(map.getTile(9,19));
    ASSERT_THROW(map.getTile(10,30),RangeException);
}