// pieceMove.h
#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include <vector>
#include "../forall.h"

class pieceMove {
	public:
		int srcRow, srcCol;
		int destRow, destCol;
		bool castlingMove, enPassant;

		pieceMove();
		pieceMove(const pieceMove &obj);
		pieceMove(int srcRow, int srcCol, int destRow, int destCol);
		pieceMove(int srcRow, int srcCol, int destRow, int destCol, bool castlingMove);
		pieceMove(int srcRow, int srcCol, int destRow, int destCol, bool castlingMove, bool enPassant);
		static bool string2move(std::string input, pieceMove* target, bool colour, int** board);		
};

#endif
