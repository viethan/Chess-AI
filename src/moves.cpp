#include "moves.h"

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
		// move one square forward
		if (row-1 >= 0 && board[row-1][column] == EMPTY) {
			moves.push_back(Move{row, column, row-1, column});
			// move two squares forward
			if (row == 6 && board[4][column] == EMPTY) {
				moves.push_back(Move{row, column, 4, column});
			} 
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
		// move one square forward
		if (row+1 < BOARD_HEIGHT && board[row+1][column] == EMPTY) {
			moves.push_back(Move{row, column, row+1, column});
			// move two squares forward
			if (row == 1 && board[3][column] == EMPTY) {
				moves.push_back(Move{row, column, 3, column});
			}
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
		if (column-1 >= 0 && (!(colourLower <= board[row+1][column-1] && board[row+1][column-1] <= colourUpper))) {
			moves.push_back(Move{row, column, row+1, column-1});
		}
		// bottom-right
		if (column+1 < BOARD_WIDTH && (!(colourLower <= board[row+1][column+1] && board[row+1][column+1] <= colourUpper))) {
			moves.push_back(Move{row, column, row+1, column+1});
		}
	}

	if (row-1 >= 0) {
		// upper
		if (!(colourLower <= board[row-1][column] && board[row-1][column] <= colourUpper)) {
			moves.push_back(Move{row, column, row-1, column});
		}
		// upper-left
		if (column-1 >= 0 && (!(colourLower <= board[row-1][column-1] && board[row-1][column-1] <= colourUpper))) {
			moves.push_back(Move{row, column, row-1, column-1});
		}
		// upper-right
		if (column+1 < BOARD_WIDTH && (!(colourLower <= board[row-1][column+1] && board[row-1][column+1] <= colourUpper))) {
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

bool string2move(string input, Move* target) {
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



