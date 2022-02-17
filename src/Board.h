// Board.h
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "pieces/pieceMove.h"
#include "pieces/pawnMove.h"
#include "pieces/knightMove.h"
#include "pieces/rookMove.h"
#include "pieces/bishopMove.h"
#include "pieces/queenMove.h"
#include "pieces/kingMove.h"

class Board {
	public:
		int** pos;
		bool turn;
		std::vector<pieceMove> moves;

		Board();
		Board(int** paramPos);
		~Board();
		Board* make_move(pieceMove move, bool getMoves);
		bool check_move(pieceMove tryMove);
		bool checked(bool colour);
		int gameOver();
	private:
		void get_moves();
		bool checked_knights(int kingRow, int kingColumn, bool colour);
		bool checked_pawns(int kingRow, int kingColumn, bool colour);
		bool checked_enemyKing(int kingRow, int kingColumn, bool colour);
		bool checked_diagonals(int kingRow, int kingColumn, bool colour);
		bool checked_rankFile(int kingRow, int kingColumn, bool colour);
};

#endif

/*

The Board object should populate the moves vector
once it's instantiated
The only time it's not is in get_moves(), as we only need
the board->pos; this also avoid infinite recursion

turn here means if it's white or black's turn to move
This is different from usersTurn from GameState, which denotes
if it's the user's or AI's turn

*/