#include "Board.h"

Board::Board() {
	this->pos = new int*[BOARD_HEIGHT];
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		switch (i) {
			case 0:
				//this->pos[i] = new int[BOARD_WIDTH]{bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook};
				this->pos[i] = new int[BOARD_WIDTH]{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, bKing};
				break;
			case 1:
				//this->pos[i] = new int[BOARD_WIDTH]{bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn};
				this->pos[i] = new int[BOARD_WIDTH]{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
				break;
			case 6:
				//this->pos[i] = new int[BOARD_WIDTH]{wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn};
				this->pos[i] = new int[BOARD_WIDTH]{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
				break;
			case 7:
				this->pos[i] = new int[BOARD_WIDTH]{wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook};
				break;
			default:
				this->pos[i] = new int[BOARD_WIDTH]{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}; 	 	
		}		
	}

	this->turn = WHITE;
	this->get_moves();
}

// just pos
Board::Board(int** paramPos) {
	this->pos = new int*[BOARD_HEIGHT];

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		this->pos[i] = new int[BOARD_WIDTH];
	}

	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			this->pos[row][column] = paramPos[row][column];
		}
	}
}

Board::~Board() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		delete this->pos[i];
	}
	delete this->pos;
}


Board* Board::make_move(Move move, bool getMoves) {  // ???????????????????????????????????????????
	Board* newBoard = new Board(this->pos);
	newBoard->pos[move.destRow][move.destCol] = newBoard->pos[move.srcRow][move.srcCol]; 
	newBoard->pos[move.srcRow][move.srcCol] = EMPTY;
	newBoard->turn = !this->turn;
	if (getMoves) newBoard->get_moves(); // this is so we don't recurse infinitely for no reason

	return newBoard;
}

void Board::get_moves() {
	int colourLower, colourUpper;
	if (this->turn == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	this->moves = std::vector<Move>();
	std::vector<Move> piece_moves;
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			if (colourLower <= this->pos[row][column] && this->pos[row][column] <= colourUpper) {
				piece_moves.clear();
				switch (this->pos[row][column]) {
					case wPawn:
					case bPawn:
						piece_moves = pawnMove(this->pos, row, column, this->turn); 
						break;
					case wKnight:
					case bKnight:
						piece_moves = knightMove(this->pos, row, column, this->turn);
						break;
					case wBishop:
					case bBishop:
						piece_moves = bishopMove(this->pos, row, column, this->turn);
						break;
					case wRook:
					case bRook:
						piece_moves = rookMove(this->pos, row, column, this->turn);
						break;
					case wQueen:
					case bQueen:
						piece_moves = queenMove(this->pos, row, column, this->turn);
						break;
					case wKing:
					case bKing:
						piece_moves = kingMove(this->pos, row, column, this->turn);
				}

				this->moves.insert(this->moves.end(), piece_moves.begin(), piece_moves.end());

			}
		}
	}

	// We have to make sure that our king is not accidentally checked
	// self-inflicting discovered attack
	// also helps if the king was checked to begin with
	// cout << "getMoves calling checked()" << endl;
	// cout << "Before: " << moves.size() << endl;
	// for (int i = 0; i < moves.size(); ++i) {
 //        cout << "srcRow: " << 7-moves.at(i).srcRow << "; srcCol: " << moves.at(i).srcCol << " destRow: " << 7-moves.at(i).destRow << "; destCol: " << moves.at(i).destCol << endl;
 //    }

	Board* tempBoard;
	for (vector<Move>::iterator it = this->moves.begin(); it != this->moves.end();) {
		tempBoard = make_move(Move{it->srcRow, it->srcCol, it->destRow, it->destCol}, false);
		if (tempBoard->checked(this->turn)) {
			this->moves.erase(it);
		} else {
			it++;
		}

		delete tempBoard;
    }

	// cout << "After: " << moves.size() << endl;
	// for (int i = 0; i < moves.size(); ++i) {
 //        cout << "srcRow: " << 7-moves.at(i).srcRow << "; srcCol: " << moves.at(i).srcCol << " destRow: " << 7-moves.at(i).destRow << "; destCol: " << moves.at(i).destCol << endl;
 //    }
}

bool Board::check_move(Move tryMove) {
	for (vector<Move>::iterator it = this->moves.begin(); it != this->moves.end(); it++) {
		if (it->srcRow == tryMove.srcRow &&
			it->srcCol == tryMove.srcCol &&
			it->destRow == tryMove.destRow &&
			it->destCol == tryMove.destCol){
					return true;
				}
    }
    return false;
}






bool Board::checked(bool colour) {
	// Find the king in the specified colour
	int kingRow = -1, kingColumn = -1;

	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			if ((colour == WHITE && this->pos[row][column] == wKing) ||
				(colour == BLACK && this->pos[row][column] == bKing)) {
				kingRow = row;
				kingColumn = column;
			}
		}
	}

	if (kingRow == -1 || kingColumn == -1) return true;

	//cout << "King coordinates: " << kingRow << kingColumn << endl;
	if (this->checked_knights(kingRow, kingColumn, colour) ||
		this->checked_pawns(kingRow, kingColumn, colour) ||
		this->checked_enemyKing(kingRow, kingColumn, colour) ||
		this->checked_diagonals(kingRow, kingColumn, colour) ||
		this->checked_rankFile(kingRow, kingColumn, colour)) {
		return true;
	}
	
	return false;
}

bool Board::checked_enemyKing(int kingRow, int kingColumn, bool colour) {
	if (kingRow+1 < BOARD_HEIGHT) {
		// bottom
		if ((colour == WHITE && this->pos[kingRow+1][kingColumn] == bKing) ||
			(colour == BLACK && this->pos[kingRow+1][kingColumn] == wKing)) {
			return true;
		}
		// bottom-left
		if (kingColumn-1 >= 0 && ((colour == WHITE && this->pos[kingRow+1][kingColumn-1] == bKing) ||
					(colour == BLACK && this->pos[kingRow+1][kingColumn-1] == wKing))) {
			return true;
		}
		// bottom-right
		if (kingColumn+1 < BOARD_WIDTH && ((colour == WHITE && this->pos[kingRow+1][kingColumn+1] == bKing) ||
					(colour == BLACK && this->pos[kingRow+1][kingColumn+1] == wKing))) {
			return true;
		}
	}

	if (kingRow-1 >= 0) {
		// upper
		if ((colour == WHITE && this->pos[kingRow-1][kingColumn] == bKing) ||
			(colour == BLACK && this->pos[kingRow-1][kingColumn] == wKing)) {
			return true;
		}
		// upper-left
		if (kingColumn-1 >= 0 && ((colour == WHITE && this->pos[kingRow-1][kingColumn-1] == bKing) ||
					(colour == BLACK && this->pos[kingRow-1][kingColumn-1] == wKing))) {
			return true;
		}
		// upper-right
		if (kingColumn+1 < BOARD_WIDTH && ((colour == WHITE && this->pos[kingRow-1][kingColumn+1] == bKing) ||
					(colour == BLACK && this->pos[kingRow-1][kingColumn+1] == wKing))) {
			return true;
		}
	}


	// left
	if (kingColumn-1 >= 0 && 
		((colour == WHITE && this->pos[kingRow][kingColumn-1] == bKing) ||
			(colour == BLACK && this->pos[kingRow][kingColumn-1] == wKing))) {
			return true;
	} 

	// right
	if (kingColumn+1 < BOARD_WIDTH && 
		((colour == WHITE && this->pos[kingRow][kingColumn+1] == bKing) ||
			(colour == BLACK && this->pos[kingRow][kingColumn+1] == wKing))) {
			return true;
	}

	return false;
}

bool Board::checked_diagonals(int kingRow, int kingColumn, bool colour) {
	int ro, col;

	// top-right diagonal
	ro = kingRow - 1;
	col = kingColumn + 1;

	while (ro >= 0 && col < BOARD_WIDTH) {
		if ((colour == WHITE && (this->pos[ro][col] == bBishop || this->pos[ro][col] == bQueen)) ||
			(colour == BLACK && (this->pos[ro][col] == wBishop || this->pos[ro][col] == wQueen))) { 
			return true;
		} else if (this->pos[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}

		ro--; col++;
	}

	// bottom-left diagonal
	ro = kingRow + 1;
	col = kingColumn - 1;

	while (ro < BOARD_HEIGHT && col >= 0) {
		if ((colour == WHITE && (this->pos[ro][col] == bBishop || this->pos[ro][col] == bQueen)) ||
			(colour == BLACK && (this->pos[ro][col] == wBishop || this->pos[ro][col] == wQueen))) { 
			return true;
		} else if (this->pos[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
		
		ro++; col--;
	}

	// top-left diagonal
	ro = kingRow - 1;
	col = kingColumn - 1;

	while (ro >= 0 && col >= 0) {
		if ((colour == WHITE && (this->pos[ro][col] == bBishop || this->pos[ro][col] == bQueen)) ||
			(colour == BLACK && (this->pos[ro][col] == wBishop || this->pos[ro][col] == wQueen))) { 
			return true;
		} else if (this->pos[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
		
		ro--; col--;
	}

	// bottom-right diagonal
	ro = kingRow + 1;
	col = kingColumn + 1;

	while (ro < BOARD_HEIGHT && col < BOARD_WIDTH) {
		if ((colour == WHITE && (this->pos[ro][col] == bBishop || this->pos[ro][col] == bQueen)) ||
			(colour == BLACK && (this->pos[ro][col] == wBishop || this->pos[ro][col] == wQueen))) { 
			return true;
		} else if (this->pos[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
		
		ro++; col++;
	}

	return false;
}

bool Board::checked_rankFile(int kingRow, int kingColumn, bool colour) {
	// right
	for (int col = kingColumn+1; col < BOARD_WIDTH; col++) {
		if ((colour == WHITE && (this->pos[kingRow][col] == bRook || this->pos[kingRow][col] == bQueen)) ||
			(colour == BLACK && (this->pos[kingRow][col] == wRook || this->pos[kingRow][col] == wQueen))) { 
			return true;
		} else if (this->pos[kingRow][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
	}

	// left
	for (int col = kingColumn-1; col >= 0; col--) {
		if ((colour == WHITE && (this->pos[kingRow][col] == bRook || this->pos[kingRow][col] == bQueen)) ||
			(colour == BLACK && (this->pos[kingRow][col] == wRook || this->pos[kingRow][col] == wQueen))) { 
			return true;
		} else if (this->pos[kingRow][col] != EMPTY) {
			break;
		}
	}		

	// bottom of rook
	for (int ro = kingRow+1; ro < BOARD_HEIGHT; ro++) {
		if ((colour == WHITE && (this->pos[ro][kingColumn] == bRook || this->pos[ro][kingColumn] == bQueen)) ||
			(colour == BLACK && (this->pos[ro][kingColumn] == wRook || this->pos[ro][kingColumn] == wQueen))) { 
			return true;
		} else if (this->pos[ro][kingColumn] != EMPTY) {
			break;
		}
	}

	// top of rook
	for (int ro = kingRow-1; ro >= 0; ro--) {
		if ((colour == WHITE && (this->pos[ro][kingColumn] == bRook || this->pos[ro][kingColumn] == bQueen)) ||
			(colour == BLACK && (this->pos[ro][kingColumn] == wRook || this->pos[ro][kingColumn] == wQueen))) { 
			return true;
		} else if (this->pos[ro][kingColumn] != EMPTY) {
			break;
		}
	}

	return false;
}

bool Board::checked_pawns(int kingRow, int kingColumn, bool colour) {
	if (colour == WHITE) {
		if (kingRow-1 >= 0) {
			if (kingColumn-1 >= 0 && this->pos[kingRow-1][kingColumn-1] == bPawn) {
				return true;
			}
			if (kingColumn+1 < BOARD_WIDTH && this->pos[kingRow-1][kingColumn+1] == bPawn) {
				return true;
			}
		}
	} else {
		if (kingRow+1 < BOARD_HEIGHT) {
			if (kingColumn-1 >= 0 && this->pos[kingRow+1][kingColumn-1] == wPawn) {
				return true;
			}
			if (kingColumn+1 < BOARD_WIDTH && this->pos[kingRow+1][kingColumn+1] == wPawn) {
				return true;
			}	
		}
	}

	return false;
}

bool Board::checked_knights(int kingRow, int kingColumn, bool colour) {
	int opponent_knight;
	if (colour == WHITE) {
		opponent_knight = bKnight; 
	} else {
		opponent_knight = wKnight;
	}

	int ro, col;

	// upper-left1
	ro = kingRow - 2;
	col = kingColumn - 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) { 
			return true;
	}

	// upper-left2
	ro = kingRow - 1;
	col = kingColumn - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) {
			return true;
	}

	// upper-right1
	ro = kingRow - 2;
	col = kingColumn + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) {
			return true;
	}

	// upper-right2
	ro = kingRow - 1;
	col = kingColumn + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) {
			return true;
	}

	// bottom-left1
	ro = kingRow + 2;
	col = kingColumn - 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) {
			return true;
	}

	// bottom-left2
	ro = kingRow + 1;
	col = kingColumn - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) {
			return true;
	}

	// bottom-right1int Board::gameOver()
	ro = kingRow + 2;
	col = kingColumn + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) { // must be a knight
			return true;
	}

	// bottom-right2
	ro = kingRow + 1;
	col = kingColumn + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		this->pos[ro][col] == opponent_knight) { // must be a knight
			return true;
	}

	return false;
}


int Board::gameOver() {
	if (this->moves.size() == 0) {
		if (this->checked(this->turn)) return LOSE;
		return STALEMATE;
	}

	return CONTINUE; 
}