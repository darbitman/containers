#include <gtest/gtest.h>

#include "containers/FastLinkedList.hpp"

namespace helpers::containers {
namespace {

TEST(FastLinkedListTest, EmptyList) {
  FastLinkedList<uint32_t, 10> list;

  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list.max_size(), 10);
}

TEST(FastLinkedListTest, FullList) {
  FastLinkedList<uint32_t, 10> list;

  for (size_t i = 0; i < 10; ++i) {
    list.push_front(i);
  }

  EXPECT_EQ(list.size(), 10);
  EXPECT_EQ(list.max_size(), 10);
  EXPECT_TRUE(list.full());
}

TEST(FastLinkedListTest, ClearingList) {
  FastLinkedList<uint32_t, 10> list;

  for (size_t i = 0; i < 10; ++i) {
    list.push_front(i);
  }

  list.clear();

  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list.max_size(), 10);
}

TEST(FastLinkedList, ClearThenAdd) {
  FastLinkedList<uint32_t, 10> list;

  for (size_t i = 0; i < 10; ++i) {
    list.push_front(i);
  }

  list.clear();

  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list.max_size(), 10);

  list.push_front(3);
  ASSERT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 3);
}

TEST(FastLinkedList, Remove) {
  FastLinkedList<uint32_t, 10> list;

  list.push_front(3);
  list.push_front(3);
  list.push_front(3);
  list.push_front(2);

  list.remove(3);

  EXPECT_EQ(list.size(), 1);
}

}  // namespace
}  // namespace helpers::containers
