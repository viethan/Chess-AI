#include "pieceMove.h"

// placeholders
pieceMove::pieceMove() {
	this->srcRow = -1;
	this->srcCol = -1;
	this->destRow = -1;
	this->destCol = -1;
}

pieceMove::pieceMove(int srcRow, int srcCol, int destRow, int destCol) {
	this->srcRow = srcRow;
	this->srcCol = srcCol;
	this->destRow = destRow;
	this->destCol = destCol;
}

bool pieceMove::string2move(std::string input, pieceMove* target) {
	if (input.size() == 4 && 
		('a' <= input[0] && input[0] <= 'h') &&
		('1' <= input[1] && input[1] <= '8') && 
		('a' <= input[2] && input[2] <= 'h') &&
		('1' <= input[3] && input[3] <= '8')) {
			
			target->srcCol = input[0] - 'a';
			target->srcRow = 7 - (input[1] - '1'); 
			target->destCol = input[2] - 'a';
			target->destRow = 7 - (input[3] - '1');
			return true;
	}

	return false;
}
