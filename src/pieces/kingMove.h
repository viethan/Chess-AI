// kingMove.h
#ifndef KINGMOVE_H
#define KINGMOVE_H

#include <iostream>
#include <vector>
#include "../forall.h"
#include "pieceMove.h"

class kingMove: public pieceMove {
	public:
		static std::vector<pieceMove> findMoves(int** board, int row, int column, bool colour);		
};

#endif
