#include <iostream>
#include <stdexcept>
#include <string>
#include "state.hpp"

std::string status_to_string(Status s) {
    switch (s) {
        case Status::InProgress: return "in progress";
        case Status::PlusWon:    return "1 won";
        case Status::MinusWon:   return "-1 won";
        default:                 return "tie";
    }
}

bool State::is_valid(int turn, int action) const {
    if (get_turn() != turn)
        return false;
    if (get_status() != InProgress)
        return false;
    if (action < 0 || 9 <= action)
        return false;
    if (board[action] != 0)
        return false;
    return true;
}

State State::play(int turn, int action) const {
    if (get_status() != InProgress)
        throw std::runtime_error("Game is not in progress.");
    if (get_turn() != turn)
        throw std::invalid_argument("Wrong player for turn.");
    if (!is_valid(turn, action))
        throw std::invalid_argument("Invalid action.");
    return State(board, turn, action);
}

std::ostream& operator<<(std::ostream &ost, const State &game) {
    for (int i = 0; i != 9; ++i) {
        if (i % 3 == 0)
            ost << "\n";
        ost << game.board[i] << " ";
    }
    ost << "\n";
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
