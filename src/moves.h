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

// Initialise the board with default pieces
int** init_board();

// Returns a pointer to a hard copy of the board
int** copy_board(int **board);

// Returns a pointer to a new board, after the move has been played
int** make_move(Move move, int** board);

// Frees the board
void free_board(int** board); 


std::vector<Move> get_moves(int **board, bool colour);

std::vector<Move> pawnMove(int** board, int row, int column, bool colour);
std::vector<Move> knightMove(int** board, int row, int column, bool colour);
std::vector<Move> bishopMove(int** board, int row, int column, bool colour);
std::vector<Move> rookMove(int** board, int row, int column, bool colour);
std::vector<Move> queenMove(int** board, int row, int column, bool colour);
std::vector<Move> kingMove(int** board, int row, int column, bool colour);

bool checked(int **board, bool colour); // we can use this to see if we're checking our opponent, and if we accidentally got checked
bool checked_knights(int** board, int kingRow, int kingColumn, bool colour);
bool checked_pawns(int** board, int kingRow, int kingColumn, bool colour);
bool checked_enemyKing(int** board, int kingRow, int kingColumn, bool colour);
bool checked_diagonals(int** board, int kingRow, int kingColumn, bool colour);
bool checked_rankFile(int** board, int kingRow, int kingColumn, bool colour);

bool string2move(string input, Move* target);
bool check_move(Move tryMove, int** board, bool colour);

int gameOver(int** board, bool colour);

#endif