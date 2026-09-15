#include <iostream>
#include <array>
using Board = std::array<int, 9>;

enum Status {
    InProgress,
    PlusWon,
    MinusWon,
    Tie
};

class State {
public:
    State() = default;
    Status get_status() const;
    int get_turn() const { return turn; }
    bool is_valid(int turn, int loc) const;
    State play(int turn, int loc) const;
    std::ostream& print(std::ostream &ost) const;
private:
    Board board = {};
    int turn = 1;
    State(const Board &b, int t, int loc): 
        board(b), turn(-1 * t) { board[loc] = t; }
};
