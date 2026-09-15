#include <array>
#include <algorithm>
#include "state.h"

class Node {
friend class Tree; 
private:
    Node *parent;
    int prev_action;

    State state;
    int value;

    std::array<bool, 9> valid;
    std::array<int, 9> action_value = {};
    std::array<std::unique_ptr<Node>, 9> childrens = {};

    void populate_valid(const State &state);

    Node();
    Node(Node *p, int turn, int loc);
}

void populate_valid(const State &state) {
    for (int i = 0; i != 9; ++i)
        valid[i] = state.is_valid(state.get_turn(), i);
}

Node::Node() : 
    parent(nullptr), prev_action(-1), state(State()), value(0) 
{
    populate_valid();
}

Node::Node(Node *p, int turn, int loc) :
    parent(p), prev_action(loc), state(p->state.play(turn, loc)), value(0)
{
    // set up the new node
    populate_valid();

    // backtrack if terminal node
    auto status = state.get_status();
    if (status != InProgress) {
        if (status == Tie)
            value = 0;
        else
            value = (status == PlusWon) ? 1 : -1;

        while (p != nullptr) {
            if (p->state.get_turn() == value) {
                p->action_value[a] = value;
            }
            a = p->prev_action;
            p = p->parent;
        }
    }
}