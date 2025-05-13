#include <gtest/gtest.h>

#include "vector.hpp"

using biv::Vector;

TEST(VectorTests, PushBackAndBasicOperations) {
    Vector<int> vec;
    EXPECT_EQ(vec.get_size(), 0U);

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.get_size(), 3U);
    EXPECT_TRUE(vec.has_item(1));
    EXPECT_TRUE(vec.has_item(2));
    EXPECT_TRUE(vec.has_item(3));
    EXPECT_FALSE(vec.has_item(4));
}

TEST(VectorTests, InsertValidAndInvalidPosition) {
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(30);

    bool inserted = vec.insert(1, 20);
    EXPECT_TRUE(inserted);
    EXPECT_EQ(vec.get_size(), 3U);
    EXPECT_TRUE(vec.has_item(20));

    inserted = vec.insert(5, 40);
    EXPECT_FALSE(inserted);
    EXPECT_EQ(vec.get_size(), 3U);
}

TEST(VectorTests, RemoveExistingAndNonExisting) {
    Vector<int> vec;
    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(15);

    bool removed = vec.remove_first(10);
    EXPECT_TRUE(removed);
    EXPECT_EQ(vec.get_size(), 2U);
    EXPECT_FALSE(vec.has_item(10));

    removed = vec.remove_first(100);
    EXPECT_FALSE(removed);
    EXPECT_EQ(vec.get_size(), 2U);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
