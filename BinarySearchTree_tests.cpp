#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

TEST(test_empty_tree) {
    BinarySearchTree<int> t;
    ASSERT_TRUE(t.empty());
    ASSERT_EQUAL(t.size(), 0u);
    ASSERT_EQUAL(t.height(), 0u);
    ASSERT_TRUE(t.begin() == t.end());
    ASSERT_TRUE(t.check_sorting_invariant());
}

TEST(test_single_insert) {
    BinarySearchTree<int> t;
    auto it = t.insert(5);

    ASSERT_FALSE(t.empty());
    ASSERT_EQUAL(t.size(), 1u);
    ASSERT_EQUAL(t.height(), 1u);
    ASSERT_TRUE(t.check_sorting_invariant());

    ASSERT_EQUAL(*it, 5);
    ASSERT_TRUE(t.begin() != t.end());
    ASSERT_EQUAL(*t.begin(), 5);

    auto it2 = t.begin();
    ++it2;
    ASSERT_TRUE(it2 == t.end());
}

TEST(test_multiple_insert_balanced) {
    BinarySearchTree<int> t;
    t.insert(4);
    t.insert(2);
    t.insert(6);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(7);

    ASSERT_EQUAL(t.size(), 7u);
    ASSERT_EQUAL(t.height(), 3u);
    ASSERT_TRUE(t.check_sorting_invariant());

    std::stringstream inorder;
    t.traverse_inorder(inorder);
    ASSERT_EQUAL(inorder.str(), "1 2 3 4 5 6 7 ");

    std::stringstream preorder;
    t.traverse_preorder(preorder);
    ASSERT_EQUAL(preorder.str(), "4 2 1 3 6 5 7 ");
}

TEST(test_min_max_and_find) {
    BinarySearchTree<int> t;
    t.insert(10);
    t.insert(5);
    t.insert(20);
    t.insert(15);
    t.insert(30);

    ASSERT_TRUE(t.find(10) != t.end());
    ASSERT_TRUE(t.find(5) != t.end());
    ASSERT_TRUE(t.find(15) != t.end());
    ASSERT_TRUE(t.find(30) != t.end());
    ASSERT_TRUE(t.find(100) == t.end());

    auto min_it = t.min_element();
    auto max_it = t.max_element();
    ASSERT_TRUE(min_it != t.end());
    ASSERT_TRUE(max_it != t.end());
    ASSERT_EQUAL(*min_it, 5);
    ASSERT_EQUAL(*max_it, 30);
}

TEST(test_min_greater_than) {
    BinarySearchTree<int> t;
    int vals[] = {10, 5, 20, 15, 30};
    for (int v : vals) {
        t.insert(v);
    }

    auto it = t.min_greater_than(10);
    ASSERT_TRUE(it != t.end());
    ASSERT_EQUAL(*it, 15);

    it = t.min_greater_than(9);
    ASSERT_TRUE(it != t.end());
    ASSERT_EQUAL(*it, 10);

    it = t.min_greater_than(29);
    ASSERT_TRUE(it != t.end());
    ASSERT_EQUAL(*it, 30);

    it = t.min_greater_than(30);
    ASSERT_TRUE(it == t.end());
}

TEST(test_check_sorting_invariant_break) {
    BinarySearchTree<int> t;
    t.insert(1);
    t.insert(0);

    *t.begin() = 2;
    ASSERT_FALSE(t.check_sorting_invariant());
}

TEST(test_copy_constructor_and_assignment) {
    BinarySearchTree<int> t1;
    t1.insert(2);
    t1.insert(1);
    t1.insert(3);

    BinarySearchTree<int> t2(t1);
    ASSERT_EQUAL(t2.size(), 3u);
    ASSERT_TRUE(t2.check_sorting_invariant());

    *t1.find(2) = 10;
    ASSERT_TRUE(t2.find(2) != t2.end());
    ASSERT_TRUE(t2.find(10) == t2.end());

    BinarySearchTree<int> t3;
    t3.insert(100);
    t3 = t2;
    ASSERT_EQUAL(t3.size(), 3u);
    ASSERT_TRUE(t3.check_sorting_invariant());
}

TEST_MAIN()
