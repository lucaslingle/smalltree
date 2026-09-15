#include <iostream>
#include <tree.hpp>

int main() {
    Tree tree;
    tree.grow();
    tree.eval();
    std::cout << tree.get_value() << std::endl;
    return 0;
}