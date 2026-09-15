#include <array>
#include <algorithm>
#include <queue>
#include "tree.hpp"

void Node::populate_valid(const State &state) {
    for (int i = 0; i != 9; ++i)
        valid[i] = state.is_valid(state.get_turn(), i);
}

Node::Node() : 
    parent(nullptr), prev_action(-1), state(State()), value(0) 
{
    populate_valid(state);
}

Node::Node(std::shared_ptr<Node> p, int turn, int loc) :
    parent(p.get()), prev_action(loc), state(p->state.play(turn, loc)), value(0)
{
    // set up the new node
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
        double val = (is_max) ? -100 : 100;
        for (int i = 0; i != 9; ++i)
            if (valid[i]) {
                childrens[i]->eval();
                double val_i = childrens[i]->value;
                val = (is_max) ? std::max(val_i, val) : std::min(val_i, val);
            }
        value = val;
    }
}

void Tree::grow() {
    // breadth-first search
    std::shared_ptr<Node> node;
    std::queue<std::shared_ptr<Node>> q;
    q.push(root);
    while (!q.empty()) {
        node = q.front();
        q.pop();
        for (int i = 0; i != 9; ++i) {
            if (node->valid[i] && node->childrens[i] == nullptr) {
                node->childrens[i] = std::shared_ptr<Node>(new Node(node, node->state.get_turn(), i));
                q.push(node->childrens[i]);
            }
        }
    }
}

void Tree::eval() {
    root->eval();
}
