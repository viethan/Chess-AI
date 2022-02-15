#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "moves.h"
#include "minimax.h"
#include "visualise.h"
using namespace std;

bool QUIT = false;
vector<string> history;

static int PollEvents(void *ptr)
{
    SDL_Event e;
    while (QUIT == false) { 
        while (SDL_PollEvent(&e)) {}
    }

    return 1;
}

int selectPlayer() {
    int n;
    string input;
    bool validInput = false;
    
    while(!validInput) {
        cout << "Enter 0 for White, 1 for Black, 2 for Random" << endl;
        cout << "Type quit in order to exit" << endl;
        cin >> input;
        if (input.size() == 1 && 
            (input[0] == '0' || input[0] == '1' || input[0] == '2')) {
            validInput = true;
            n = input[0] - '0';
        } else if (input.compare("quit") == 0) { 
            QUIT = true;
            return -1;
        }
    }

    if (n == 2) {
        srand(static_cast<unsigned int>(time(nullptr))); 
        return rand() % 2;
    }

    return n;
}

int** userMoves(int** board, bool colour) {
    string input;
    Move userMove;
    bool validInput = false;
    while (!validInput) {
        cout << "Your next move: " << endl;
        cin >> input;

        if (input.compare("quit") == 0) { 
            QUIT = true;
            return board;
        }

        if (string2move(input, &userMove) && 
            check_move(userMove, board, colour)) 
            validInput = true; 
        else cout << "bad input" << endl;
    }

    if (colour == WHITE) {
        history.push_back("White " + input);    
    } else {
        history.push_back("Black " + input);
    }
    

    int** temp;
    temp = make_move(userMove, board);
    free_board(board);
    return temp;
}

int** AIMoves(int** board, bool colour) {
    Move AIMove = getOptimalMove(board, colour);
    string srcCol(1, 'a' + AIMove.srcCol), destCol(1, 'a' + AIMove.destCol);
    string srcRow(1, '1' + (7-AIMove.srcRow)), destRow(1, '1' + (7-AIMove.destRow));
    
    if (colour == WHITE) {
        history.push_back("White " + srcCol + srcRow + destCol + destRow);    
    } else {
        history.push_back("Black " + srcCol + srcRow + destCol + destRow);
    }

    int** temp;
    temp = make_move(AIMove, board);
    free_board(board);
    //SDL_Delay(3000);
    return temp;
}

int** init_main(bool colour) { 
    if (!init_SDL()) {
        cout << "Failed to initialize SDL" << endl;
        return NULL;
    }

    if (!loadMedia(colour)) {
        cout << "Failed to load media" << endl;
        return NULL;
    }

    return init_board();
}

int status_check(int** board, bool colour) {
    int status = gameOver(board, colour);    
    if (status != CONTINUE) {
        if (status == LOSE) {
            if (colour == WHITE) history.push_back("Black wins");
            else history.push_back("White wins");
        } else if (status == STALEMATE) {
            history.push_back("Stalemate");
        }
    }

    return status;
} 

int main(int argc,char *argv[]){
    // These will prevent our game window to be deemed unresponsive
    SDL_Thread *thread;
    int         threadReturnValue;
    thread = SDL_CreateThread(PollEvents, "Events", (void *)NULL);

    bool prevWindow = false;
    while (!QUIT) {
        bool playerMoves;
        int colour = selectPlayer();
        if (colour == WHITE) {
            cout << "You are white" << endl;
            playerMoves = true;
        } else if (colour == BLACK) { 
            cout << "You are black" << endl;
            playerMoves = false;
        } else if (colour == -1) break;

        history = vector<string>();
        if (prevWindow == true) close_visualise();
        int** board = init_main(colour);
        prevWindow = true;
        if (board == NULL) return -1;

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