#include "queenMove.h"

std::vector<pieceMove> queenMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();
	std::vector<pieceMove> rook_moves, bishop_moves;
	
	rook_moves = rookMove::findMoves(board, row, column, colour);
	moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());

	bishop_moves = bishopMove::findMoves(board, row, column, colour);
	moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());

	return moves;
}