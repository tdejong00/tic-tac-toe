// definition of tic-tac-toe class

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <climits>
#include <random>
#include <cassert>

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

// Class containing functions for playing a tic-tac-toe game against an AI.
class tictactoe {
    public:
        // Initializes a new instance of the tictactoe class with an initialized board.
        tictactoe();

        // Destroys the instance of the tictactoe class.
        ~tictactoe();

        // Starts the tic-tac-toe game against the AI.
        void play_game(bool const &is_random_ai);
        
    private:
        mark board[SIZE][SIZE]; // The board containing noughts and crosses.
        mark player; // Mark of the player.
        mark opponent; // Mark of the opponent.
        mark current_player; // Mark of the current player.
        
        // Writes a string representation of the board to the output.
        void draw_board(mark b[SIZE][SIZE]) const;

        // Determines whether a move is valid.
        bool is_valid_move(move const &mv) const;

        // Read a move from input of the user.
        move read_move() const;     

        // Determines if the board is completely filled.
        bool is_filled(mark b[SIZE][SIZE]) const;

        // Evaluates a the state of the board.
        // Returns 10 if noughts won, -10 if crosses won, or 0 if its a draw.
        // Returns INT_MIN  when board is not in a terminal state.
        int evaluate_board(mark b[SIZE][SIZE]) const;

        // Finds the best possible move for the AI.
        move find_best_move(mark b[SIZE][SIZE]);

        // Minimum value part of the minimax-algorithm for deciding the best possible score.
        int mini(mark b[SIZE][SIZE]);

        // Maximum value part of the minimax-algorithm for deciding the best possible score.
        int maxi(mark b[SIZE][SIZE]);        

        // Clears all text in terminal.
        void clear_terminal() const;
};

#endif