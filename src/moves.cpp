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
	move.srcRow = 7 - move.srcRow;
	move.destRow = 7 - move.destRow;

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

	std::vector<Move> moves, piece_moves;
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			if (colourLower <= board[row][column] && board[row][column] <= colourUpper) {
				switch (board[row][column]) {
					case wPawn:
					case bPawn:
						piece_moves = pawnMove(board, row, column, colour);
						//cout << "pawn at row " << 7 - row << ", col " << column << endl;
						break;
					case wKnight:
					case bKnight:
						piece_moves = knightMove(board, row, column, colour);
						//cout << "knight at row " << 7 - row << ", col " << column << endl;
						break;
					case wBishop:
					case bBishop:
						piece_moves = BishopMove(board, row, column, colour);
						//cout << "bishop at row " << 7 - row << ", col " << column << endl;
						break;
					case wRook:
					case bRook:
						piece_moves = RookMove(board, row, column, colour);
						//cout << "rook at row " << 7 - row << ", col " << column << endl;
						break;
					case wQueen:
					case bQueen:
						piece_moves = QueenMove(board, row, column, colour);
						//cout << "queen at row " << 7 - row << ", col " << column << endl;
						break;
					case wKing:
					case bKing:
						piece_moves = KingMove(board, row, column, colour);
						//cout << "king at row " << 7 - row << ", col " << column << endl;
				}

				moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
			}
		}
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

std::vector<Move> BishopMove(int** board, int row, int column, bool colour) {
	return std::vector<Move>();
}

std::vector<Move> RookMove(int** board, int row, int column, bool colour) {
	return std::vector<Move>();
}

std::vector<Move> QueenMove(int** board, int row, int column, bool colour) {
	return std::vector<Move>();
}

std::vector<Move> KingMove(int** board, int row, int column, bool colour) {
	return std::vector<Move>();
}