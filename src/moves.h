// moves.h
#ifndef moves_H
#define moves_H

#include <iostream>
#include "forall.h"
using namespace std;

extern int** gBoardCoords;

// struct Move {
// 	int srcRow, srcCol, destRow, destCol;
// 	int score;
// 	bool Capture;
// };


// Initialise the board with default pieces
void init_board();
// Frees everything board/move related
void close_moves();



int** copy_board(int **board);
int** make_move(int srcRow, int srcCol, int destRow, int destCol, int** board);
void free_board(int** board); // maybe struct in the future?

#endif