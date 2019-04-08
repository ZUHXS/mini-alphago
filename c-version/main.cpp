#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"
#include "Python.h"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {

    Py_Initialize();
    if (!Py_IsInitialized()) {
        return -1;
    }

    PySys_SetArgv(argc, argv);
    PyRun_SimpleString("import game, time");
    PyRun_SimpleString("game.init()");

    Chessboard chessboard;
    PyObject *GameModule = PyImport_ImportModule("game");
    PyObject *OverallFunc = PyObject_GetAttrString(GameModule, "overall");
    int r1 = 0;
    int r2 = 0;

    while (1) {

        vector<char> solutions;
        solutions.clear();
        chessboard.get_possible_solutions(solutions);
        int solutions_number = solutions.size();
        printf("solutions number is: %d\n", solutions_number);
        PyObject *solution_params = PyTuple_New(solutions_number);
        for (int i = 0; i < solutions_number; i++) {
            PyTuple_SetItem(solution_params, i, Py_BuildValue("i", solutions.back()));
            solutions.pop_back();
        }

/*
        vector<char> solutions;
        chessboard.get_possible_solutions(solutions);
        PyObject *solution_params = PyTuple_New(solutions.size());
        PyTuple_SetItem(solution_params, 0, Py_BuildValue("i", 2));
        PyTuple_SetItem(solution_params, 1, Py_BuildValue("i", 3));
        PyTuple_SetItem(solution_params, 2, Py_BuildValue("i", 4));
        PyTuple_SetItem(solution_params, 3, Py_BuildValue("i", 5));
        PyTuple_SetItem(solution_params, 4, Py_BuildValue("i", 2));
        PyTuple_SetItem(solution_params, 5, Py_BuildValue("i", 3));
        PyTuple_SetItem(solution_params, 6, Py_BuildValue("i", 4));
        PyTuple_SetItem(solution_params, 7, Py_BuildValue("i", 5));
*/

        printf("111\n");
        PyObject *RetValue = PyObject_CallObject(OverallFunc, solution_params);
        PyArg_ParseTuple(RetValue, "i|i", &r1, &r2);
        printf("%d %d\n", r1, r2);

        if (r1 >= 0 && r2 >= 0) {
            chessboard.make_move(r1, r2);
        }
        string color_string = "game.board_color = " + to_string(chessboard.get_board_color());
        string occupied_string = "game.board_occupied = " + to_string(chessboard.get_board_occupied());
        PyRun_SimpleString(color_string.c_str());
        PyRun_SimpleString(occupied_string.c_str());
    }
    Py_Finalize();
    return 0;
}
