//
// Created by zuhxs on 2019/4/4.
//

#include "MCTS.h"

MCTS::MCTS(Chessboard *init) {   // for the root node
    this->chessboard.set_bitmap(init->get_board_color(), init->get_board_occupied());
    this->chessboard.set_color(init->get_current_color());
    this->sti_times = 0;
    this->win_times = 0;
    this->parent = nullptr;
    this->first_children = nullptr;
    this->siblings = nullptr;
}