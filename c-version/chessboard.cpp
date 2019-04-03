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
    int number = 0;
    uint_fast64_t temp = this->board_color & this->board_occupied;
    for (int i = 0; i < 64; i++){
        number += temp % 2;
        temp >>= 1;
    }
    return number;
}

int Chessboard::white_num() const {
    int number = 0;
    uint_fast64_t temp = this->board_occupied & (this->board_color ^ this->board_occupied);
    for (int i = 0; i < 64; i++) {
        number += temp % 2;
        temp >>= 1;
    }
    return number;
}

void Chessboard::get_next_position(int &x, int &y, int direction) const{
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

bool Chessboard::make_move(int x, int y) {
    int temp_x, temp_y;
    int if_movable = 0;
    for (int dir = 0; dir < 8; dir++) {
        temp_x = x;
        temp_y = y;
        int step = 0;
        this->get_next_position(temp_x, temp_y, dir);
        while (this->if_possible_place(temp_x, temp_y) && this->if_different_color(temp_x, temp_y)) {
            step += 1;
            this->get_next_position(temp_x, temp_y, dir);
        }
        if (step == 0) {
            continue;
        }
        if (!this->if_possible_place(temp_x, temp_y) || this->if_empty(temp_x, temp_y)) {  // can't reverse
            continue;
        }
        else {
            if_movable = 1;
            temp_x = x;
            temp_y = y;
            for (int i = 0; i < step; i++) {
                this->get_next_position(temp_x, temp_y, dir);
                this->make_reverse(temp_x, temp_y);
            }
        }
    }
    if (if_movable) {
        board_occupied |= 1LL << (x + y * 8);
        if (this->current_color) {  // black move
            board_color |= 1LL << (x + y * 8);
        } else {
            board_color &= (MAX_INT64 ^ (1LL << (x + y * 8)));
        }
        this->current_color = this->current_color ? 0 : 1;
    }
    return if_movable;
}


inline bool Chessboard::if_different_color(int x, int y) const {
    if (this->current_color)
        return if_white(x, y);
    else
        return if_black(x, y);
}

inline bool Chessboard::if_possible_place(int x, int y) const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

inline bool Chessboard::if_black(int x, int y) const {
    return this->board_occupied & (1LL << (x + y * 8)) && this->board_color & (1LL << (x + y * 8));
}

inline bool Chessboard::if_empty(int x, int y) const {
    return (~this->board_occupied) & (1LL << (x + y * 8));
}

inline bool Chessboard::if_white(int x, int y) const {
    return this->board_occupied & (1LL << (x + y * 8)) && (~this->board_color) & (1LL << (x + y * 8));
}

inline void Chessboard::make_reverse(int x, int y) {
#ifdef DEBUG
    if(!this->board_occupied & (1LL << (x + y * 8))){
        cout << "error occured in make reverse" << endl;
    }
#endif
    this->board_color ^= (1LL << (x + y * 8));
}

bool Chessboard::if_movable(int x, int y) const{
    int temp_x, temp_y;
    int if_movable = 0;
    if (!this->if_empty(x, y)) {
        return 0;
    }
    for (int dir = 0; dir < 8; dir++) {
        temp_x = x;
        temp_y = y;
        int step = 0;
        this->get_next_position(temp_x, temp_y, dir);
        while (this->if_possible_place(temp_x, temp_y) && this->if_different_color(temp_x, temp_y)) {
            step = 1;
            this->get_next_position(temp_x, temp_y, dir);
        }
        if (step == 0) {
            continue;
        }
        if (!this->if_possible_place(temp_x, temp_y) || this->if_empty(temp_x, temp_y)) {  // can't reverse
            continue;
        }
        else {
            if_movable = 1;
        }
    }
    return if_movable;
}

void Chessboard::get_possible_solutions(vector<char> &solutions) const {
    for (int i = 0; i < 8; i++) {
       for (int j = 0; j < 8; j++) {
           if (this->if_movable(i, j)) {
               solutions.push_back((char)i);
               solutions.push_back((char)j);
           }
       }
    }
}