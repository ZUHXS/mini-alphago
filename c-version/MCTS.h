//
// Created by zuhxs on 2019/4/4.
//

#ifndef C_VERSION_MCTS_H
#define C_VERSION_MCTS_H

#include "chessboard.h"
#include <assert.h>
#include <math.h>

#define C 2
#define INFINITY 100000
#define MAXCOUNTING 2000


class MCTS {
private:
    Chessboard chessboard;
    MCTS *parent;   // father
    MCTS *first_children;
    MCTS *siblings;   // a chain connection all siblings
    int sim_times;
    int win_times;
    int height;    // the height of the node, probability calculation use
    int if_end;    // if it is the end of the game
    int best_x;
    int best_y;
    int prev_x;
    int prev_y;
    int current_node_counting;
    static MCTS *root_node;
    static int node_counting;
    //static bool win_expectation;  // if we want black to win, 1, else 0
public:
    MCTS(Chessboard *init);   // init for father points
    MCTS(MCTS *init, int x, int y);    // x and y is the move to make
    int get_height();
    void set_siblings(MCTS *sibling);
    float get_ucb(int total_N);
    MCTS *select_ucb();
    bool make_simulate();
    bool get_prev_xy(int &x, int &y);
    bool get_win_condition();   // if we want black to win, return 1, else return 0

    bool make_children();    // if it is the leaf node, then create children
    void do_MCTS(int &best_x, int &best_y);
    void back_propagate(bool victory);
    void change_root(int x1, int y1, int x2, int y2);

};


#endif //C_VERSION_MCTS_H
