// minimax.h
#ifndef MINIMAX_H
#define MINIMAX_H

#include <iostream>
#include <vector>
#include <limits>
#include "forall.h"
#include "Board.h"
#include "pieces/pieceMove.h"

/*

Potential Improvements:
- sort moves based on score for better pruning
- openings
- king endgame table
- try to differentiate between moves of the same value (especially those with +/- inf)
- there are cases when the king is literally captured. In that case, checked() will return True
- option to resign to the AI
- piece update thing

*/ 

const int MAX_DEPTH = 4; // must be >= 1
struct MoveEval {
	pieceMove move;
	int score;
};

const int pawnVal = 100;
const int knightVal = 320;
const int bishopVal = 330;
const int rookVal = 500;
const int queenVal = 900;
const int kingVal = 20000;

const int kingTable[8][8] = {
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-20, -30, -30, -40, -40, -30, -30, -20},
	{-10, -20, -20, -20, -20, -20, -20, -10},
	{ 20,  20,   0,   0,   0,   0,  20,  20},
	{ 20,  30,  10,   0,   0,  10,  30,  20}
};

const int queenTable[8][8] = {
	{-20, -10, -10,  -5,  -5, -10, -10, -20},
	{-10,   0,   0,   0,   0,   0,   0, -10},
	{-10,   0,   5,   5,   5,   5,   0, -10},
	{ -5,   0,   5,   5,   5,   5,   0,  -5},
	{  0,   0,   5,   5,   5,   5,   0,  -5},
	{-10,   5,   5,   5,   5,   5,   0, -10},
	{-10,   0,   5,   0,   0,   0,   0, -10},
	{-20, -10, -10,  -5,  -5, -10, -10, -20}
};

const int rookTable[8][8] = {
	{  0,   0,   0,   0,   0,   0,   0,   0},
  	{  5,  10,  10,  10,  10,  10,  10,   5},
 	{ -5,   0,   0,   0,   0,   0,   0,  -5},
 	{ -5,   0,   0,   0,   0,   0,   0,  -5},
 	{ -5,   0,   0,   0,   0,   0,   0,  -5},
 	{ -5,   0,   0,   0,   0,   0,   0,  -5},
 	{ -5,   0,   0,   0,   0,   0,   0,  -5},
  	{  0,   0,   0,   5,   5,   0,   0,   0}
};

const int bishopTable[8][8] = {
	{-20, -10, -10, -10, -10, -10, -10, -20},
	{-10,   0,   0,   0,   0,   0,   0, -10},
	{-10,   0,   5,  10,  10,   5,   0, -10},
	{-10,   5,   5,  10,  10,   5,   5, -10},
	{-10,   0,  10,  10,  10,  10,   0, -10},
	{-10,  10,  10,  10,  10,  10,  10, -10},
	{-10,   5,   0,   0,   0,   0,   5, -10},
	{-20, -10, -10, -10, -10, -10, -10, -20}
};

const int knightTable[8][8] = {
	{-50, -40, -30, -30, -30, -30, -40, -50},
	{-40, -20,   0,   0,   0,   0, -20, -40},
	{-30,   0,  10,  15,  15,  10,   0, -30},
	{-30,   5,  15,  20,  20,  15,   5, -30},
	{-30,   0,  15,  20,  20,  15,   0, -30},
	{-30,   5,  10,  15,  15,  10,   5, -30},
	{-40, -20,   0,   5,   5,   0, -20, -40},
	{-50, -40, -30, -30, -30, -30, -40, -50}
};

const int pawnTable[8][8] = {
	{  0,   0,   0,   0,   0,   0,   0,   0},
	{ 50,  50,  50,  50,  50,  50,  50,  50},
	{ 10,  10,  20,  30,  30,  20,  10,  10},
 	{  5,   5,  10,  25,  25,  10,   5,   5},
 	{  0,   0,   0,  20,  20,   0,   0,   0},
 	{  5,  -5, -10,   0,   0, -10,  -5,   5},
 	{  5,  10,  10, -20, -20,  10,  10,   5},
 	{  0,   0,   0,   0,   0,   0,   0,   0}
};

int eval(int **board);
pieceMove getOptimalMove(Board* board, bool colour);
MoveEval minimax(Board* board, int depth, int alpha, int beta, bool colour);

#endif