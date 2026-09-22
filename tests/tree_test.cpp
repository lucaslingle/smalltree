#include <gtest/gtest.h>
#include "tree.hpp"

TEST(TreeTest, EmptyBoardIsAForcedDraw) {
    Tree tree;
    tree.grow();
    tree.eval();
    EXPECT_DOUBLE_EQ(tree.get_value(), 0.0);
}

TEST(TreeTest, ComputerPlayReturnsAnInBoundsAction) {
    Tree tree;
    tree.grow();
    tree.eval();
    tree.user_play(1, 4);
    int computer_action = tree.computer_play(-1);
    EXPECT_GE(computer_action, 0);
    EXPECT_LE(computer_action, 8);
}

TEST(TreeTest, UserPlayThrowsOnWrongTurn) {
    Tree tree;
    tree.grow();
    tree.eval();
    EXPECT_THROW(tree.user_play(-1, 0), std::invalid_argument);
}

TEST(TreeTest, UserPlayThrowsOnOutOfRangeAction) {
    Tree tree;
    tree.grow();
    tree.eval();
    EXPECT_THROW(tree.user_play(1, 9), std::invalid_argument);
    EXPECT_THROW(tree.user_play(1, -1), std::invalid_argument);
}

TEST(TreeTest, MinimaxAvoidsLosingWhenLossIsAvoidable) {
    Tree tree;
    tree.grow();
    tree.eval();
    tree.user_play(1, 0);
    tree.user_play(-1, 6);
    tree.user_play(1, 1);
    EXPECT_EQ(tree.computer_play(-1), 2);
}

TEST(TreeTest, MinimaxPicksWinningMoveWhenNoDelayedWinIsGuaranteeable) {
    Tree tree;
    tree.grow();
    tree.eval();
    tree.user_play(1, 0);
    tree.user_play(-1, 6);
    tree.user_play(1, 1);
    tree.user_play(-1, 7);
    EXPECT_EQ(tree.computer_play(1), 2);
}
