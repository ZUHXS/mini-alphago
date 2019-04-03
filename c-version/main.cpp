#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"

using namespace std;

int main() {

    Chessboard a;
    vector<char> b;
    a.get_possible_solutions(b);

    cout << endl;
    cout << a.make_move(2, 3) << endl;
    cout << a.make_move(4, 2) << endl;
    cout << a.make_move(5, 1) << endl;
    cout << a.make_move(2, 2) << endl;
    cout << a.make_move(2, 1) << endl;
    cout << a.make_move(3, 5) << endl;
    cout << a.make_move(4, 5) << endl;
    cout << a.make_move(6, 0) << endl;
    cout << a.make_move(3, 6) << endl;

    cout << "white number " << a.white_num() << endl;
    cout << "black number " << a.black_num() << endl;

    b.clear();
    std::cout << "number is " << b.size() << endl;
    a.get_possible_solutions(b);
    std::cout << "number is " << b.size() << endl;
    std::cout << "possible moves are: ";
    for (std::vector<char>::const_iterator i = b.begin(); i != b.end(); i++) {
        std::cout << (int)*i << ' ';
    }



    //std::cout << (1 ^ 1) << std::endl;
    return 0;
}