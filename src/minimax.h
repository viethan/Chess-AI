// minimax.h
#ifndef MINIMAX_H
#define MINIMAX_H

#include <iostream>
#include <vector>
#include "forall.h"
#include "moves.h"
using namespace std;

int eval(int **board);
Move getOptimalMove(int **board, bool colour);

#endif