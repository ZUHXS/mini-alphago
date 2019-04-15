//
// Created by zuhxs on 2019/4/4.
//

#include "MCTS.h"

MCTS *MCTS::root_node = nullptr;
int MCTS::node_counting = 0;
//bool MCTS::win_expectation = 0;

MCTS::MCTS(Chessboard *init) {   // for the root node
    this->chessboard.set_bitmap(init->get_board_color(), init->get_board_occupied());
    this->chessboard.set_color(init->get_current_color());
    this->sim_times = 0;
    this->win_times = 0;
    this->height = 0;        // the height of the root node is 0
    this->parent = nullptr;
    this->first_children = nullptr;
    this->siblings = nullptr;
    this->if_end = 0;
    root_node = this;

    this->current_node_counting = MCTS::node_counting;
    MCTS::node_counting++;
}

MCTS::MCTS(MCTS *init, int x, int y) {
    this->chessboard.set_bitmap(init->chessboard.get_board_color(), init->chessboard.get_board_occupied());
    this->chessboard.set_color(init->chessboard.get_current_color());

#ifdef DEBUG
    assert(this->chessboard.make_move(x, y));
#else
    this->chessboard.make_move(x, y);
#endif

    this->sim_times = 0;
    this->win_times = 0;
    this->parent = init;
    this->first_children = nullptr;
    this->siblings = nullptr;
    this->if_end = 0;
    this->height = init->get_height() + 1;
    this->prev_x = x;
    this->prev_y = y;

    this->current_node_counting = MCTS::node_counting;
    MCTS::node_counting++;
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
        auto child = new MCTS(this, x, y);
        cout << "create children under " << this->current_node_counting << " with x " << x << " y " << y << " with index " << child->current_node_counting << endl;
        if (previous) {   // init siblings
            previous->set_siblings(child);
        }
        else {
            this->first_children = child;
        }
        previous = child;
    }
    if (!flag) {
        auto child = new MCTS(this, -1, -1);   // does not have a possible move
        if (!child->chessboard.get_possible_solutions()) {   // the opponent still can't make a move
            this->if_end = 1;
        }
        else {
            this->first_children = child;
        }
    }
    return 1;
}

void MCTS::set_siblings(MCTS *sibling) {
    this->siblings = sibling;
}

float MCTS::get_ucb(int total_N) {
    if (this->sim_times == 0) {
        cout << "index " <<  this->current_node_counting << " has ucb " << (this->height % 2 ? 1000 : -1) << endl;
        return this->height % 2 ? 1000 : -1;
    }
    else {
        cout << "index " <<  this->current_node_counting << " has ucb " << (float) ((double)this->win_times / (double)this->sim_times + sqrt(log(total_N) * C / (float)this->sim_times)) << endl;
        return (float) ((double)this->win_times / (double)this->sim_times + sqrt(log(total_N) * C / (float)this->sim_times));
    }
}

MCTS* MCTS::select_ucb() {
    auto best = this->first_children;
    auto p = this->first_children;
    int total_N = this->sim_times;
    float best_ucb_1 = -1;
    float best_ucb_2 = INFINITY;
    while (p != NULL) {
        float ucb = p->get_ucb(total_N);
        if (p->height % 2) {
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
    cout << "selected node No. " <<  best->current_node_counting << endl;
    return best;
}

void MCTS::do_MCTS() {
#ifdef DEBUG
    if (MCTS::root_node != this) {
        printf("root node not match!\n");
    }
#endif
    bool win_condition = get_win_condition();

    auto temp = root_node;

    int countings = 0;
    while (countings <= MAXCOUNTING) {
        countings++;
        cout << countings << endl;
        while (temp->first_children != NULL) {
            temp = temp->select_ucb();
            cout << "UCB selected index " << temp->current_node_counting << endl;
        }
        temp->make_children();
        if (temp->if_end) {   // check end when making children
            int situation = this->chessboard.check_win();
            if (get_win_condition()) {  // we want black to win, if it is a tie, we consider we win
                if (situation == 1 || situation == 2) {
                    back_propagate(1);
                } else {
                    back_propagate(0);
                }
            } else {
                if (situation == 0 || situation == 2) {
                    back_propagate(1);
                } else {
                    back_propagate(0);
                }
            }
        }
        temp = temp->first_children;
        cout << "selected index " << temp->current_node_counting << " to do simulation" << endl;
        bool victory = temp->make_simulate();
        victory = !static_cast<bool>((victory) ^ (win_condition));
        //bool victory = ~(temp->make_simulate() ^ win_condition);
        temp->back_propagate(victory);
        cout << "simulation result " << victory << endl;
        temp = root_node;
    }

    cout << "the conditions are " << temp->sim_times << " " << temp->win_times << endl;

}


bool MCTS::make_simulate() {
    return this->chessboard.simulate();
}

void MCTS::back_propagate(bool victory) {
    auto p = this;
    while (p != root_node) {
        p->win_times += victory;
        p->sim_times += 1;
        p = p->parent;
    }
    p->win_times += victory;
    p->sim_times += 1;   // add the root node
}

bool MCTS::get_prev_xy(int &x, int &y) {
    x = this->prev_x;
    y = this->prev_y;
}

bool MCTS::get_win_condition() {
    return root_node->chessboard.get_current_color();
}