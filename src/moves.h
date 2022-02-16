// moves.h
#ifndef MOVES_H
#define MOVES_H

#include <iostream>
#include <vector>
#include "forall.h"
using namespace std;

// THE MOVES ARE FROM SDL POINT OF VIEW
struct Move {
	int srcRow, srcCol;
	int destRow, destCol;
};


std::vector<Move> pawnMove(int** board, int row, int column, bool colour);
std::vector<Move> knightMove(int** board, int row, int column, bool colour);
std::vector<Move> bishopMove(int** board, int row, int column, bool colour);
std::vector<Move> rookMove(int** board, int row, int column, bool colour);
std::vector<Move> queenMove(int** board, int row, int column, bool colour);
std::vector<Move> kingMove(int** board, int row, int column, bool colour);
bool string2move(string input, Move* target);

#endif