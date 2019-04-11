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
    MCTS::root_node = this;
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
        MCTS *child = new MCTS(this, -1, -1);   // does not have a possible move
        if (!child->chessboard.get_possible_solutions()) {   // the opponent still can't make a move
            this->if_end = 1;
            int situation = this->chessboard.check_win();
            if (this->win_expectation) {  // we want black to win, if it is a tie, we consider we win
                if (situation == 1 || situation == 2) {
                    this->sti_times = 1;
                    this->win_times = 1;
                } else {
                    this->sti_times = 1;
                    this->win_times = 0;
                }
            } else {
                if (situation == 0 || situation == 2) {
                    this->sti_times = 1;
                    this->win_times = 1;
                } else {
                    this->sti_times = 1;
                    this->win_times = 0;
                }
            }
        }
    }
    return 1;
}

void MCTS::set_siblings(MCTS *sibling) {
    this->siblings = sibling;
}

float MCTS::get_ucb(int total_N) {
    if (total_N == 0) {
        return 1000;
    }
    else {
        return (float) ((double)this->win_times / (double)this->sti_times + sqrt(log(total_N) * C / (float)this->sti_times));
    }
}

MCTS* MCTS::select_ucb() {
    MCTS *best = this->first_children;
    MCTS *p = this->first_children;
    int total_N = this->sti_times;
    float best_ucb_1 = -1;
    float best_ucb_2 = INFINITY;
    while (p != NULL) {
        float ucb = p->get_ucb(total_N);
        if (this->height % 2) {
            if (ucb > best_ucb_1) {
                best_ucb_1 = ucb;
                best = p;
            }
        } else {
            if (ucb < best_ucb_2) {
                best_ucb_2 = ucb;
                best = p;
            }
        }
        p = p->siblings;
    }
    return best;
}

void MCTS::do_MCTS() {
#ifdef DEBUG
    if (MCTS::root_node != this) {
        printf("root node not match!\n");
    }
#endif
    bool win_condition = root_node->chessboard.get_current_color();

    MCTS *temp = MCTS::root_node;

    int countings = 0;
    while (countings <= MAXCOUNTING) {
        countings++;
        while (temp->first_children != NULL) {
            temp = temp->select_ucb();
        }
        temp->make_children();
        temp = temp->first_children;
        bool victory = temp->make_stimulate();

    }

}


bool MCTS::make_stimulate() {
    return this->chessboard.stimulate();
}