//
// Created by zuhxs on 2019/4/2.
//

#include "chessboard.h"

Chessboard::Chessboard(){
    this->board_occupied = NEWBOARDOCCUPIED;
    this->board_color = NEWBOARDCOLOR;
    this->current_color = 1;
}

int Chessboard::black_num() const {
    int number;
    uint_fast64_t temp = this->board_color & this->board_occupied;
    for (int i = 0; i < 64; i++){
        number += temp & 1;
        temp >> 1;
    }
    return number;
}

int Chessboard::white_num() const {
    int number;
    uint_fast64_t temp = this->board_occupied & (this->board_color ^ this->board_occupied);
    for (int i = 0; i < 64; i++) {
        number += temp & 1;
        temp >> 1;
    }
}

void Chessboard::get_next_position(int &x, int &y, int direction) {
    if (direction == 0) {
        x--;
        y--;
    }
    else if (direction == 1) {
        y--;
    }
    else if (direction == 2) {
        x++;
        y--;
    }
    else if (direction == 3) {
        x++;
    }
    else if (direction == 4) {
        x++;
        y++;
    }
    else if (direction == 5) {
        y++;
    }
    else if (direction == 6) {
        x--;
        y++;
    }
    else if (direction == 7) {
        x--;
    }
}

void Chessboard::make_move(int x, int y) {
    int temp_x = x;
    int temp_y = y;
    for (int dir = 0; dir < 8; dir++) {
        this->get_next_position(temp_x, temp_y, dir);
        if 
    }





    board_occupied |= 1 << (x + y * 8);
    if (this->current_color){  // black move
        board_color |= 1 << (x + y * 8);
    }
    else{
        board_color &= (MAX_INT64 ^ (1 << (x + y * 8)));
    }
}

inline bool Chessboard::if_possible_place(int x, int y) const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}