//
// Created by suraj on 3/6/22.
//
#include <gtest/gtest.h>

#include "../include/strings.cpp"

TEST(StringsTest, TrimShouldRemovePrefixWhitespaces) {
    EXPECT_EQ(ltrim(" 1234"), "1234");
}

TEST(StringsTest, TrimShouldRemoveSuffixWhitespaces) {
    EXPECT_EQ(rtrim("1234 "), "1234");
}

TEST(StringsTest, TrimShouldRemoveAllWhitespaces) {
    EXPECT_EQ(trim(" 1234 "), "1234");
}


