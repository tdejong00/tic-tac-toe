#include "../include/tic-tac-toe.h"

#include <iostream>
#include <climits>
#include <random>
#include <cassert>

namespace tictactoe {
    Game::Game(bool const &is_random, bool const &is_crosses) {
        this->is_random_ = is_random;
        this->is_crosses_ = is_crosses;

        // set correct marks
        this->player_ = is_crosses ? Mark::CROSS : Mark::NOUGHT;
        this->opponent_ = is_crosses ? Mark::NOUGHT : Mark::CROSS;

        this->reset();
    }

    void Game::play() {

        // repeat while board is not in a terminal state
        while (this->evaluateBoard() == INT_MIN) {
            clearTerminal();

            // player's turn
            if (this->current_player_ == this->player_) {
                this->draw();

                Move mv = this->readMove();

                // do move and switch player
                this->board_[mv.row][mv.column] = player_;
                this->current_player_ = this->opponent_;
            }
            // AI's turn
            else {
                Move mv;
                
                if (this->is_random_) {
                    mv = {-1, -1};
                    while (!this->isValidMove(mv)) {
                        std::random_device rd;
                        std::mt19937 rng(rd());
                        std::uniform_int_distribution<std::mt19937::result_type> dist(0,2);

                        int r = (int)dist(rng);
                        int c = (int)dist(rng);
                        mv = {r, c};
                    }
                }
                else if (this->is_crosses_) {

                    mv = this->findBestMoveNought();
                }
                else {
                    mv = this->findBestMoveCross();
                }

                // do move and switch player
                this->board_[mv.row][mv.column] = opponent_;
                this->current_player_ = this->player_;
            }
        }

        clearTerminal();
        this->draw();

        int score = this->evaluateBoard();

        // board is in terminal state, score cannot be INT_MIN
        assert(score != INT_MIN);

        switch (score) {
            case 0: std::cout << "It's a draw." << std::endl; break;
            case 10: std::cout << "Crosses won!" << std::endl; break;
            default: std::cout << "Noughts won!" << std::endl; break;
        }
    }

    void Game::reset() {
        // reset board
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                this->board_[i][j] = Mark::EMPTY;
            }
        }

        // reset current player
        this->current_player_ = Mark::CROSS;
    }

    void Game::draw() const {
        std::cout << APP_NAME << " " << VERSION << std::endl << std::endl;

        std::cout << "  0   1   2 " << std::endl;
        for (int i = 0; i < SIZE; i++) {
            std::cout << i;
            for (int j = 0; j < SIZE; j++) {
                switch (this->board_[i][j]) {
                    case Mark::NOUGHT: std::cout << " o "; break;
                    case Mark::CROSS: std::cout << " x "; break;
                    default: std::cout << "   "; break;
                }
                if (j < 2) {
                    std::cout << "|";
                }
            }
            std::cout << std::endl;
            if (i < 2) {
                std::cout << " ---+---+---" << std::endl;
            }
        }

        std::string player_mark = (this->player_ == Mark::NOUGHT ? "noughts" : "crosses");
        std::cout << std::endl << "You are playing as " << player_mark << '.' << std::endl;
    }

    bool Game::isValidMove(Move const& mv) const {
        if (mv.row < 0 || mv.row > 2 || mv.column < 0 || mv.column > 2) {
            return false;
        }
        return this->board_[mv.row][mv.column] == Mark::EMPTY;
    }

    int Game::readIndex(bool const& is_row) const {
        char index;

        std::cout << "Type a " << (is_row ? "row" : "column") << " number: ";
        std::cin >> index;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');

        while (index < '0' || index > '2') {
            std::cout << "Invalid " << (is_row ? "row" : "column") <<" number. ";
            std::cout << "Type a " << (is_row ? "row" : "column") << " number between 0 and 2: ";
            std::cin >> index;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        return index - '0';
    }

    Move Game::readMove() const {
        int row = readIndex(true);
        int column = readIndex(false);

        Move mv = {row, column};
        if (!this->isValidMove(mv)) {
            std::cout << "Invalid move." << std::endl;
            mv = readMove();
        }
        return mv;
    }

    int Game::evaluateBoard() const {
        // check horizontals
        for (int i = 0; i < SIZE; i++) {
            if (this->board_[i][0] == this->board_[i][1] && 
                this->board_[i][1] == this->board_[i][2] && 
                this->board_[i][0] != Mark::EMPTY) {
                return this->board_[i][0];
            } 
        }

        // check verticals
        for (int j = 0; j < SIZE; j++) {
            if (this->board_[0][j] == this->board_[1][j] && 
                this->board_[1][j] == this->board_[2][j] && 
                this->board_[0][j] != Mark::EMPTY) {
                return this->board_[0][j];
            }
        }

        // check diagonals
        for (int k : {0,2}) {
            if (this->board_[0][k] == this->board_[1][1] && 
                this->board_[1][1] == this->board_[2][2-k] && 
                this->board_[0][k] != Mark::EMPTY) {
                return this->board_[0][k];
            }
        }

        // check if entire board is filled
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this->board_[i][j] == Mark::EMPTY) {
                    return INT_MIN;
                }
            }
        }
        return 0;
    }

    Move Game::findBestMoveCross() {
        int best_score = INT_MIN;
        Move move = {-1, -1};

        // loop over all spaces and determine best move
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this->board_[i][j] != Mark::EMPTY) continue;

                // do move
                this->board_[i][j] = Mark::CROSS;

                int score = mini(INT_MIN, INT_MAX, 0);

                // undo move
                this->board_[i][j] = Mark::EMPTY;

                if (score > best_score) {
                    best_score = score;
                    move = {i, j};
                }
            }
        }

        return move;
    }

    Move Game::findBestMoveNought() {
        int best_score = INT_MAX;
        Move move = {-1, -1};

        // loop over all spaces and determine best move
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this->board_[i][j] != Mark::EMPTY) continue;

                // do move
                this->board_[i][j] = Mark::NOUGHT;

                int score = maxi(INT_MAX, INT_MIN, 0);

                // undo move
                this->board_[i][j] = Mark::EMPTY;

                if (score < best_score) {
                    best_score = score;
                    move = {i, j};
                }
            }
        }

        return move;
    }

    int Game::mini(int alpha, int beta, int depth) {
        int result = this->evaluateBoard();

        // return score if board is in terminal state
        if (result != INT_MIN) {
            return result - depth;
        }
        
        int best_score = INT_MAX;

        // loop over all spaces and determine score recursively
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this->board_[i][j] != Mark::EMPTY) continue;

                // do move
                this->board_[i][j] = Mark::NOUGHT;

                int score = maxi(alpha, beta, depth + 1);

                // undo move
                this->board_[i][j] = Mark::EMPTY;

                best_score = std::min(score, best_score);

                beta = std::min(beta, best_score);
                if (beta <= alpha) {
                    break;
                }
            }
        }

        return best_score;
    }

    int Game::maxi(int alpha, int beta, int depth) {
        int result = this->evaluateBoard();

        // return score if board is in terminal state
        if (result != INT_MIN) {
            return result + depth;
        }

        int best_score = INT_MIN;

        // loop over all spaces and determine score recursively
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this->board_[i][j] != Mark::EMPTY) continue;

                // do move
                this->board_[i][j] = Mark::CROSS;

                int score = mini(alpha, beta, depth + 1);

                // undo move
                this->board_[i][j] = Mark::EMPTY;

                best_score = std::max(score, best_score);

                alpha = std::max(alpha, best_score);
                if (beta <= alpha) {
                    break;
                }
            }
        }

        return best_score;
    }

    void clearTerminal()  {
        #ifdef _WIN32
        system("cls");
        #elif __unix__ 
        system("clear");
        #endif
    }
}