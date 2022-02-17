// pieceMove.h
#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include <iostream>
#include <vector>
#include "../forall.h"

class pieceMove {
	public:
		int srcRow, srcCol;
		int destRow, destCol;

		pieceMove();
		pieceMove(int srcRow, int srcCol, int destRow, int destCol);
		static bool string2move(std::string input, pieceMove* target);		
};

#endif
