#include <iostream>
#include "forall.h"
#include "visualise.h"
#include "moves.h"
using namespace std;

bool gColour;

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
    
    int** temp;
    temp = make_move(Move{1, 4, 3, 4}, gBoardCoords);
    free_board(gBoardCoords);
    gBoardCoords = temp;
    
    temp = make_move(Move{7, 6, 3, 4}, gBoardCoords);
    free_board(gBoardCoords);
    gBoardCoords = temp;

    std::vector<Move> no;
    no = get_moves(gBoardCoords, gColour);


    bool quit = false;
    SDL_Event e;

    while (!quit) {
    	while (SDL_PollEvent(&e)) {
    		if (e.type == SDL_QUIT) quit = true;
    	}

    	if (!visualise()) {
    		cout << "Failed to visualise" << endl;
    		return -1;
    	}
    }    

    close_visualise();
    close_moves();
    return 0;
}