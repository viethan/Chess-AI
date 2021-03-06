// GameState.h
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "Board.h"
#include "minimax.h"
#include "visualise.h"
#include "forall.h"
#include "pieces/pieceMove.h"

class GameState {
	public:
		int status;
		bool usersTurn, userColour;

		GameState();
		~GameState();
		void userMoves();
		void AIMoves();
		void visualise();
		void printHistory();
	private:
		Board* board;
		std::vector<std::string> history;

		void status_check();
		int selectPlayer();
};

// Note: the destructor doesn't free the SDL surfaces
// associated with the current game
// This is so that the window doesn't close immediately
// after the game is over
// If called the constructor for new game, it will close it then

#endif