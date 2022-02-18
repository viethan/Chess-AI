#include "minimax.h"

int eval(int **board) {
	int score = 0;
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int col = 0; col < BOARD_WIDTH; col++) {
			if (board[row][col] != EMPTY) {
				switch (board[row][col]) {
					case wPawn:
						score += pawnTable[row][col] + pawnVal;
						break;
					case bPawn:
						score += (pawnTable[7-row][7-col] + pawnVal) * (-1);
						break;
					case wKnight:
						score += knightTable[row][col] + knightVal;
						break;
					case bKnight:
						score += (knightTable[7-row][7-col] + knightVal) * (-1);
						break;
					case wBishop:
						score += bishopTable[row][col] + bishopVal;
						break;
					case bBishop:
						score += (bishopTable[7-row][7-col] + bishopVal) * (-1);
						break;
					case wRook:
						score += rookTable[row][col] + rookVal;
						break;
					case bRook:
						score += (rookTable[7-row][7-col] + rookVal) * (-1);
						break;
					case wQueen:
						score += queenTable[row][col] + queenVal;
						break;
					case bQueen:
						score += (queenTable[7-row][7-col] + queenVal) * (-1);
						break;
					case wKing:
						score += kingTable[row][col] + kingVal;
						break;
					case bKing:
						score += (kingTable[7-row][7-col] + kingVal) * (-1);
						break;
					}
			}
		}
	}

	return score;
}

pieceMove getOptimalMove(Board* board, bool colour) {
	MoveEval best = minimax(board, MAX_DEPTH, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), colour);
	return best.move;
}

MoveEval minimax(Board* board, int depth, int alpha, int beta, bool colour) {
	// Game over, colour is being checked and has no moves
	if (board->moves.size() == 0 && board->checked(colour)) {
		if (colour == WHITE) return MoveEval{ pieceMove(), std::numeric_limits<int>::min() + 1 };
		else  return MoveEval{ pieceMove(), std::numeric_limits<int>::max() - 1 };
	}

	// Stalemate will call eval() as usual
	if (depth == 0 || board->moves.size() == 0) 
		return MoveEval{ pieceMove(), eval(board->pos) };	  

	MoveEval eval, compareEval = MoveEval{}; 
	if (colour == WHITE) compareEval.score = std::numeric_limits<int>::min(); // maximizing
	else if (colour == BLACK) compareEval.score = std::numeric_limits<int>::max(); // minimizing

	for (std::vector<pieceMove>::iterator it = board->moves.begin(); it != board->moves.end(); it++) {
			Board* nextBoard = board->make_move(*it, true);
			eval = minimax(nextBoard, depth-1, alpha, beta, !colour);
			if ((colour == WHITE && eval.score > compareEval.score) || 
				(colour == BLACK && eval.score < compareEval.score)) 
				compareEval = MoveEval{*it, eval.score};

			delete nextBoard;
			if (colour == WHITE) alpha = std::max(alpha, eval.score);
			else beta = std::min(beta, eval.score);
			if (beta <= alpha) break;
	}
	//std::cout << compareEval.score << std::endl;
	return compareEval;
}