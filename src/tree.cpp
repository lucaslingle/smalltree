#include <array>
#include <algorithm>
#include <queue>
#include <stdexcept>
#include <memory>
#include "tree.hpp"

void Node::populate_valid(const State &state) {
    for (int i = 0; i != 9; ++i)
        valid[i] = state.is_valid(state.get_turn(), i);
}

Node::Node() : 
    parent(nullptr), prev_action(-1), state(State()), value(0.0) 
{
    populate_valid(state);
}

Node::Node(Node *p, int turn, int action) :
    parent(p), prev_action(action), state(p->state.play(turn, action)), value(0.0)
{
    populate_valid(state);
}

void Node::eval() {
    auto status = state.get_status();
    if (status != InProgress) {
        if (status == Tie)
            value = 0;
        else
            value = (status == PlusWon) ? 1 : -1;
    } else {
        bool is_max = (state.get_turn() == 1);
        double best_val = (is_max) ? -100 : 100;
        for (int i = 0; i != 9; ++i)
            if (valid[i]) {
                childrens[i]->eval();
                double val = childrens[i]->value;
                action_values[i] = val;
                best_val = (is_max) ? std::max(best_val, val) : std::min(best_val, val);
            } else {
                action_values[i] = (is_max) ? -100 : 100;
            }
        value = best_val;
    }
}

void Tree::grow() {
    // breadth-first search
    Node* node;
    std::queue<Node*> q;
    q.push(root.get());
    while (!q.empty()) {
        node = q.front();
        q.pop();
        for (int i = 0; i != 9; ++i) {
            if (node->valid[i] && node->childrens[i] == nullptr) {
                node->childrens[i] = std::unique_ptr<Node>(new Node(node, node->state.get_turn(), i));
                q.push(node->childrens[i].get());
            }
        }
    }
}

void Tree::eval() {
    root->eval();
}

void Tree::user_play(int turn, int action) { 
    if (root->state.get_status() != InProgress)
        throw std::runtime_error("Game is not in progress.");
    if (root->state.get_turn() != turn)
        throw std::invalid_argument("Wrong player for turn.");
    if (!root->state.is_valid(turn, action))
        throw std::invalid_argument("Invalid action."); 

    root = std::move(root->childrens[action]);
    root->parent = nullptr;
}

int Tree::computer_play(int turn) {
    if (root->state.get_status() != InProgress)
        throw std::runtime_error("Game is not in progress.");
    if (root->state.get_turn() != turn)
        throw std::invalid_argument("Wrong player for turn.");

    auto best = std::find(root->action_values.begin(), root->action_values.end(), root->value);
    int action = std::distance(root->action_values.begin(), best);

    // This check shouldnt trigger since game is InProgress
    // there should be at least one action whose action_value is not a mask value
    if (!root->state.is_valid(turn, action))
        throw std::invalid_argument("Invalid action.");

    root = std::move(root->childrens[action]);
    root->parent = nullptr;
    return action;
}
