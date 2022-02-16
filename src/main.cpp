#include "GameState.h"

bool mainQuit = false;

static int PollEvents(void *ptr)
{
    SDL_Event e;
    while (!mainQuit) { 
        while (SDL_PollEvent(&e)) {}
    }

    return 1;
}

int main(int argc,char *argv[]){
    // These will prevent our game window to be deemed unresponsive
    SDL_Thread *thread;
    int         threadReturnValue;
    thread = SDL_CreateThread(PollEvents, "Events", (void *)NULL);

    while (!mainQuit) {
        GameState* currentGame = new GameState();

        while (currentGame->status == CONTINUE) {
            currentGame->visualise();
            if (currentGame->usersTurn) 
                currentGame->userMoves();
            else
                currentGame->AIMoves();
            currentGame->printHistory();
        }

        // visualise the last move that led to
        // the status != CONTINUE
        // only when status != QUIT because either nothing to vis
        // or already visualised (midgame)
        if (currentGame->status == QUIT) mainQuit = true;
        else currentGame->visualise();
        delete currentGame;
    }

    if (SDL_WasInit(SDL_INIT_EVERYTHING)) close_visualise();
    SDL_WaitThread(thread, &threadReturnValue);
    return 0;
}