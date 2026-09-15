#include <iostream>
#include "state.h"

int main() {
    State game;
    int loc;
    while (game.get_status() == InProgress) {
        game.print(std::cout);
        std::cout << game.get_turn()
                  << " to play. Where should they go?" 
                  << std::endl;
        if (std::cin >> loc)
            game = game.play(game.get_turn(), loc);
    }
    std::cout << "game status: " << game.get_status() << std::endl;
    return 0;
}