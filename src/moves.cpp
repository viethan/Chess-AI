#include "moves.h"

int** gBoardCoords = NULL;

void init_board() {
	wChecked = false;
	bChecked = false;
	gBoardCoords = new int*[BOARD_HEIGHT];

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		switch (i) {
			case 0:
				gBoardCoords[i] = new int[BOARD_WIDTH]{bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook};
				break;
			case 1:
				gBoardCoords[i] = new int[BOARD_WIDTH]{bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn};
				break;
			case 6:
				gBoardCoords[i] = new int[BOARD_WIDTH]{wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn};
				break;
			case 7:
				gBoardCoords[i] = new int[BOARD_WIDTH]{wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook};
				break;
			default:
				gBoardCoords[i] = new int[BOARD_WIDTH]{0, 0, 0, 0, 0, 0, 0, 0}; 	 	
		}		
	}
}

void close_moves() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		delete gBoardCoords[i];
	}
	delete gBoardCoords;
}

int** copy_board(int **board) {
	int** copy = new int*[BOARD_HEIGHT];
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		copy[i] = new int[BOARD_WIDTH];
	}

	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			copy[row][column] = board[row][column];
		}
	}

	return copy;
}


int** make_move(Move move, int** board) {
	int **newBoard = copy_board(board);
	newBoard[move.destRow][move.destCol] = newBoard[move.srcRow][move.srcCol]; 
	newBoard[move.srcRow][move.srcCol] = 0;

	return newBoard;
}

void free_board(int** board) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		delete board[i];
	}
	delete board;
}

std::vector<Move> get_moves(int **board, bool colour) {
	if (colour == WHITE && wChecked) {
		return escape_check(board, colour);
	}

	if (colour == BLACK && bChecked) {
		return escape_check(board, colour);
	}

	int colourLower, colourUpper;
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	std::vector<Move> moves = std::vector<Move>(), piece_moves;
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			if (colourLower <= board[row][column] && board[row][column] <= colourUpper) {
				switch (board[row][column]) {
					case wPawn:
					case bPawn:
						piece_moves = pawnMove(board, row, column, colour);
						cout << "pawn at row " << 7 - row << ", col " << column << endl;
						break;
					case wKnight:
					case bKnight:
						piece_moves = knightMove(board, row, column, colour);
						cout << "knight at row " << 7 - row << ", col " << column << endl;
						break;
					case wBishop:
					case bBishop:
						piece_moves = bishopMove(board, row, column, colour);
						cout << "bishop at row " << 7 - row << ", col " << column << endl;
						break;
					case wRook:
					case bRook:
						//piece_moves = rookMove(board, row, column, colour); COMMENTED FOR NOW
						cout << "rook at row " << 7 - row << ", col " << column << endl;
						break;
					case wQueen:
					case bQueen:
						//piece_moves = queenMove(board, row, column, colour); COMMENTED FOR NOW
						cout << "queen at row " << 7 - row << ", col " << column << endl;
						break;
					case wKing:
					case bKing:
						piece_moves = kingMove(board, row, column, colour);
						cout << "king at row " << 7 - row << ", col " << column << endl;
				}

				moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
			}
		}
	}

	cout << "Hello?????" << endl;
	cout << moves.size() << endl;
	for (int i = 0; i < moves.size(); ++i) {
        cout << "srcRow: " << 7-moves.at(i).srcRow << "; srcCol: " << moves.at(i).srcCol << " destRow: " << 7-moves.at(i).destRow << "; destCol: " << moves.at(i).destCol << endl;
    }

	return moves;
}

std::vector<Move> escape_check(int **board, bool colour) {
	return std::vector<Move>();
}

std::vector<Move> pawnMove(int** board, int row, int column, bool colour) {
	return std::vector<Move>();
}

std::vector<Move> knightMove(int** board, int row, int column, bool colour) {
	return std::vector<Move>();
}

std::vector<Move> bishopMove(int** board, int row, int column, bool colour) {
	std::vector<Move> moves = std::vector<Move>();

	int colourLower, colourUpper;
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	int ro, col;

	// top-right diagonal
	ro = row - 1;
	col = column + 1;

	while (ro >= 0 && col < BOARD_WIDTH) {
		if (board[ro][col] == 0) { // empty square
			moves.push_back(Move{row, column, ro, col});
		} else if (colourLower <= board[ro][col] && board[ro][col] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, ro, col});
			break;
		}

		ro--; col++;
	}

	// bottom-left diagonal
	ro = row + 1;
	col = column - 1;

	while (ro < BOARD_HEIGHT && col >= 0) {
		if (board[ro][col] == 0) { // empty square
			moves.push_back(Move{row, column, ro, col});
		} else if (colourLower <= board[ro][col] && board[ro][col] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, ro, col});
			break;
		}
		
		ro++; col--;
	}


	// top-left diagonal
	ro = row - 1;
	col = column - 1;

	while (ro >= 0 && col >= 0) {
		if (board[ro][col] == 0) { // empty square
			moves.push_back(Move{row, column, ro, col});
		} else if (colourLower <= board[ro][col] && board[ro][col] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, ro, col});
			break;
		}
		
		ro--; col--;
	}


	// bottom-right diagonal
	ro = row + 1;
	col = column + 1;

	while (ro < BOARD_HEIGHT && col < BOARD_WIDTH) {
		if (board[ro][col] == 0) { // empty square
			moves.push_back(Move{row, column, ro, col});
		} else if (colourLower <= board[ro][col] && board[ro][col] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, ro, col});
			break;
		}
		
		ro++; col++;
	}

	return moves;
}

std::vector<Move> rookMove(int** board, int row, int column, bool colour) {
	std::vector<Move> moves = std::vector<Move>();

	int colourLower, colourUpper;
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	// right of rook
	for (int col = column+1; col < BOARD_WIDTH; col++) {
		if (board[row][col] == 0) { // empty square
			moves.push_back(Move{row, column, row, col});
		} else if (colourLower <= board[row][col] && board[row][col] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, row, col});
			break;
		}
	}

	// left of rook
	for (int col = column-1; col >= 0; col--) {
		if (board[row][col] == 0) { // empty square
			moves.push_back(Move{row, column, row, col});
		} else if (colourLower <= board[row][col] && board[row][col] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, row, col});
			break;
		}
	}		

	// bottom of rook
	for (int ro = row+1; ro < BOARD_HEIGHT; ro++) {
		if (board[ro][column] == 0) { // empty square
			moves.push_back(Move{row, column, ro, column});
		} else if (colourLower <= board[ro][column] && board[ro][column] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, ro, column});
			break;
		}
	}

	// top of rook
	for (int ro = row-1; ro >= 0; ro--) {
		if (board[ro][column] == 0) { // empty square
			moves.push_back(Move{row, column, ro, column});
		} else if (colourLower <= board[ro][column] && board[ro][column] <= colourUpper) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(Move{row, column, ro, column});
			break;
		}
	}

	return moves;
}

std::vector<Move> queenMove(int** board, int row, int column, bool colour) {
	std::vector<Move> moves = std::vector<Move>(), rook_moves, bishop_moves;
	
	rook_moves = rookMove(board, row, column, colour);
	moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());

	bishop_moves = bishopMove(board, row, column, colour);
	moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());

	return moves;
}

std::vector<Move> kingMove(int** board, int row, int column, bool colour) {
	return std::vector<Move>();
}