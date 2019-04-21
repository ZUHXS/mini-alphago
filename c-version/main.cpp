#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"
#include "Python.h"
#include <unistd.h>
#include "MCTS.h"

using namespace std;

int main(int argc, char *argv[]) {

    //srand(time(0));

    Chessboard chessboard;
    MCTS chess(&chessboard);
    //chess.do_MCTS();




    Py_Initialize();
    if (!Py_IsInitialized()) {
        return -1;
    }

    PySys_SetArgv(argc, argv);
    PyRun_SimpleString("import game, time");
    PyRun_SimpleString("game.init()");


    PyObject *GameModule = PyImport_ImportModule("game");
    PyObject *OverallFunc = PyObject_GetAttrString(GameModule, "overall");
    int r1 = 0;
    int r2 = 0;
    int flag = 0;

    for (int k = 0; k < 50; k++) {
        Chessboard chessboard;
        while (1) {
            int ai_move_x;
            int ai_move_y;

            vector<char> solutions;
            solutions.clear();
            chessboard.get_possible_solutions(solutions);
            int solutions_number = solutions.size();
            PyObject *solution_params = PyTuple_New(solutions_number);
            for (int i = 0; i < solutions_number; i++) {
                PyTuple_SetItem(solution_params, i, Py_BuildValue("i", solutions.back()));
                solutions.pop_back();
            }

            PyObject *RetValue = PyObject_CallObject(OverallFunc, solution_params);

            if (flag == 0) {
                flag = 1;
                chess.do_MCTS(ai_move_x, ai_move_y);
            }
            else {
                chess.change_root(ai_move_x, ai_move_y, r1, r2);
                chess.do_MCTS(ai_move_x, ai_move_y);
            }
            cout << "select to move x = " << ai_move_x << " and y = " << ai_move_y << endl;
            chessboard.make_move(ai_move_x, ai_move_y);


            if (chessboard.check_end()) {
                cout << chessboard.check_win() << endl;
                break;
            }

            string color_string = "game.board_color = " + to_string(chessboard.get_board_color());
            string occupied_string = "game.board_occupied = " + to_string(chessboard.get_board_occupied());
            PyRun_SimpleString(color_string.c_str());
            PyRun_SimpleString(occupied_string.c_str());

            // list the possible solutions
            solutions;
            solutions.clear();
            chessboard.get_possible_solutions(solutions);
            solutions_number = solutions.size();
            solution_params = PyTuple_New(solutions_number);
            for (int i = 0; i < solutions_number; i++) {
                PyTuple_SetItem(solution_params, i, Py_BuildValue("i", solutions.back()));
                solutions.pop_back();
            }

            r1 = -1;
            r2 = -1;
            int possible_moves = chessboard.get_possible_solutions();
            if (possible_moves) {

                while (!chessboard.if_movable(r1, r2)) {
                    PyObject *RetValue = PyObject_CallObject(OverallFunc, solution_params);
                    PyArg_ParseTuple(RetValue, "i|i", &r1, &r2);
                    usleep(1000);
                }
                cout << r1 << "  " << r2 << endl;
                chessboard.make_move(r1, r2);
            }
            else {
                chessboard.make_move(-1, -1);
            }

            //sleep(1);
            color_string = "game.board_color = " + to_string(chessboard.get_board_color());
            occupied_string = "game.board_occupied = " + to_string(chessboard.get_board_occupied());
            PyRun_SimpleString(color_string.c_str());
            PyRun_SimpleString(occupied_string.c_str());
        }
    }
    sleep(100);

    return 0;

}
