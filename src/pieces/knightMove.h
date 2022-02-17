// knightMove.h
#ifndef KNIGHTMOVE_H
#define KNIGHTMOVE_H

#include <iostream>
#include <vector>
#include "../forall.h"
#include "pieceMove.h"

class knightMove: public pieceMove {
	public:
		static std::vector<pieceMove> findMoves(int** board, int row, int column, bool colour);		
};

#endif
