//
// Created by zuhxs on 2019/4/4.
//

#ifndef C_VERSION_MCTS_H
#define C_VERSION_MCTS_H

#include "chessboard.h"


class MCTS {
private:
    Chessboard chessboard;
    MCTS *parent;   // father
    MCTS *first_children;
    MCTS *siblings;   // a chain connection all siblings
    int sti_times;
    int win_times;
public:
    MCTS(Chessboard *init);   // init for father points
    MCTS(MCTS *init);
};


#endif //C_VERSION_MCTS_H
