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
				gBoardCoords[i] = new int[BOARD_WIDTH]{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}; 	 	
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
	newBoard[move.srcRow][move.srcCol] = EMPTY;

	return newBoard;
}

void free_board(int** board) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		delete board[i];
	}
	delete board;
}

std::vector<Move> get_moves(int **board, bool colour) {
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
				piece_moves.clear();
				switch (board[row][column]) {
					case wPawn:
					case bPawn:
						piece_moves = pawnMove(board, row, column, colour); 
						break;
					case wKnight:
					case bKnight:
						piece_moves = knightMove(board, row, column, colour);
						break;
					case wBishop:
					case bBishop:
						piece_moves = bishopMove(board, row, column, colour);
						break;
					case wRook:
					case bRook:
						piece_moves = rookMove(board, row, column, colour);
						break;
					case wQueen:
					case bQueen:
						piece_moves = queenMove(board, row, column, colour);
						break;
					case wKing:
					case bKing:
						piece_moves = kingMove(board, row, column, colour);
				}

				moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());

			}
		}
	}

	int **temp_copy;
	for (vector<Move>::iterator it = moves.begin(); it != moves.end();) {
		if (checked(temp_copy = make_move(Move{it->srcRow, it->srcCol, it->destRow, it->destCol}, board), colour)) {
			moves.erase(it);
		} else {
			it++;
		}

		free_board(temp_copy);
    }

	cout << moves.size() << endl;
	for (int i = 0; i < moves.size(); ++i) {
        cout << "srcRow: " << 7-moves.at(i).srcRow << "; srcCol: " << moves.at(i).srcCol << " destRow: " << 7-moves.at(i).destRow << "; destCol: " << moves.at(i).destCol << endl;
    }

	return moves;
}

std::vector<Move> pawnMove(int** board, int row, int column, bool colour) {
	std::vector<Move> moves = std::vector<Move>();

	int colourLower, colourUpper;
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	if (colour == WHITE) {
		// move two squares forward
		if (row == 6 && board[4][column] == EMPTY) {
			moves.push_back(Move{row, column, 4, column});
		} 

		// move one square forward
		if (row-1 >= 0 && board[row-1][column] == EMPTY) {
			moves.push_back(Move{row, column, row-1, column});
		}

		// attack diagonally
		if (row-1 >= 0 && column-1 >= 0 && \
			! (board[row-1][column-1] == EMPTY || (colourLower <= board[row-1][column-1] && board[row-1][column-1] <= colourUpper))) {
			moves.push_back(Move{row, column, row-1, column-1});		
		}

		if (row-1 >= 0 && column+1 < BOARD_WIDTH && \
			! (board[row-1][column+1] == EMPTY || (colourLower <= board[row-1][column+1] && board[row-1][column+1] <= colourUpper))) {
			moves.push_back(Move{row, column, row-1, column+1});		
		}
	} else {
		// move two squares forward
		if (row == 1 && board[3][column] == EMPTY) {
			moves.push_back(Move{row, column, 3, column});
		}

		// move one square forward
		if (row+1 < BOARD_HEIGHT && board[row+1][column] == EMPTY) {
			moves.push_back(Move{row, column, row+1, column});
		}

		// attack diagonally
		if (row+1 < BOARD_HEIGHT && column-1 >= 0 && \
			! (board[row+1][column-1] == EMPTY || (colourLower <= board[row+1][column-1] && board[row+1][column-1] <= colourUpper))) {
			moves.push_back(Move{row, column, row+1, column-1});		
		}

		if (row+1 < BOARD_HEIGHT && column+1 < BOARD_WIDTH && \
			! (board[row+1][column+1] == EMPTY || (colourLower <= board[row+1][column+1] && board[row+1][column+1] <= colourUpper))) {
			moves.push_back(Move{row, column, row+1, column+1});		
		}
	}

	return moves;
}

std::vector<Move> knightMove(int** board, int row, int column, bool colour) {
	std::vector<Move> moves = std::vector<Move>();

	int colourLower, colourUpper;
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	// Can physically do the move, and it's not in our team
	int ro, col;

	// upper-left1
	ro = row - 2;
	col = column - 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	// upper-left2
	ro = row - 1;
	col = column - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	// upper-right1
	ro = row - 2;
	col = column + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	// upper-right2
	ro = row - 1;
	col = column + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	// bottom-left1
	ro = row + 2;
	col = column - 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	// bottom-left2
	ro = row + 1;
	col = column - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	// bottom-right1
	ro = row + 2;
	col = column + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	// bottom-right2
	ro = row + 1;
	col = column + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		! (colourLower <= board[ro][col] && board[ro][col] <= colourUpper)) { // must not be on the same team
			moves.push_back(Move{row, column, ro, col});
	}

	return moves;
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
		if (board[ro][col] == EMPTY) { // empty square
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
		if (board[ro][col] == EMPTY) { // empty square
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
		if (board[ro][col] == EMPTY) { // empty square
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
		if (board[ro][col] == EMPTY) { // empty square
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
		if (board[row][col] == EMPTY) { // empty square
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
		if (board[row][col] == EMPTY) { // empty square
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
		if (board[ro][column] == EMPTY) { // empty square
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
		if (board[ro][column] == EMPTY) { // empty square
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
	std::vector<Move> moves = std::vector<Move>();
	int colourLower, colourUpper;
	
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	if (row+1 < BOARD_HEIGHT) {
		// bottom
		if (!(colourLower <= board[row+1][column] && board[row+1][column] <= colourUpper)) {
			moves.push_back(Move{row, column, row+1, column});
		}
		// bottom-left
		if (!(colourLower <= board[row+1][column-1] && board[row+1][column-1] <= colourUpper)) {
			moves.push_back(Move{row, column, row+1, column-1});
		}
		// bottom-right
		if (!(colourLower <= board[row+1][column+1] && board[row+1][column+1] <= colourUpper)) {
			moves.push_back(Move{row, column, row+1, column+1});
		}
	}

	if (row-1 >= 0) {
		// upper
		if (!(colourLower <= board[row-1][column] && board[row-1][column] <= colourUpper)) {
			moves.push_back(Move{row, column, row-1, column});
		}
		// upper-left
		if (!(colourLower <= board[row-1][column-1] && board[row-1][column-1] <= colourUpper)) {
			moves.push_back(Move{row, column, row-1, column-1});
		}
		// upper-right
		if (!(colourLower <= board[row-1][column+1] && board[row-1][column+1] <= colourUpper)) {
			moves.push_back(Move{row, column, row-1, column+1});
		}
	}

	// left
	if (column-1 >= 0 && (!(colourLower <= board[row][column-1] && board[row][column-1] <= colourUpper))) {
			moves.push_back(Move{row, column, row, column-1});
	}
	// right
	if (column+1 < BOARD_WIDTH && (!(colourLower <= board[row][column+1] && board[row][column+1] <= colourUpper))) {
			moves.push_back(Move{row, column, row, column+1});
	}

	return moves;
}

bool checked(int **board, bool colour) {
	// Find the king in the specified colour
	int kingRow, kingColumn;

	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			if ((colour == WHITE && board[row][column] == wKing) ||
				(colour == BLACK && board[row][column] == bKing)) {
				kingRow = row;
				kingColumn = column;
			}
		}
	}

	if (checked_knights(board, kingRow, kingColumn, colour) ||
		checked_pawns(board, kingRow, kingColumn, colour) ||
		checked_enemyKing(board, kingRow, kingColumn, colour) ||
		checked_diagonals(board, kingRow, kingColumn, colour) ||
		checked_rankFile(board, kingRow, kingColumn, colour)) {
		return true;
	}
	
	return false;
}

bool checked_enemyKing(int** board, int kingRow, int kingColumn, bool colour) {
	if (kingRow+1 < BOARD_HEIGHT) {
		// bottom
		if ((colour == WHITE && board[kingRow+1][kingColumn] == bKing) ||
			(colour == BLACK && board[kingRow+1][kingColumn] == wKing)) {
			return true;
		}
		// bottom-left
		if ((colour == WHITE && board[kingRow+1][kingColumn-1] == bKing) ||
			(colour == BLACK && board[kingRow+1][kingColumn-1] == wKing)) {
			return true;
		}
		// bottom-right
		if ((colour == WHITE && board[kingRow+1][kingColumn+1] == bKing) ||
			(colour == BLACK && board[kingRow+1][kingColumn+1] == wKing)) {
			return true;
		}
	}

	if (kingRow-1 >= 0) {
		// upper
		if ((colour == WHITE && board[kingRow-1][kingColumn] == bKing) ||
			(colour == BLACK && board[kingRow-1][kingColumn] == wKing)) {
			return true;
		}
		// upper-left
		if ((colour == WHITE && board[kingRow-1][kingColumn-1] == bKing) ||
			(colour == BLACK && board[kingRow-1][kingColumn-1] == wKing)) {
			return true;
		}
		// upper-right
		if ((colour == WHITE && board[kingRow-1][kingColumn+1] == bKing) ||
			(colour == BLACK && board[kingRow-1][kingColumn+1] == wKing)) {
			return true;
		}
	}


	// left
	if (kingColumn-1 >= 0 && 
		((colour == WHITE && board[kingRow][kingColumn-1] == bKing) ||
			(colour == BLACK && board[kingRow][kingColumn-1] == wKing))) {
			return true;
	} 

	// right
	if (kingColumn+1 < BOARD_WIDTH && 
		((colour == WHITE && board[kingRow][kingColumn+1] == bKing) ||
			(colour == BLACK && board[kingRow][kingColumn+1] == wKing))) {
			return true;
	}

	return false;
}

bool checked_diagonals(int** board, int kingRow, int kingColumn, bool colour) {
	int ro, col;

	// top-right diagonal
	ro = kingRow - 1;
	col = kingColumn + 1;

	while (ro >= 0 && col < BOARD_WIDTH) {
		if ((colour == WHITE && (board[ro][col] == bBishop || board[ro][col] == bQueen)) ||
			(colour == BLACK && (board[ro][col] == wBishop || board[ro][col] == wQueen))) { 
			return true;
		} else if (board[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}

		ro--; col++;
	}

	// bottom-left diagonal
	ro = kingRow + 1;
	col = kingColumn - 1;

	while (ro < BOARD_HEIGHT && col >= 0) {
		if ((colour == WHITE && (board[ro][col] == bBishop || board[ro][col] == bQueen)) ||
			(colour == BLACK && (board[ro][col] == wBishop || board[ro][col] == wQueen))) { 
			return true;
		} else if (board[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
		
		ro++; col--;
	}

	// top-left diagonal
	ro = kingRow - 1;
	col = kingColumn - 1;

	while (ro >= 0 && col >= 0) {
		if ((colour == WHITE && (board[ro][col] == bBishop || board[ro][col] == bQueen)) ||
			(colour == BLACK && (board[ro][col] == wBishop || board[ro][col] == wQueen))) { 
			return true;
		} else if (board[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
		
		ro--; col--;
	}

	// bottom-right diagonal
	ro = kingRow + 1;
	col = kingColumn + 1;

	while (ro < BOARD_HEIGHT && col < BOARD_WIDTH) {
		if ((colour == WHITE && (board[ro][col] == bBishop || board[ro][col] == bQueen)) ||
			(colour == BLACK && (board[ro][col] == wBishop || board[ro][col] == wQueen))) { 
			return true;
		} else if (board[ro][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
		
		ro++; col++;
	}

	return false;
}

bool checked_rankFile(int** board, int kingRow, int kingColumn, bool colour) {
	// right
	for (int col = kingColumn+1; col < BOARD_WIDTH; col++) {
		if ((colour == WHITE && (board[kingRow][col] == bRook || board[kingRow][col] == bQueen)) ||
			(colour == BLACK && (board[kingRow][col] == wRook || board[kingRow][col] == wQueen))) { 
			return true;
		} else if (board[kingRow][col] != EMPTY) { // stop looking after encountering a piece
			break;
		}
	}

	// left
	for (int col = kingColumn-1; col >= 0; col--) {
		if ((colour == WHITE && (board[kingRow][col] == bRook || board[kingRow][col] == bQueen)) ||
			(colour == BLACK && (board[kingRow][col] == wRook || board[kingRow][col] == wQueen))) { 
			return true;
		} else if (board[kingRow][col] != EMPTY) {
			break;
		}
	}		

	// bottom of rook
	for (int ro = kingRow+1; ro < BOARD_HEIGHT; ro++) {
		if ((colour == WHITE && (board[ro][kingColumn] == bRook || board[ro][kingColumn] == bQueen)) ||
			(colour == BLACK && (board[ro][kingColumn] == wRook || board[ro][kingColumn] == wQueen))) { 
			return true;
		} else if (board[ro][kingColumn] != EMPTY) {
			break;
		}
	}

	// top of rook
	for (int ro = kingRow-1; ro >= 0; ro--) {
		if ((colour == WHITE && (board[ro][kingColumn] == bRook || board[ro][kingColumn] == bQueen)) ||
			(colour == BLACK && (board[ro][kingColumn] == wRook || board[ro][kingColumn] == wQueen))) { 
			return true;
		} else if (board[ro][kingColumn] != EMPTY) {
			break;
		}
	}

	return false;
}

bool checked_pawns(int** board, int kingRow, int kingColumn, bool colour) {
	if (colour == WHITE) {
		if (kingRow-1 >= 0) {
			if (kingColumn-1 >= 0 && board[kingRow-1][kingColumn-1] == bPawn) {
				return true;
			}
			if (kingColumn+1 < BOARD_WIDTH && board[kingRow-1][kingColumn+1] == bPawn) {
				return true;
			}
		}
	} else {
		if (kingRow+1 < BOARD_HEIGHT) {
			if (kingColumn-1 >= 0 && board[kingRow+1][kingColumn-1] == wPawn) {
				return true;
			}
			if (kingColumn+1 < BOARD_WIDTH && board[kingRow+1][kingColumn+1] == wPawn) {
				return true;
			}	
		}
	}

	return false;
}

bool checked_knights(int** board, int kingRow, int kingColumn, bool colour) {
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
		board[ro][col] == opponent_knight) { 
			return true;
	}

	// upper-left2
	ro = kingRow - 1;
	col = kingColumn - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		board[ro][col] == opponent_knight) {
			return true;
	}

	// upper-right1
	ro = kingRow - 2;
	col = kingColumn + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		board[ro][col] == opponent_knight) {
			return true;
	}

	// upper-right2
	ro = kingRow - 1;
	col = kingColumn + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		board[ro][col] == opponent_knight) {
			return true;
	}

	// bottom-left1
	ro = kingRow + 2;
	col = kingColumn - 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		board[ro][col] == opponent_knight) {
			return true;
	}

	// bottom-left2
	ro = kingRow + 1;
	col = kingColumn - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		board[ro][col] == opponent_knight) {
			return true;
	}

	// bottom-right1
	ro = kingRow + 2;
	col = kingColumn + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		board[ro][col] == opponent_knight) { // must be a knight
			return true;
	}

	// bottom-right2
	ro = kingRow + 1;
	col = kingColumn + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		board[ro][col] == opponent_knight) { // must be a knight
			return true;
	}

	return false;
}