//
// Created by zuhxs on 2019/4/2.
//

#ifndef C_VERSION_CHESSBOARD_H
#define C_VERSION_CHESSBOARD_H

#include <iostream>

using namespace std;

#define NEWBOARDCOLOR 0x0000000810000000
#define NEWBOARDOCCUPIED 0x0000001818000000
#define MAX_INT64 0xFFFFFFFFFFFFFFFF


class Chessboard {
private:
    int current_color;
    uint_fast64_t board_color;
    uint_fast64_t board_occupied;
    int is_end;
public:
    Chessboard();
    int black_num() const;
    int white_num() const;
    void get_possible_solutions(vector <char> &solutions) const;
    void make_move(int x, int y);
    void get_next_position(int &x, int &y, int direction);
    bool if_possible_place(int x, int y) const;
};


#endif //C_VERSION_CHESSBOARD_H
