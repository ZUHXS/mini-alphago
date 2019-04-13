//
// Created by zuhxs on 2019/4/2.
//

#include "chessboard.h"

Chessboard::Chessboard(){
    this->board_occupied = NEWBOARDOCCUPIED;
    this->board_color = NEWBOARDCOLOR;
    this->current_color = 1;
    this->is_end = 0;
}


Chessboard::Chessboard(Chessboard *init) {
    this->board_occupied = init->get_board_occupied();
    this->board_color = init->get_board_color();
    this->current_color = init->get_current_color();
    this->is_end = init->get_is_end();
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
    // if x == - 1 && y == -1, means no move can be made, just reverse the color
    if (x == -1 && y == -1){

#ifdef DEBUG  // check if indeed no move can be made
        vector<char> temp;
        this->get_possible_solutions(temp);
        assert(temp.empty());  // if not empty, the function call is problematic
#endif

        this->current_color = this->current_color ? 0 : 1;
        // test if the opponent can make a legal move, if not, stop the game
        if (!this->get_possible_solutions()) {  // return value is 0, stop the game
            this->is_end = 1;  // end the game
        }
        return true;
    }
    if (!this->if_empty(x, y)) {  // can't move here
        return 0;
    }


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
#ifdef DEBUG
    assert(if_possible_place(x, y));
#endif
    return this->board_occupied & (1LL << (x + y * 8)) & this->board_color & (1LL << (x + y * 8));
}

inline bool Chessboard::if_empty(int x, int y) const {
#ifdef DEBUG
    assert(if_possible_place(x, y));
#endif
    return (~this->board_occupied) & (1LL << (x + y * 8));
}

inline bool Chessboard::if_white(int x, int y) const {
#ifdef DEBUG
    assert(if_possible_place(x, y));
#endif
    return this->board_occupied & (1LL << (x + y * 8)) & (~this->board_color) & (1LL << (x + y * 8));
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
    solutions.clear();
    for (int i = 0; i < 8; i++) {
       for (int j = 0; j < 8; j++) {
           if (this->if_movable(i, j)) {
               solutions.push_back((char)i);
               solutions.push_back((char)j);
           }
       }
    }
}

void Chessboard::set_bitmap(uint_fast64_t board_color, uint_fast64_t board_occupied) {
    this->board_occupied = board_occupied;
    this->board_color = board_color;
}

void Chessboard::set_color(bool color) {
    this->current_color = color;
}

uint_fast64_t Chessboard::get_board_color() const {
    return this->board_color;
}

uint_fast64_t Chessboard::get_board_occupied() const {
    return this->board_occupied;
}

bool Chessboard::get_current_color() const {
    return this->current_color;
}

int Chessboard::check_win() const {
    int black = this->black_num();
    int white = this->white_num();
    cout << black << " " << white << endl;
    if (white > black) {
        return 0;
    }
    else if (black > white) {
        return 1;
    }
    else {
        cout << "tie " << black << " " << white << endl;
        return 2;
    }
}

void Chessboard::stimulate_move() {
    vector<char> solutions;
    this->get_possible_solutions(solutions);

    vector<char> result;

    int flag = 0;
    int final_x, final_y;
    int final_number = 100;
    while (!solutions.empty()) {
        flag = 1;
        int y = solutions.back();
        solutions.pop_back();
        int x = solutions.back();
        solutions.pop_back();
        int number = this->next_posible_moves(x, y) + rand() % STIMULATE_RANDOM;
        //int number = rand() % STIMULATE_RANDOM;
        if (number < final_number) {
            final_number = number;
            final_x = x;
            final_y = y;
        }
    }    // here, final_x, final_y is our next move
    if (flag == 0) {
        final_x = -1;
        final_y = -1;
    }
    this->make_move(final_x, final_y);
    int total_number = this->white_num() + this->black_num();
}

int Chessboard::next_posible_moves(int x, int y) {
    int color = this->current_color;
    uint_fast64_t old_board_occupied = this->board_occupied;
    uint_fast64_t old_board_color = this->board_color;

    this->make_move(x, y);
    int number = this->get_possible_solutions();

    // reset the state information
    this->current_color = color;
    this->board_occupied = old_board_occupied;
    this->board_color = old_board_color;
    return number;
}

int Chessboard::get_possible_solutions() const {
    int number = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (this->if_movable(i, j)) {
                number += 1;
            }
        }
    }
    return number;
}

bool Chessboard::stimulate() {
    auto temp_chessboard = new Chessboard(this);
    int number = 0;
    while (1) {
        number += 1;
        if (temp_chessboard->is_end) {  // end of the game
            break;
        }
        temp_chessboard->stimulate_move();
    }
    bool win_situation = temp_chessboard->check_win();
    delete temp_chessboard;
    return win_situation;
}

bool Chessboard::check_end() {
    return this->is_end;
}

bool Chessboard::get_is_end() {
    return this->is_end;
}