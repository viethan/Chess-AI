#include <iostream>
#include "forall.h"
#include "visualise.h"
#include "moves.h"
using namespace std;
bool gColour;

// MUST FIND A WAY TO SHUT DOWN THIS THREAD CLEANLY
static int PollEvents(void *ptr)
{
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {}
    }

    return 1;
}

int main(int argc,char *argv[]){
    gColour = 1;


    if (!init_SDL()) {
    	cout << "Failed to initialize SDL" << endl;
    	return -1;
    }

    if (!loadMedia()) {
    	cout << "Failed to load media" << endl;
    	return -1;
    }

    init_board();

    // THE MOVES ARE FROM SDL POINT OF VIEW

    
    int** temp;
    temp = make_move(Move{7-1, 4, 7-3, 4}, gBoardCoords);
    free_board(gBoardCoords);
    gBoardCoords = temp;
    
    temp = make_move(Move{7-7, 4, 7-3, 4}, gBoardCoords);
    free_board(gBoardCoords);
    gBoardCoords = temp;

    temp = make_move(Move{7-0, 5, 7-4, 2}, gBoardCoords);
    free_board(gBoardCoords);
    gBoardCoords = temp;

    //std::vector<Move> availableMoves;
    //availableMoves = get_moves(gBoardCoords, 1);

    SDL_CreateThread(PollEvents, "TestThread", (void *)NULL);

    while (true) {
        SDL_Thread *thread;
        int         threadReturnValue;

    	if (!visualise()) {
    		cout << "Failed to visualise" << endl;
    		return -1;
    	}

        string input;
        Move userMove;
        bool validInput = false;
        while (!validInput) {
            cin >> input;

            if (input.compare("quit") == 0) { break; }
            if (string2move(input, &userMove) && check_move(userMove, gBoardCoords, gColour)) { 
                cout << "Good move" << endl; 
                validInput = true; } 
            else {
                cout << "bad input" << endl;
            }
        }

        if (input.compare("quit") == 0) break;


        // Let the AI choose its move

        // Perform AI's chosen move
    }    

    close_visualise();
    close_moves();
    return 0;
}