#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"
#include "Python.h"

using namespace std;

int main(int argc, char *argv[]) {

    Py_Initialize();
    if (!Py_IsInitialized()) {
        return -1;
    }

    PySys_SetArgv(argc, argv);
    PyRun_SimpleString("import game, time");
    PyRun_SimpleString("game.init()");

    while (1) {
        PyRun_SimpleString("game.overall()");
        PyRun_SimpleString("game.board_color = 0x800000000");
    }
    Py_Finalize();
    return 0;
}
