#include "Map.hpp"
#include "unit_test_framework.hpp"

TEST(test_map_empty) {
    Map<std::string, int> m;
    ASSERT_TRUE(m.empty());
    ASSERT_EQUAL(m.size(), 0u);
    ASSERT_TRUE(m.begin() == m.end());
}

TEST(test_map_insert_and_find) {
    Map<std::string, int> m;

    auto res1 = m.insert({"apple", 3});
    ASSERT_TRUE(res1.second);
    ASSERT_EQUAL(res1.first->first, "apple");
    ASSERT_EQUAL(res1.first->second, 3);

    auto res2 = m.insert({"banana", 5});
    ASSERT_TRUE(res2.second);
    ASSERT_EQUAL(m.size(), 2u);

    auto res3 = m.insert({"apple", 10});
    ASSERT_FALSE(res3.second);
    ASSERT_EQUAL(m.size(), 2u);
    ASSERT_EQUAL(res3.first->second, 3);

    auto it = m.find("banana");
    ASSERT_TRUE(it != m.end());
    ASSERT_EQUAL(it->second, 5);

    auto it2 = m.find("orange");
    ASSERT_TRUE(it2 == m.end());
}

TEST(test_map_brackets_insert_and_update) {
    Map<std::string, int> m;

    m["x"] = 10;
    ASSERT_FALSE(m.empty());
    ASSERT_EQUAL(m.size(), 1u);
    ASSERT_EQUAL(m["x"], 10);

    m["x"] = 20;
    ASSERT_EQUAL(m["x"], 20);
    ASSERT_EQUAL(m.size(), 1u);

    int y = m["y"];
    ASSERT_EQUAL(y, 0);
    ASSERT_EQUAL(m.size(), 2u);
}

TEST(test_map_iteration_order) {
    Map<int, char> m;
    m.insert({2, 'b'});
    m.insert({1, 'a'});
    m.insert({3, 'c'});

    auto it = m.begin();

    ASSERT_TRUE(it != m.end());
    ASSERT_EQUAL(it->first, 1);
    ASSERT_EQUAL(it->second, 'a');
    ++it;
    ASSERT_TRUE(it != m.end());
    ASSERT_EQUAL(it->first, 2);
    ASSERT_EQUAL(it->second, 'b');
    ++it;
    ASSERT_TRUE(it != m.end());
    ASSERT_EQUAL(it->first, 3);
    ASSERT_EQUAL(it->second, 'c');
    ++it;
    ASSERT_TRUE(it == m.end());
}

TEST_MAIN()
