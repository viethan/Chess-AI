// queenMove.h
#ifndef QUEENMOVE_H
#define QUEENMOVE_H

#include <iostream>
#include <vector>
#include "../forall.h"
#include "pieceMove.h"
#include "bishopMove.h"
#include "rookMove.h"

class queenMove: public pieceMove {
	public:
		static std::vector<pieceMove> findMoves(int** board, int row, int column, bool colour);		
};

#endif
