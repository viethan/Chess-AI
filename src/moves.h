// moves.h
#ifndef moves_H
#define moves_H

#include <iostream>
#include "forall.h"
using namespace std;

extern int** gBoardCoords;

// Initialise the board with default pieces
void init_board();
// Frees media and shuts down SDL
void close_moves();

#endif