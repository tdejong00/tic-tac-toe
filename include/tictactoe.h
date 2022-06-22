#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>

// Namespace containing constants, structs, enums, and classes for the game Tic-Tac-Toe.
namespace tictactoe {
    const int SIZE = 3;
    const std::string APPNAME = "Tic-Tac-Toe";
    const std::string VERSION = "v1.0.0";

    // Structure representing a move.
    struct move {
        int row;
        int column;
    };

    // Type of mark on the space in the grid.
    enum mark {
        nought = -10,
        cross = 10,
        empty
    };

    // Class containing functions for playing the game Tic-Tac-Toe.
    class game {
        public:
            // Initializes a new instance of the game.
            game(bool const&is_random, bool const& is_crosses);

            // Starts a tic-tac-toe game.
            void play();
            
        private:
            // The board containing noughts and crosses.
            mark board[SIZE][SIZE]; 

             // Mark of the player.
            mark player;

            // Mark of the opponent.
            mark opponent;

            // Mark of the current player.
            mark current_player;

            // Property indicating whether the AI is making random decisions.
            bool is_random; 

            // Property indicating whether the player is playing as crosses.
            bool is_crosses; 

            // Resets the game state.
            void reset();

            // Draws the current game state to the output.
            void draw() const;

            // Determines whether a move is valid.
            bool is_valid_move(move const &mv) const;

            // Reads a row or column index from stdin.
            int read_index(bool const &is_row) const;

            // Reads a move from stdin.
            move read_move() const;

            // Evaluates the state of the board.
            // Returns 10 if noughts won, -10 if crosses won, or 0 if its a draw.
            // Returns INT_MIN  when board is not in a terminal state.
            int evaluate_board() const;

            // Finds the best possible move for the crosses player.
            move find_best_move_cross();

            // Finds the best possible move for the noughts player.
            move find_best_move_nought();

            // Minimum value part of the minimax-algorithm for deciding the best
            // best possible score with alpha-beta pruning standardized by depth.
            int mini(int alpha, int beta, int depth);

            // Maximum value part of the minimax-algorithm for deciding the best
            // best possible score with alpha-beta pruning standardized by depth.
            int maxi(int alpha, int beta, int depth);
    };    

    // Clears all text in the terminal.
    void clear_terminal();
}
#endif