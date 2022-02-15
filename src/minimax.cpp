#include "minimax.h"
#include <cstdlib> 
#include <ctime> 

int eval(int **board) {
	srand(static_cast<unsigned int>(time(nullptr))); 
    return rand() % 52;
}

Move getOptimalMove(int **board, bool colour) {
	MoveEval best = minimax(board, MAX_DEPTH, numeric_limits<int>::min(), numeric_limits<int>::max(), colour);
	cout << "Best Move for AI: " << best.move.srcRow << best.move.srcCol << " " << best.move.destRow << best.move.destCol << endl;
	return best.move;
}

MoveEval minimax(int **board, int depth, int alpha, int beta, bool colour) {
	if (depth == 0) return MoveEval{ Move{}, eval(board) };
	// || gameOver(board)

	MoveEval eval, compareEval = MoveEval{}; 
	if (colour == WHITE) compareEval.score = numeric_limits<int>::min(); // maximizing
	else if (colour == BLACK) compareEval.score = numeric_limits<int>::max(); // minimizing

	vector<Move> nextMoves = get_moves(board, colour);
	for (vector<Move>::iterator it = nextMoves.begin(); it != nextMoves.end(); it++) {
			int** nextBoard = make_move(*it, board);
			eval = minimax(nextBoard, depth-1, alpha, beta, !colour);
			if ((colour == WHITE && eval.score > compareEval.score) || 
				(colour == BLACK && eval.score < compareEval.score)) 
				compareEval = MoveEval{*it, eval.score};

			free_board(nextBoard);
			if (colour == WHITE) alpha = max(alpha, eval.score);
			else beta = min(beta, eval.score);
			if (beta <= alpha) break;
	}

	return compareEval;
}