// minimax.h
#ifndef MINIMAX_H
#define MINIMAX_H

#include <iostream>
#include <vector>
#include <limits>
#include "forall.h"
#include "moves.h"
using namespace std;

const int MAX_DEPTH = 3; // must be >= 1

struct MoveEval {
	Move move;
	int score;
};

int eval(int **board);
Move getOptimalMove(int **board, bool colour);
MoveEval minimax(int **board, int depth, int alpha, int beta, bool colour);

#endif