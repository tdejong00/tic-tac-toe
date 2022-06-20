#include "./include/tictactoe.h"
#include <cstring>

int main(int argc, char *argv[]) {
    bool is_random;
    if (argc == 2) {
        if (std::strcmp(argv[1], "--help") == 0) {
            std::cout << APPNAME << " " << VERSION << std::endl;
            std::cout << "Play a game of Tic-Tac-Toe against an AI." << std::endl;
            std::cout << std::endl;
            std::cout << "Usage: ./tic-tac-toe [AI METHOD]..." << std::endl;
            std::cout << std::endl;
            std::cout << "  -r, --random      AI makes random decisions" << std::endl;
            std::cout << "  -m, --minimax     AI uses minimax-algorithm for its decisions" << std::endl;
            std::cout << std::endl;
            std::cout << "By default, the AI uses the minimax-algorithm." << std::endl;
            std::cout << std::endl;
            std::cout << "Exit status:" << std::endl;
            std::cout << " 0 if OK" << std::endl;
            std::cout << " 1 if invalid argument or too many arguments" << std::endl;
            return 0;
        }
        else if (std::strcmp(argv[1], "--random") == 0 || std::strcmp(argv[1], "-r") == 0) {
            is_random = true;
        }
        else if (std::strcmp(argv[1], "--minimax") == 0 || std::strcmp(argv[1], "-m") == 0) {
            is_random = false;
        }
        else {
            std::cout << "tic-tac-toe: invalid argument '" << argv[1] << "'" << std::endl;
            return 1;
        }
    }
    else if (argc > 2) {
        std::cout << "tic-tac-toe: too many arguments were given" << std::endl;
        return 1;
    }

    tictactoe* ttt = new tictactoe;
    ttt->play_game(is_random);
    delete ttt;

    return 0;
}