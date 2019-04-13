#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"
#include "Python.h"
#include <unistd.h>
#include "MCTS.h"

using namespace std;

int main(int argc, char *argv[]) {

    srand(time(0));

    Chessboard chessboard;
    MCTS chess(&chessboard);
    chess.do_MCTS();

    /*

    Py_Initialize();
    if (!Py_IsInitialized()) {
        return -1;
    }

    PySys_SetArgv(argc, argv);
    PyRun_SimpleString("import game, time");
    PyRun_SimpleString("game.init()");

    Chessboard chessboard;
    for (int i = 0; i < 26; i++) {
        Chessboard *chessboard2 = new Chessboard;
        bool state = chessboard2->stimulate();
        printf("%d: %d\n", i, state);
    }
    PyObject *GameModule = PyImport_ImportModule("game");
    PyObject *OverallFunc = PyObject_GetAttrString(GameModule, "overall");
    int r1 = 0;
    int r2 = 0;


    while (1) {
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
        PyArg_ParseTuple(RetValue, "i|i", &r1, &r2);

        if (r1 >= 0 && r2 >= 0) {
            chessboard.make_move(r1, r2);
        }
        chessboard.stimulate_move();
        if (chessboard.check_end()) {
            break;
        }
        sleep(1);
        string color_string = "game.board_color = " + to_string(chessboard.get_board_color());
        string occupied_string = "game.board_occupied = " + to_string(chessboard.get_board_occupied());
        PyRun_SimpleString(color_string.c_str());
        PyRun_SimpleString(occupied_string.c_str());
    }
    Py_Finalize();
     */
    return 0;
}
