// moves.h
#ifndef moves_H
#define moves_H

#include <iostream>
#include <vector>
#include "forall.h"
using namespace std;

extern int** gBoardCoords;
static bool wChecked, bChecked;

// THE MOVES ARE FROM SDL POINT OF VIEW
struct Move {
	int srcRow, srcCol;
	int destRow, destCol;
};

// Initialise the board with default pieces
void init_board();

// Frees everything board/move related
void close_moves();

// Returns a pointer to a hard copy of the board
int** copy_board(int **board);

// Returns a pointer to a new board, after the move has been played
int** make_move(Move move, int** board);

// Frees the board
void free_board(int** board); 


std::vector<Move> get_moves(int **board, bool colour);
std::vector<Move> escape_check(int **board, bool colour); // direct attack and potential attack (maybe mark the squares?)

std::vector<Move> pawnMove(int** board, int row, int column, bool colour);
std::vector<Move> knightMove(int** board, int row, int column, bool colour);
std::vector<Move> bishopMove(int** board, int row, int column, bool colour);
std::vector<Move> rookMove(int** board, int row, int column, bool colour);
std::vector<Move> queenMove(int** board, int row, int column, bool colour);
std::vector<Move> kingMove(int** board, int row, int column, bool colour);

bool checked(int **board, bool colour); // we can use this to see if we're checking our opponent, and if we accidentally got checked
bool checked_knights(int** board, int kingRow, int kingColumn, bool colour);
bool checked_pawns(int** board, int kingRow, int kingColumn, bool colour);
bool checked_diagonals(int** board, int kingRow, int kingColumn, bool colour);
bool checked_rankFile(int** board, int kingRow, int kingColumn, bool colour);






int stalemate_win(int **board, bool colour); // 0 = nothing, 1 = win, 2 = lose, 3 = stalemate; probably enum
int eval(int **board);

#endif