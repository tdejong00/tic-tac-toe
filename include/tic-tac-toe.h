#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>

namespace tictactoe {
    const int SIZE = 3;
    const std::string APP_NAME = "Tic-Tac-Toe";
    const std::string VERSION = "v1.0.0";

    struct Move {
        int row;
        int column;
    };

    enum Mark {
        NOUGHT = -10,
        CROSS = 10,
        EMPTY
    };

    // Represents a Tic-Tac-Toe game against an AI.
    class Game {
        public:
            // Initializes a new instance of the game.
            Game(bool const&is_random, bool const& is_crosses);

            // Starts a tic-tac-toe game.
            void play();
            
        private:            
            Mark board_[SIZE][SIZE];
            Mark player_;
            Mark opponent_;
            Mark current_player_;
            bool is_random_;
            bool is_crosses_;

            // Resets the game state.
            void reset();

            // Draws the current game state to the output.
            void draw() const;

            // Determines whether a move is valid.
            bool isValidMove(Move const& mv) const;

            // Reads a row or column index from stdin.
            int readIndex(bool const& is_row) const;

            // Reads a move from stdin.
            Move readMove() const;

            // Evaluates the state of the board.
            // Returns 10 if noughts won, -10 if crosses won, 0 if 
            // its a draw, and INT_MIN when board is not in a terminal state.
            int evaluateBoard() const;

            // Finds the best possible move for the crosses player.
            Move findBestMoveCross();

            // Finds the best possible move for the noughts player.
            Move findBestMoveNought();

            // Minimum value part of the minimax-algorithm for deciding the best
            // possible score with alpha-beta pruning standardized by depth.
            int mini(int alpha, int beta, int depth);

            // Maximum value part of the minimax-algorithm for deciding the best
            // possible score with alpha-beta pruning standardized by depth.
            int maxi(int alpha, int beta, int depth);
    };    

    // Clears all text in the terminal.
    void clearTerminal();
}
#endif