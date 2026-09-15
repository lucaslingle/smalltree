#include <iostream>
#include "state.hpp"
#include "tree.hpp"

int main() {
    State game;
    Tree tree;
    tree.grow();
    tree.eval();

    int loc;
    while (game.get_status() == InProgress) {
        game.print(std::cout);
        std::cout << "Your turn. Where will you go?"
                  << std::endl;
        if (std::cin >> loc) {
            auto turn = game.get_turn();
            game = game.play(turn, loc);
            tree.user_play(turn, loc);
        }

        if (game.get_status() == InProgress) {
            int loc = tree.computer_play(game.get_turn());
            game = game.play(game.get_turn(), loc);
        }
    }
    game.print(std::cout);
    std::cout << "game status: " << statusToString(game.get_status()) << std::endl;
    return 0;
}