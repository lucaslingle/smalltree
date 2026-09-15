#include <iostream>
#include <stdexcept>
#include "state.hpp"

std::string statusToString(Status s) {
    switch (s) {
        case Status::InProgress: return "in progress";
        case Status::PlusWon:    return "1 won";
        case Status::MinusWon:   return "-1 won";
        default:                 return "tie";
    }
}

bool State::is_valid(int turn, int loc) const {
    if (get_status() != InProgress)
        return false;
    if (board[loc] != 0)
        return false;
    return true;
}

State State::play(int turn, int loc) const {
    if (get_status() != InProgress)
        throw std::invalid_argument("Game is not in progress.");
    if (board[loc] != 0)
        throw std::invalid_argument("Location is occupied.");
    return State(board, turn, loc);
}

std::ostream& State::print(std::ostream &ost) const {
    for (int i = 0; i != 9; ++i) {
        if (i % 3 == 0)
            ost << "\n";
        ost << board[i] << " ";
    }
    ost << std::endl;
    return ost;
}

Status State::get_status() const {
    for (int i = 0; i != 3; ++i) {
        // check row i
        if (board[3 * i + 0] == board[3 * i + 1] && board[3 * i + 1] == board[3 * i + 2]) {
            if (board[3 * i] == 1)
                return PlusWon;
            if (board[3 * i] == -1)
                return MinusWon;
        }
        // check column i
        if (board[0 + i] == board[3 + i] && board[3 + i] == board[6 + i]) {
            if (board[0 + i] == 1)
                return PlusWon;
            if (board[0 + i] == -1)
                return MinusWon;
        }
    }
    // check diagonals
    if (board[3 * 0 + 0] == board[3 * 1 + 1] && board[3 * 1 + 1] == board[3 * 2 + 2]) {
        if (board[3 * 0 + 0] == 1)
            return PlusWon;
        if (board[3 * 0 + 0] == -1)
            return MinusWon;
    }
    if (board[3 * 0 + 2] == board[3 * 1 + 1] && board[3 * 1 + 1] == board[3 * 2 + 0]) {
        if (board[3 * 0 + 2] == 1)
            return PlusWon;
        if (board[3 * 0 + 2] == -1)
            return MinusWon;
    }
    for (int i = 0; i != 9; ++i)
        if (board[i] == 0)
            return InProgress;
    return Tie;
}
