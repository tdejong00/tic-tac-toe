// implementation of tic-tac-toe class

#include "../include/tictactoe.h"


tictactoe::tictactoe() {
    // initialize board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            this->board[i][j] = mark::empty;
        }
    }

    this->player = mark::nought;
    this->opponent = mark::cross;
    this->current_player = this->opponent;
}

tictactoe::~tictactoe() {
    // TODO: Implement if necessary
}


void tictactoe::play_game(bool const &is_random_ai) {
    // repeat while board is not in a terminal state
    while (this->evaluate_board() == INT_MIN) {
        clear_terminal();

        // player's turn
        if (this->current_player == this->player) {
            this->draw_board();

            move mv = this->read_move();

            // do move and switch player
            this->board[mv.row][mv.column] = player;
            this->current_player = this->opponent;
        }
        // AI's turn
        else {
            move mv;
            
            if (is_random_ai) {
                mv = {-1, -1};
                while (!this->is_valid_move(mv)) {
                    std::random_device rd;
                    std::mt19937 rng(rd());
                    std::uniform_int_distribution<std::mt19937::result_type> dist(0,2);

                    int r = (int)dist(rng);
                    int c = (int)dist(rng);
                    mv = {r, c};
                }
            }
            else {
                mv = this->find_best_move();
            }

            // do move and switch player
            this->board[mv.row][mv.column] = opponent;
            this->current_player = this->player;
        }
    }

    clear_terminal();
    this->draw_board();

    int score = this->evaluate_board();

    // board is in terminal state, score cannot be INT_MIN
    assert(score != INT_MIN);

    switch (score) {
        case 0: std::cout << "It's a draw." << std::endl; break;
        case 10: std::cout << "Crosses won!" << std::endl; break;
        default: std::cout << "Noughts won!" << std::endl; break;        
    }
}


void tictactoe::draw_board() const {
    std::cout << APPNAME << " " << VERSION << std::endl << std::endl;

    std::cout << "  0   1   2 " << std::endl;
    for (int i = 0; i < SIZE; i++) {
        std::cout << i;
        for (int j = 0; j < SIZE; j++) {
            switch (this->board[i][j]) {
                case mark::nought: std::cout << " o "; break;
                case mark::cross: std::cout << " x "; break;            
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

    std::cout << std::endl << "You are playing as " << (this->player == mark::nought ? "noughts" : "crosses") << '.' << std::endl;
}


bool tictactoe::is_valid_move(move const &mv) const {
    if (mv.row < 0 || mv.row > 2 || mv.column < 0 || mv.column > 2) {
        return false;
    }
    return this->board[mv.row][mv.column] == mark::empty;
}


move tictactoe::read_move() const {    
    int row = -1, column = -1;

    std::cout << "Type a row number: ";
    std::cin >> row;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    while (row < 0 || row > 2) {
        std::cout << "Invalid row number. Type a row number between 0 and 2: ";
        std::cin >> row;
    }

    std::cout << "Type a column number: ";
    std::cin >> column;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    while (column < 0 || column > 2) {
        std::cout << "Invalid column number. Type a column number between 0 and 2: ";
        std::cin >> column;
    }

    move mv = {row, column};
    if (!this->is_valid_move(mv)) {
        std::cout << "Invalid move." << std::endl;
        mv = read_move();
    }
    return mv;    
}


bool tictactoe::is_filled() const {
    // check all filled
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (this->board[i][j] == mark::empty) {
                return false;
            }
        }
    }
    return true;
}


int tictactoe::evaluate_board() const {
    // check horizontals
    if (this->board[0][0] == this->board[0][1] && this->board[0][1] == this->board[0][2] && this->board[0][0] != mark::empty) return this->board[0][0];
    if (this->board[1][0] == this->board[1][1] && this->board[1][1] == this->board[1][2] && this->board[1][0] != mark::empty) return this->board[1][0];
    if (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != mark::empty) return this->board[2][0];

    // check verticals
    if (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != mark::empty) return this->board[0][0];
    if (this->board[0][1] == this->board[1][1] && this->board[1][1] == this->board[2][1] && this->board[0][1] != mark::empty) return this->board[0][1];
    if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != mark::empty) return this->board[0][2];

    // check diagonals
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != mark::empty) return this->board[0][0];
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != mark::empty) return this->board[0][2];

    // check draw
    if (this->is_filled()) {
        return 0;
    }

    // not a terminal state
    return INT_MIN;
}


move tictactoe::find_best_move() {
    int best_score = INT_MIN;
    move move = {-1, -1};

    // loop over all spaces and determine best move
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (this->board[i][j] != mark::empty) continue;

            // do move
            this->board[i][j] = opponent;

            bool is_maximizing = player == mark::cross;
            int score = is_maximizing ? maxi() : mini();

            // undo move
            this->board[i][j] = mark::empty;

            if (score > best_score) {
                best_score = score;
                move = {i, j};                    
            }
        }
    }

    return move;
}

int tictactoe::mini() {    
    int result = this->evaluate_board();

    // return score if board is in terminal state
    if (result != INT_MIN) {
        return result;
    }
    
    int best_score = INT_MAX;

    // loop over all spaces and determine score recursively
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (this->board[i][j] != mark::empty) continue;

            // do move
            this->board[i][j] = player;

            int score = maxi();

            // undo move
            this->board[i][j] = mark::empty;

            best_score = std::min(score, best_score);
        }
    }

    return best_score;
}

int tictactoe::maxi() {    
    int result = this->evaluate_board();

    // return score if board is in terminal state
    if (result != INT_MIN) {
        return result;
    }

    int best_score = INT_MIN;

    // loop over all spaces and determine score recursively
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (this->board[i][j] != mark::empty) continue;

            // do move
            this->board[i][j] = opponent;

            int score = mini();

            // undo move
            this->board[i][j] = mark::empty;

            best_score = std::max(score, best_score);
        }
    }

    return best_score;
}

void clear_terminal()  {
    #ifdef _WIN32
    system("cls");
    #elif __unix__ 
    system("clear");
    #endif
}