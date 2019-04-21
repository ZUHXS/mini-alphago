//
// Created by zuhxs on 2019/4/4.
//

#include "MCTS.h"

MCTS *MCTS::root_node = nullptr;
int MCTS::node_counting = 0;

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
        auto y = solutions.back();
        solutions.pop_back();
        auto x = solutions.back();
        solutions.pop_back();
        auto child = new MCTS(this, x, y);
        //cout << "create children under " << this->current_node_counting << " with x " << (int)x << " y " << (int)y << " with index " << child->current_node_counting << endl;
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
        //cout << "debug 2" << endl;
        if (!child->chessboard.get_possible_solutions()) {   // the opponent still can't make a move
            this->first_children = nullptr;
            delete child;
            this->if_end = 1;
            //cout << "debug 3" << endl;
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
        //cout << "index " <<  this->current_node_counting << " has ucb " << (this->height % 2 ? 1000 : -1) << endl;
        return 1000;
    }
    else {
        if (this->height % 2) {  // black move
            return (float) ((double)this->win_times / (double)this->sim_times + sqrt(log(total_N) * C / (double)this->sim_times));
        }
        else {
            return (float) (1 - ((double) this->win_times / (double) this->sim_times) +
                            sqrt(log(total_N) * C / (double) this->sim_times));
        }
    }
}

MCTS* MCTS::select_ucb() {
    auto best = this->first_children;
    auto p = this->first_children;
    int total_N = this->sim_times;
    float best_ucb = -1;
    while (p != NULL) {
        float ucb = p->get_ucb(total_N);
        if (ucb > best_ucb) {
            best_ucb = ucb;
            best = p;
        }
        p = p->siblings;
    }
    //cout << "selected node No. " <<  best->current_node_counting << endl;
    return best;
}

void MCTS::do_MCTS(int &best_x, int &best_y) {
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
            //cout << "UCB selected index " << temp->current_node_counting << endl;
        }
        temp->make_children();
        if (countings == 4239)
            cout << "debug 4" << endl;

        if (temp->if_end) {   // check end when making children

            bool situation = temp->chessboard.check_win();
            //cout << "debug 1" << endl;
            if (win_condition) {  // we want black to win, if it is a tie, we consider we win
                temp->back_propagate(situation);
            } else {
                temp->back_propagate(!situation);
            }
            temp = root_node;
        }
        else {
            temp = temp->first_children;
            //cout << "selected index " << temp->current_node_counting << " to do simulation" << endl;
            bool victory = temp->make_simulate();
            if (win_condition) {
                temp->back_propagate(victory);
            }
            else {
                temp->back_propagate(!victory);
            }
            //cout << "simulation result " << victory << endl;
            temp = root_node;
        }
    }


    cout << "the conditions are " << temp->sim_times << " " << temp->win_times << endl;
    // output the result
    temp = root_node;
    temp = temp->first_children;
    int temp_x = -1;
    int temp_y = -1;
    double best_prob = -1;
    while(temp) {
        double temp_prob = (double)temp->win_times / (double)temp->sim_times;
        cout << "with x = " << temp->prev_x << " y = " << temp->prev_y << " the conditions are " << temp_prob << endl;
        if (temp_prob > best_prob) {
            temp_x = temp->prev_x;
            temp_y = temp->prev_y;
            best_prob = temp_prob;
        }
        temp = temp->siblings;
    }
    if (temp_x == -1 || temp_y == -1) {
        cout << "an error occured in MCTS" << endl;
    }
    best_x = temp_x;
    best_y = temp_y;
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

void MCTS::change_root(int x1, int y1, int x2, int y2) {
    auto temp = root_node;
    temp = temp->first_children;
    int find_flag = 0;
    while(temp != nullptr) {
        if (temp->prev_x == x1 && temp->prev_y == y1) {
            find_flag = 1;
            break;
        }
        temp = temp->siblings;
    }
    if (!find_flag) {
        cout << "an error occured when changing the root1" << endl;
        exit(1);
    }
    temp = temp->first_children;
    find_flag = 0;
    while (temp != nullptr) {
        if (temp->prev_x == x2 && temp->prev_y == y2) {
            find_flag = 1;
            break;
        }
        temp = temp->siblings;
    }
    if (!find_flag) {
        cout << "an error occured when changing the root2" << endl;
        exit(1);
    }


    else {
        root_node = temp;
    }
}