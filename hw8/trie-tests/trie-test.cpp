//
// trie-test
//
//     Created: 11/29/18
//      Author: Matthew Treadwell
//

#include "gtest/gtest.h"
#include "Trie.h"

// Mainly meant to be tested for memory leaks with valgrind
// Not much assertion checking
class TrieSimple : public ::testing::Test {
protected:
    TrieSet *trie;

    void SetUp() override {
        trie = new TrieSet;
    }

    void TearDown() override {
        delete trie;
    }
};

// Important: These tests rely on a 100% working prefix function
class TrieHard : public TrieSimple {
protected:
    void checkInsert(const std::string &ins) {
        trie->insert(ins);
        EXPECT_TRUE(trie->prefix(ins));
    }

};


TEST_F(TrieSimple, build) {
}

TEST_F(TrieSimple, isEmpty) {
    EXPECT_TRUE(trie->isEmpty());
}

TEST_F(TrieSimple, insert) {
    trie->insert("bob");
}

TEST_F(TrieSimple, insertCheck) {
    trie->insert("bob");
    EXPECT_TRUE(trie->prefix("bob") != nullptr);
}

TEST_F(TrieSimple, insertMultiple) {
    trie->insert("bob");
    trie->insert("jim");
}

TEST_F(TrieSimple, NotEmpty) {
    trie->insert("bob");
    EXPECT_TRUE(!trie->isEmpty());
}

TEST_F(TrieSimple, Remove) {
    trie->insert("bob");
    trie->remove("bob");
}

TEST_F(TrieSimple, FalseRemove) {
    trie->insert("bob");
    trie->remove("jim");
}

TEST_F(TrieSimple, LongRemove) {
    trie->insert("iammadscientist");
    trie->remove("iammadscientist");
}

TEST_F(TrieSimple, prefix) {
    trie->insert("bob");
    EXPECT_TRUE(trie->prefix("bob") != nullptr);
}

TEST_F(TrieHard, inserts) {
    checkInsert("he");
    checkInsert("hello");
    checkInsert("hellothere");
    checkInsert("bob");
}

TEST_F(TrieHard, combo) {
    EXPECT_TRUE(trie->isEmpty());
    checkInsert("he");
    checkInsert("hello");
    checkInsert("hellothere");
    checkInsert("bob");
    EXPECT_TRUE(!trie->isEmpty());

    trie->remove("hello");
    EXPECT_TRUE(trie->prefix("hello") != nullptr);
    trie->remove("he");
    EXPECT_TRUE(trie->prefix("he") != nullptr);
    trie->remove("hellothere");
    EXPECT_TRUE(trie->prefix("he") == nullptr);
    EXPECT_TRUE(trie->prefix("hello") == nullptr);
    EXPECT_TRUE(trie->prefix("hellothere") == nullptr);
    trie->remove("bob");
    EXPECT_TRUE(trie->isEmpty());
}

TEST_F(TrieHard, ReUseDeleted) {
    checkInsert("he");
    checkInsert("hello");
    trie->remove("hello");
    EXPECT_TRUE(trie->prefix("hello") == nullptr);
    checkInsert("hello");
    EXPECT_TRUE(trie->prefix("hel") != nullptr);
}