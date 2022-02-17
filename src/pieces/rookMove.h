// rookMove.h
#ifndef ROOKMOVE_H
#define ROOKMOVE_H

#include <iostream>
#include <vector>
#include "../forall.h"
#include "pieceMove.h"

class rookMove: public pieceMove {
	public:
		static std::vector<pieceMove> findMoves(int** board, int row, int column, bool colour);		
};

#endif
