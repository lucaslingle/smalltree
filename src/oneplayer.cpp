#include <iostream>
#include "state.hpp"
#include "tree.hpp"

int main() {
    State game;
    Tree tree;
    tree.grow();
    tree.eval();

    int action;
    while (game.get_status() == InProgress) {
        std::cout << game;
        std::cout << "Your turn. Where will you go?" << std::endl;

        if (std::cin >> action) {
            tree.user_play(game.get_turn(), action);
            game = game.play(game.get_turn(), action);
        } else {
            std::cerr << "Invalid input." << std::endl;
            return -1;
        }

        if (game.get_status() == InProgress) {
            action = tree.computer_play(game.get_turn());
            game = game.play(game.get_turn(), action);
        }
    }
    std::cout << game;
    std::cout << "Game status: " << status_to_string(game.get_status()) << std::endl;
    return 0;
}