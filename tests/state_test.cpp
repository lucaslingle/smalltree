#include <gtest/gtest.h>
#include "state.hpp"

TEST(StateTest, InitialStateIsInProgressAndPlayerOneToMove) {
    State game;
    EXPECT_EQ(game.get_status(), InProgress);
    EXPECT_EQ(game.get_turn(), 1);
}

TEST(StateTest, PlayAdvancesTurnAndOccupiesSquare) {
    State game;
    State next = game.play(1, 4);
    EXPECT_EQ(next.get_turn(), -1);
    EXPECT_TRUE(next.is_valid(-1, 0));   // still open
    EXPECT_FALSE(next.is_valid(-1, 4));  // just occupied
}

TEST(StateTest, RowWinIsDetected) {
    State game;
    game = game.play(1, 0);
    game = game.play(-1, 3);
    game = game.play(1, 1);
    game = game.play(-1, 4);
    game = game.play(1, 2);  // completes top row for player 1
    EXPECT_EQ(game.get_status(), PlusWon);
}

TEST(StateTest, ColumnWinIsDetected) {
    State game;
    game = game.play(1, 0);
    game = game.play(-1, 1);
    game = game.play(1, 3);
    game = game.play(-1, 2);
    game = game.play(1, 6);  // completes left column for player 1
    EXPECT_EQ(game.get_status(), PlusWon);
}

TEST(StateTest, DiagonalWinIsDetected) {
    State game;
    game = game.play(1, 0);
    game = game.play(-1, 1);
    game = game.play(1, 4);
    game = game.play(-1, 2);
    game = game.play(1, 8);  // completes main diagonal for player 1
    EXPECT_EQ(game.get_status(), PlusWon);
}

TEST(StateTest, TieIsDetectedOnFullBoardWithNoWinner) {
    State game;
    game = game.play(1, 0);
    game = game.play(-1, 1);
    game = game.play(1, 2);
    game = game.play(-1, 4);
    game = game.play(1, 3);
    game = game.play(-1, 5);
    game = game.play(1, 7);
    game = game.play(-1, 6);
    game = game.play(1, 8);
    EXPECT_EQ(game.get_status(), Tie);
}

TEST(StateTest, IsValidRejectsWrongPlayersTurn) {
    State game;
    EXPECT_FALSE(game.is_valid(-1, 0));
    EXPECT_TRUE(game.is_valid(1, 0));
}

TEST(StateTest, IsValidRejectsOutOfRangeAction) {
    State game;
    EXPECT_FALSE(game.is_valid(1, -1));
    EXPECT_FALSE(game.is_valid(1, 9));
}

TEST(StateTest, PlayThrowsOnOccupiedSquare) {
    State game;
    game = game.play(1, 4);
    EXPECT_THROW(game.play(-1, 4), std::invalid_argument);
}

TEST(StateTest, PlayThrowsOnWrongTurn) {
    State game;
    EXPECT_THROW(game.play(-1, 0), std::invalid_argument);
}

TEST(StateTest, PlayThrowsWhenGameAlreadyOver) {
    State game;
    game = game.play(1, 0);
    game = game.play(-1, 3);
    game = game.play(1, 1);
    game = game.play(-1, 4);
    game = game.play(1, 2);  // PlusWon
    EXPECT_THROW(game.play(-1, 5), std::runtime_error);
}

TEST(StatusToStringTest, MapsEachStatus) {
    EXPECT_EQ(status_to_string(InProgress), "in progress");
    EXPECT_EQ(status_to_string(PlusWon), "1 won");
    EXPECT_EQ(status_to_string(MinusWon), "-1 won");
    EXPECT_EQ(status_to_string(Tie), "tie");
}
