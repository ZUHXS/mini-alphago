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
#define DEBUG

class Chessboard {
private:
    bool current_color;
    uint_fast64_t board_color;
    uint_fast64_t board_occupied;
    int is_end;
public:
    Chessboard();
    int black_num() const;
    int white_num() const;
    void get_possible_solutions(vector <char> &solutions) const;
    bool make_move(int x, int y);
    bool if_movable(int x, int y) const;
    void get_next_position(int &x, int &y, int direction) const;
    bool if_possible_place(int x, int y) const;
    bool if_different_color(int x, int y) const;
    bool if_white(int x, int y) const;
    bool if_black(int x, int y) const;
    bool if_empty(int x, int y) const;
    void make_reverse(int x, int y);
};


#endif //C_VERSION_CHESSBOARD_H
