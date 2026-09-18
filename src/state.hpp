#pragma once
#include <iostream>
#include <array>
#include <string>
using Board = std::array<int, 9>;

enum Status {
    InProgress,
    PlusWon,
    MinusWon,
    Tie
};

std::string status_to_string(Status s);

class State {
friend std::ostream& operator<<(std::ostream &, const State &);
public:
    State() = default;
    Status get_status() const;
    int get_turn() const { return turn; }
    bool is_valid(int turn, int action) const;
    State play(int turn, int action) const;
private:
    Board board = {};
    int turn = 1;
    State(const Board &b, int t, int action): 
        board(b), turn(-1 * t) { board[action] = t; }
};
