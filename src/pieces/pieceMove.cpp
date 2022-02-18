#include "pieceMove.h"

// placeholders
pieceMove::pieceMove() {
	this->srcRow = -1;
	this->srcCol = -1;
	this->destRow = -1;
	this->destCol = -1;
	this->castlingMove = false;
}

pieceMove::pieceMove(int srcRow, int srcCol, int destRow, int destCol) {
	this->srcRow = srcRow;
	this->srcCol = srcCol;
	this->destRow = destRow;
	this->destCol = destCol;
	this->castlingMove = false;
}

pieceMove::pieceMove(int srcRow, int srcCol, int destRow, int destCol, bool castlingMove) {
	this->srcRow = srcRow;
	this->srcCol = srcCol;
	this->destRow = destRow;
	this->destCol = destCol;
	this->castlingMove = true;
}

pieceMove::pieceMove(const pieceMove &obj) {
	this->srcRow = obj.srcRow;
	this->srcCol = obj.srcCol;
	this->destRow = obj.destRow;
	this->destCol = obj.destCol;
	this->castlingMove = obj.castlingMove;
}

bool pieceMove::string2move(std::string input, pieceMove* target, bool colour) {
	if (input.compare("kingside castle") == 0) {
		target->castlingMove = true;
		target->srcCol = 4;
		target->destCol = 6;
		
		if (colour == WHITE) {
			target->srcRow = 7;
			target->destRow = 7;
		} else {
			target->srcRow = 0;
			target->destRow = 0;
		}

		return true;
	}

	if (input.compare("queenside castle") == 0) {
		target->castlingMove = true;
		target->srcCol = 4;
		target->destCol = 2;
		
		if (colour == WHITE) {
			target->srcRow = 7;
			target->destRow = 7;
		} else {
			target->srcRow = 0;
			target->destRow = 0;
		}

		return true;
	}

	if (input.size() == 4 && 
		('a' <= input[0] && input[0] <= 'h') &&
		('1' <= input[1] && input[1] <= '8') && 
		('a' <= input[2] && input[2] <= 'h') &&
		('1' <= input[3] && input[3] <= '8')) {
			
			target->castlingMove = false;
			target->srcCol = input[0] - 'a';
			target->srcRow = 7 - (input[1] - '1'); 
			target->destCol = input[2] - 'a';
			target->destRow = 7 - (input[3] - '1');
			return true;
	}

	return false;
}
