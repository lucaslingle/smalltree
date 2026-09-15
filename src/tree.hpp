#include <array>
#include <algorithm>
#include <queue>
#include "state.hpp"

class Node {
friend class Tree; 
private:
    Node();
    Node(std::shared_ptr<Node> p, int turn, int loc);
    void populate_valid(const State &state);
    void eval();

    Node *parent;
    int prev_action;
    State state;
    int value;
    std::array<bool, 9> valid;
    std::array<std::shared_ptr<Node>, 9> childrens = {};
};

class Tree {
private:
    std::shared_ptr<Node> root = std::shared_ptr<Node>(new Node());
public:
    Tree() = default;
    double get_value() const { return root->value; }
    void grow();
    void eval();
};
