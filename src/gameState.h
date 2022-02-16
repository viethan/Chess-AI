// gameState.h
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "moves.h"
#include "minimax.h"
#include "visualise.h"
#include "forall.h"
using namespace std;

extern bool QUIT;
extern vector<string> history;

// input: 0 for white, 1 for black
// 2 for random, "quit" for quitting
// returns 0 for white, 1 for black, -1 for quitting
int selectPlayer();

// initialises SDL
// loads the media into memory
// returns a new board with default setup
int** init_main(bool colour);

// asks user to make their next move
// returns the updated board
// returns the same board if user quits
int** userMoves(int** board, bool colour);

// the AI will use minimax to find an optimal move
// returns the updated board
int** AIMoves(int** board, bool colour);

// decides if the game is over or continues
// the game is over when <colour> has no more moves
// this means it's LOST or STALEMATE
// returns status value
int status_check(int** board, bool colour);



#endif