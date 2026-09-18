#include <iostream>
#include "state.hpp"

int main() {
    State game;
    int action;
    while (game.get_status() == InProgress) {
        std::cout << game;
        std::cout << game.get_turn() << " to play. Where should they go?" << std::endl;
        
        if (std::cin >> action)
            game = game.play(game.get_turn(), action);
        else {
            std::cerr << "Invalid input." << std::endl;
            return -1;
        }
    }
    std::cout << "Game status: " << status_to_string(game.get_status()) << std::endl;
    return 0;
}