//
// Created by zuhxs on 2019/4/2.
//

#ifndef C_VERSION_CHESSBOARD_H
#define C_VERSION_CHESSBOARD_H

#include <iostream>
#include <vector>

using namespace std;

#define NEWBOARDCOLOR 0x0000000810000000
#define NEWBOARDOCCUPIED 0x0000001818000000
#define MAX_INT64 0xFFFFFFFFFFFFFFFF

#define SIMULATE_RANDOM 5


const int g_Weight[8][8] = {
        {100, 1, 50, 30, 30, 50, 1, 100},
        {1, 1, 30, 10, 10, 30, 1, 1},
        {50, 30, 20, 10, 10, 20, 30, 50},
        {30, 10, 20,  0, 0, 20, 10, 30},
        {30, 10, 20,  0, 0, 20, 10, 30},
        {50, 30, 20, 10, 10, 20, 30, 50},
        {1, 1, 30, 10, 10, 30, 1, 1},
        {100, 1, 50, 30, 30, 50, 1, 100}
};

//#define DEBUG  // make some assertions

class Chessboard {
private:
    bool current_color;
    uint_fast64_t board_color;
    uint_fast64_t board_occupied;
    bool is_end;

public:
    Chessboard();
    Chessboard(Chessboard *init);
    bool check_end();
    int black_num() const;   // return the number of black chess
    int white_num() const;   // return the number of white chess
    void get_possible_solutions(vector <char> &solutions) const;   // fill the vector with x1, y1, x2, y2, if no possible solutions, return empty vector
    int get_possible_solutions() const;   // return the number of the solutions
    bool make_move(int x, int y);    // make move at (x, y)
    bool if_movable(int x, int y) const;   // check if (x, y) is a legal move in current chessboard
    void get_next_position(int &x, int &y, int direction) const;
    bool if_possible_place(int x, int y) const;   // check if (x, y) is within the chessboard
    bool if_different_color(int x, int y) const;    // if (x, y) is a different color with the current color
    bool if_white(int x, int y) const;   // if (x, y) is white
    bool if_black(int x, int y) const;   // if (x, y) is black
    bool if_empty(int x, int y) const;   // if (x, y) is empty
    void make_reverse(int x, int y);     // reverse the board_color at (x, y)
    void set_color(bool color);          // set current color, MCTS use
    void set_bitmap(uint_fast64_t board_color, uint_fast64_t board_occupied);    // set bitmap, MCTS use
    bool get_current_color() const;      // get current color, MCTS use
    uint_fast64_t get_board_color() const;    // get board color, MCTS use
    uint_fast64_t get_board_occupied() const;  // get board bitmap, MCTS use
    int check_win() const;    // if tie, return 2, if black wins, return 1, if white wins, return 0
    void simulate_move();    // stimulate the value and select a move
    bool simulate();         // for MCTS use, stimulate the moving, if black wins, return 1, else return 0
    int next_posible_moves(int x, int y);   // after making move at (x, y), check the number of possible solutions
    bool get_is_end();
};


#endif //C_VERSION_CHESSBOARD_H
