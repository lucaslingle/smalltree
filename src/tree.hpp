#pragma once
#include <array>
#include <algorithm>
#include <queue>
#include <memory>
#include "state.hpp"

class Node {
friend class Tree; 
private:
    Node();
    Node(Node* p, int turn, int action);
    void populate_valid(const State &state);
    void eval();

    Node *parent;
    int prev_action;
    State state;
    double value;
    std::array<bool, 9> valid;
    std::array<double, 9> action_values;
    std::array<std::unique_ptr<Node>, 9> childrens = {};
};

class Tree {
private:
    std::unique_ptr<Node> root = std::unique_ptr<Node>(new Node());
public:
    Tree() = default;
    double get_value() const { return root->value; }
    void grow();
    void eval();
    void user_play(int turn, int action);
    int computer_play(int turn);
};
