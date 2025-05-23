#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using biv::DoublyLinkedList;

TEST(DoublyLinkedListTests, PushBackAndBasicOperations) {
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.get_size(), 0U);
    
    list.push_back(7);
    list.push_back(14);
    list.push_back(21);
    EXPECT_EQ(list.get_size(), 3U);
    EXPECT_TRUE(list.has_item(7));
    EXPECT_TRUE(list.has_item(14));
    EXPECT_TRUE(list.has_item(21));
    EXPECT_FALSE(list.has_item(28));
}

TEST(DoublyLinkedListTests, RemoveExistingAndNonExisting) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    bool removed = list.remove_first(20);
    EXPECT_TRUE(removed);
    EXPECT_EQ(list.get_size(), 2U);
    EXPECT_FALSE(list.has_item(20));
    
    removed = list.remove_first(100);
    EXPECT_FALSE(removed);
    EXPECT_EQ(list.get_size(), 2U);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}