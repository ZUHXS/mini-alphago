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
#define MAXCOUNTING 1000


class MCTS {
private:
    Chessboard chessboard;
    MCTS *parent;   // father
    MCTS *first_children;
    MCTS *siblings;   // a chain connection all siblings
    int sti_times;
    int win_times;
    int height;    // the height of the node, probability calculation use
    int if_end;    // if it is the end of the game
    int best_x;
    int best_y;
    static MCTS *root_node;
    static bool win_expectation;  // if we want black to win, 1, else 0
public:
    MCTS(Chessboard *init);   // init for father points
    MCTS(MCTS *init, int x, int y);    // x and y is the move to make
    int get_height();
    void set_siblings(MCTS *sibling);
    float get_ucb(int total_N);
    MCTS *select_ucb();
    bool make_stimulate();

    bool make_children();    // if it is the leaf node, then create children
    void do_MCTS();

};


#endif //C_VERSION_MCTS_H
