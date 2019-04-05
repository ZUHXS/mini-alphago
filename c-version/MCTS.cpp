//
// Created by zuhxs on 2019/4/4.
//

#include "MCTS.h"

bool MCTS::win_expectation = 0;

MCTS::MCTS(Chessboard *init) {   // for the root node
    this->chessboard.set_bitmap(init->get_board_color(), init->get_board_occupied());
    this->chessboard.set_color(init->get_current_color());
    this->sti_times = 0;
    this->win_times = 0;
    this->height = 0;        // the height of the root node is 0
    this->parent = nullptr;
    this->first_children = nullptr;
    this->siblings = nullptr;
    this->if_end = 0;
}

MCTS::MCTS(MCTS *init, int x, int y) {
    this->chessboard.set_bitmap(init->chessboard.get_board_color(), init->chessboard.get_board_occupied());
    this->chessboard.set_color(init->chessboard.get_current_color());

#ifdef DEBUG
    assert(this->chessboard.make_move(x, y));
#else
    this->chessboard.make_move(x, y);
#endif

    this->sti_times = 0;
    this->win_times = 0;
    this->parent = init;
    this->first_children = nullptr;
    this->siblings = nullptr;
    this->if_end = 0;
    this->height = init->get_height() + 1;
}

int MCTS::get_height() {
    return height;
}

bool MCTS::make_children() {
    vector<char> solutions;
    this->chessboard.get_possible_solutions(solutions);
    int flag = 0;
    MCTS *previous = nullptr;
    while (!solutions.empty()) {
        flag = 1;
        int y = solutions.back();
        solutions.pop_back();
        int x = solutions.back();
        solutions.pop_back();
        MCTS *child = new MCTS(this, x, y);
        if (previous) {   // init siblings
            previous->set_siblings(child);
        }
        previous = child;
    }
    if (!flag) {
        if (this->chessboard.check_end()) {   // end of the game
            this->if_end = 1;
            int situation = this->chessboard.check_win();
            if (this->win_expectation) {  // we want black to win, if it is a tie, we consider we win
                if (situation == 1 || situation == 2) {
                    this->sti_times = 1;
                    this->win_times = 1;
                }
                else {
                    this->sti_times = 1;
                    this->win_times = 0;
                }
            }
            else {
                if (situation == 0 || situation == 2) {
                    this->sti_times = 1;
                    this->win_times = 1;
                }
                else {
                    this->sti_times = 1;
                    this->win_times = 0;
                }
            }
        }
        else {
            MCTS *child = new MCTS(this, -1, -1);   // does not have a possible move
        }
    }
    return 1;
}

void MCTS::set_siblings(MCTS *sibling) {
    this->siblings = sibling;
}