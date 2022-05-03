#include <gtest/gtest.h>


TEST(HEY,WAS_GEHT) {


    EXPECT_NEAR(6.6, 6.6, 0.000000001);
}

TEST(CAT,MEOW) {


    ASSERT_EQ("meow","wouf");
}

TEST(DOG,WOUF) {


    ASSERT_EQ("wouf","wouf");
}