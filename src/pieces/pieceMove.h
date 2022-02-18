// pieceMove.h
#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include <vector>
#include "../forall.h"

class pieceMove {
	public:
		int srcRow, srcCol;
		int destRow, destCol;
		bool castlingMove;

		pieceMove();
		pieceMove(int srcRow, int srcCol, int destRow, int destCol);
		pieceMove(int srcRow, int srcCol, int destRow, int destCol, bool castlingMove);
		static bool string2move(std::string input, pieceMove* target);		
};

#endif
