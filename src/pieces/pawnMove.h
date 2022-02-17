// pawnMove.h
#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include <iostream>
#include <vector>
#include "../forall.h"
#include "pieceMove.h"

class pawnMove: public pieceMove {
	public:
		static std::vector<pieceMove> findMoves(int** board, int row, int column, bool colour);		
};

#endif
