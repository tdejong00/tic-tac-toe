// definition of tic-tac-toe class

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <ctime>
#include <climits>
#include <random>

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
    nought,
    cross,
    empty
};

// Class containing functions for playing a tic-tac-toe game against an AI using the minimax-algorithm.
class tictactoe {
    public:
        // Initializes a new instance of the tictactoe class with an initialized board.
        tictactoe();

        // Destroys the instance of the tictactoe class.
        ~tictactoe();

        // Writes a string representation of the board to the output.
        void draw_board(mark b[SIZE][SIZE]) const;

        // Determines if the board is completely filled.
        bool is_filled(mark b[SIZE][SIZE]) const;

        // Determines if the board is in a terminal state.
        bool is_terminal_state(mark b[SIZE][SIZE]) const;

        // Evaluates a terminal state of the board.
        // Returns 10 if noughts won, -10 if crosses won, and 0 if its a draw.
        int evaluate_board(mark b[SIZE][SIZE]) const;

        // Starts the tic-tac-toe game against the AI.
        void play_game(bool const &is_random_ai);

        // Minimax-algorithm for deciding the best possible score.
        int minimax(mark b[SIZE][SIZE], bool is_maximizing);

        // Finds the best possible move for the AI.
        move find_best_move(mark b[SIZE][SIZE]);
    private:
        // The board containing noughts and crosses.
        mark board[SIZE][SIZE];

        // Mark of the player.
        mark player;
        // Mark of the opponent.
        mark opponent;
        // Mark of the current player.
        mark current_player;

        // Read a move from input of the user.
        move read_move() const;

        // Marks the place on the board with the give mark.
        void do_move(move const &mv, mark const &mk);

        // Determines whether a move is valid.
        bool is_valid_move(move const &mv) const;

        // Determines score based on a mark.
        int determine_score(mark const &mk) const;

        // Clears all text in terminal.
        void clear_terminal() const;
};

#endif