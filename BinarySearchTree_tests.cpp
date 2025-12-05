#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

BinarySearchTree<int> copy_by_value(BinarySearchTree<int> t) {
    return t;
}

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

TEST(test_iterator_full_traversal) {
    BinarySearchTree<int> t;
    t.insert(4);
    t.insert(2);
    t.insert(6);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(7);

    std::stringstream ss;
    for (auto it = t.begin(); it != t.end(); ++it) {
        ss << *it << " ";
    }
    ASSERT_EQUAL(ss.str(), "1 2 3 4 5 6 7 ");
}

TEST(test_unbalanced_height_and_min_greater) {
    BinarySearchTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);

    ASSERT_EQUAL(t.size(), 5u);
    ASSERT_EQUAL(t.height(), 5u);

    auto min_it = t.min_element();
    auto max_it = t.max_element();
    ASSERT_TRUE(min_it != t.end());
    ASSERT_TRUE(max_it != t.end());
    ASSERT_EQUAL(*min_it, 1);
    ASSERT_EQUAL(*max_it, 5);

    auto it = t.min_greater_than(0);
    ASSERT_TRUE(it != t.end());
    ASSERT_EQUAL(*it, 1);

    it = t.min_greater_than(3);
    ASSERT_TRUE(it != t.end());
    ASSERT_EQUAL(*it, 4);

    it = t.min_greater_than(5);
    ASSERT_TRUE(it == t.end());
}

TEST(test_deep_sorting_invariant_violation) {
    BinarySearchTree<int> t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);
    t.insert(12);
    t.insert(18);

    auto it = t.find(3);
    ASSERT_TRUE(it != t.end());
    *it = 20;
    ASSERT_FALSE(t.check_sorting_invariant());
}

TEST(test_self_assignment_and_empty_copy) {
    BinarySearchTree<int> t;
    t.insert(1);
    t.insert(2);
    t = t;
    ASSERT_TRUE(t.check_sorting_invariant());
    ASSERT_EQUAL(t.size(), 2u);

    BinarySearchTree<int> e;
    BinarySearchTree<int> copy(e);
    ASSERT_TRUE(copy.empty());
    ASSERT_EQUAL(copy.size(), 0u);
    ASSERT_TRUE(copy.check_sorting_invariant());
}

TEST(test_copy_large_balanced_tree) {
    BinarySearchTree<int> t;
    int vals[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    for (int v : vals) {
        t.insert(v);
    }

    BinarySearchTree<int> c(t);
    ASSERT_EQUAL(c.size(), 15u);
    ASSERT_EQUAL(c.height(), 4u);
    ASSERT_TRUE(c.check_sorting_invariant());

    std::stringstream inorder_t;
    std::stringstream inorder_c;
    t.traverse_inorder(inorder_t);
    c.traverse_inorder(inorder_c);
    ASSERT_EQUAL(inorder_c.str(), inorder_t.str());
    ASSERT_EQUAL(inorder_c.str(), "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 ");
}

TEST(test_copy_large_unbalanced_tree) {
    BinarySearchTree<int> t;
    for (int i = 1; i <= 8; ++i) {
        t.insert(i);
    }

    BinarySearchTree<int> c(t);
    ASSERT_EQUAL(c.size(), 8u);
    ASSERT_EQUAL(c.height(), 8u);
    ASSERT_TRUE(c.check_sorting_invariant());

    std::stringstream inorder_t;
    std::stringstream inorder_c;
    t.traverse_inorder(inorder_t);
    c.traverse_inorder(inorder_c);
    ASSERT_EQUAL(inorder_c.str(), inorder_t.str());
    ASSERT_EQUAL(inorder_c.str(), "1 2 3 4 5 6 7 8 ");
}

TEST(test_copy_mutate_original_right_subtree) {
    BinarySearchTree<int> t1;
    t1.insert(4);
    t1.insert(2);
    t1.insert(6);
    t1.insert(1);
    t1.insert(3);
    t1.insert(5);
    t1.insert(7);

    BinarySearchTree<int> t2(t1);

    auto it_orig = t1.find(6);
    ASSERT_TRUE(it_orig != t1.end());
    *it_orig = 100;

    ASSERT_TRUE(t1.find(100) != t1.end());
    ASSERT_TRUE(t2.find(6) != t2.end());
    ASSERT_TRUE(t2.find(100) == t2.end());
}

TEST(test_copy_via_pass_by_value) {
    BinarySearchTree<int> t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);
    t.insert(12);
    t.insert(18);

    BinarySearchTree<int> c = copy_by_value(t);

    ASSERT_EQUAL(c.size(), 7u);
    ASSERT_TRUE(c.check_sorting_invariant());

    std::stringstream inorder_t;
    std::stringstream inorder_c;
    t.traverse_inorder(inorder_t);
    c.traverse_inorder(inorder_c);
    ASSERT_EQUAL(inorder_c.str(), inorder_t.str());
    ASSERT_EQUAL(inorder_c.str(), "3 5 7 10 12 15 18 ");
}

TEST(test_copy_then_insert_in_copy_only) {
    BinarySearchTree<int> t1;
    t1.insert(2);
    t1.insert(1);
    t1.insert(3);

    BinarySearchTree<int> t2(t1);

    t2.insert(0);

    ASSERT_EQUAL(t1.size(), 3u);
    ASSERT_EQUAL(t2.size(), 4u);

    ASSERT_TRUE(t1.find(0) == t1.end());
    ASSERT_TRUE(t2.find(0) != t2.end());

    ASSERT_TRUE(t1.check_sorting_invariant());
    ASSERT_TRUE(t2.check_sorting_invariant());
}

TEST(test_copy_then_insert_in_original_only) {
    BinarySearchTree<int> t1;
    t1.insert(2);
    t1.insert(1);
    t1.insert(3);

    BinarySearchTree<int> t2(t1);

    t1.insert(0);
    t1.insert(4);

    ASSERT_EQUAL(t1.size(), 5u);
    ASSERT_EQUAL(t2.size(), 3u);

    ASSERT_TRUE(t1.find(0) != t1.end());
    ASSERT_TRUE(t1.find(4) != t1.end());
    ASSERT_TRUE(t2.find(0) == t2.end());
    ASSERT_TRUE(t2.find(4) == t2.end());

    ASSERT_TRUE(t1.check_sorting_invariant());
    ASSERT_TRUE(t2.check_sorting_invariant());
}

TEST(test_chain_of_copies) {
    BinarySearchTree<int> t1;
    int vals[] = {5, 2, 8, 1, 3, 7, 9};
    for (int v : vals) {
        t1.insert(v);
    }

    BinarySearchTree<int> t2(t1);
    BinarySearchTree<int> t3(t2);

    ASSERT_EQUAL(t1.size(), 7u);
    ASSERT_EQUAL(t2.size(), 7u);
    ASSERT_EQUAL(t3.size(), 7u);

    std::stringstream in1, in2, in3;
    t1.traverse_inorder(in1);
    t2.traverse_inorder(in2);
    t3.traverse_inorder(in3);

    ASSERT_EQUAL(in1.str(), "1 2 3 5 7 8 9 ");
    ASSERT_EQUAL(in2.str(), in1.str());
    ASSERT_EQUAL(in3.str(), in1.str());

    ASSERT_TRUE(t1.check_sorting_invariant());
    ASSERT_TRUE(t2.check_sorting_invariant());
    ASSERT_TRUE(t3.check_sorting_invariant());
}

TEST_MAIN()
