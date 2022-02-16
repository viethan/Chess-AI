#include <iostream>
#include "gameState.h"
using namespace std;

bool QUIT;
vector<string> history;

static int PollEvents(void *ptr)
{
    SDL_Event e;
    while (QUIT == false) { 
        while (SDL_PollEvent(&e)) {}
    }

    return 1;
}

int main(int argc,char *argv[]){

    // These will prevent our game window to be deemed unresponsive
    SDL_Thread *thread;
    int         threadReturnValue;
    thread = SDL_CreateThread(PollEvents, "Events", (void *)NULL);

    bool prevWindow = false;
    QUIT = false;
    while (!QUIT) {
        bool playerMoves = false;
        int colour = selectPlayer();
        if (colour == WHITE) playerMoves = true;
        if (colour == -1) break;

        history = vector<string>();
        if (prevWindow == true) close_visualise();
        int** board = init_main(colour);
        if (board == NULL) return -1;
        prevWindow = true;
        
        int status = CONTINUE;
        while (status == CONTINUE && !QUIT) {
            if (!visualise(board, colour)) {
    		  cout << "Failed to visualise" << endl;
    		  return -1;
    	    }

            if (playerMoves) {
                board = userMoves(board, colour);
                playerMoves = false;
                if (!QUIT) status = status_check(board, !colour);
            } else {
                board = AIMoves(board, !colour);
                playerMoves = true;                
                status = status_check(board, colour);
            }

            cout << "\033[2J\033[1;1H";
            for (vector<string>::iterator it = history.begin(); it != history.end(); it++) {
                cout << *it << endl;
            }
        }

        if (board != NULL) free_board(board); // technically optional
        if (!visualise(board, colour)) {
              cout << "Failed to visualise" << endl;
              return -1;
        }
        cout << "Game Over!" << endl;
    }

    if (prevWindow == true) close_visualise();
    SDL_WaitThread(thread, &threadReturnValue);
    return 0;
}