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
    PyRun_SimpleString("import game");
    PyRun_SimpleString("game.overall()");
    Py_Finalize();
    return 0;
}
