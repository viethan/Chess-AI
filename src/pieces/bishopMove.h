// bishopMove.h
#ifndef BISHOPMOVE_H
#define BISHOPMOVE_H

#include <iostream>
#include <vector>
#include "../forall.h"
#include "pieceMove.h"

class bishopMove: public pieceMove {
	public:
		static std::vector<pieceMove> findMoves(int** board, int row, int column, bool colour);		
};

#endif
