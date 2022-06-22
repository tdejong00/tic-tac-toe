#include <iostream>
#include <cstring>

#include "./include/tictactoe.h"

// Prints list of available command line arguments.
void printHelp() {
    std::cout << tictactoe::APP_NAME << " " << tictactoe::VERSION << std::endl;
    std::cout << "Play a game of Tic-Tac-Toe against an AI." << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: ./tic-tac-toe [OPTIONS]..." << std::endl;
    std::cout << std::endl;
    std::cout << "  --help" << std::endl;
    std::cout << "      Show help for all options" << std::endl;
    std::cout << std::endl;
    std::cout << "  --version" << std::endl;
    std::cout << "      Show version number of this application" << std::endl;
    std::cout << std::endl;
    std::cout << "  --method=<r|m> [default: m]" << std::endl;
    std::cout << "      Set the method of the AI to either 'r' (AI makes random decisions) or 'm' (AI uses the minimax-algorithm)" << std::endl;
    std::cout << std::endl;
    std::cout << "  --player=<x|o> [default: o]" << std::endl;
    std::cout << "      Set the mark of the player to either 'x' (crosses) or 'o' (noughts)." << std::endl;
    std::cout << std::endl;
    std::cout << "Exit status:" << std::endl;
    std::cout << " 0 if OK" << std::endl;
    std::cout << " 1 if invalid argument or too many arguments" << std::endl;
}

int main(int argc, char *argv[]) {
    bool is_random = false;
    bool is_crosses = false;
    if (argc > 4) {
        std::cout << "tic-tac-toe: too many arguments were given, use --help for a list of accepted arguments" << std::endl;
        return 1;
    }
    else if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (std::strcmp(argv[i], "--help") == 0) {
                printHelp();
                return 0;
            }
            if (std::strcmp(argv[i], "--version") == 0) {
                std::cout << tictactoe::APP_NAME << " " << tictactoe::VERSION << std::endl;
                return 0;
            }
            else if (std::strcmp(argv[i], "--method=r") == 0) {
                is_random = true;
            }
            else if (std::strcmp(argv[i], "--method=m") == 0) {
                is_random = false;
            }
            else if (std::strcmp(argv[i], "--player=x") == 0) {
                is_crosses = true;
            }
            else if (std::strcmp(argv[i], "--player=o") == 0) {
                is_crosses = false;
            }
            else {
                std::cout << "tic-tac-toe: invalid argument '" << argv[1] << "', use --help for a list of accepted arguments" << std::endl;
                return 1;
            }
        }
    }

    tictactoe::Game game(is_random, is_crosses);
    game.play();

    return 0;
}