/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

enum Pieces { wPawn = 1, wKnight, wBishop, wRook, wQueen, wKing, bPawn, bKnight, bBishop, bRook, bQueen, bKing };

const int BORDER_OFFSET = 18;
const int BOARD_OFFSET = 75;
int** BOARD = NULL;

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* board = NULL;
SDL_Surface** Piece_Surfaces = NULL;

bool init_SDL()
{
	if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
		cout << "SDL could not initialize" << endl;
		cout << "Reason: " << SDL_GetError() << endl;
		return 0;
	}
	
	gWindow = SDL_CreateWindow( "chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(gWindow == NULL) {
		cout << "Window could not be created" << endl; 
		cout << "Reason: " << SDL_GetError() << endl;
		return 0;
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if( initted & flags != flags) {
        cout << "Could not init SDL_Image" << endl;
        cout << "Reason: " << IMG_GetError() << endl;
        return 0;
    }

	//Get window surface
	gScreenSurface = SDL_GetWindowSurface( gWindow );
	return 1;
}

bool loadMedia()
{
	board = IMG_Load("../img/wBoard.png");
    if (board == NULL) {
        cout << "Could not load board img" << endl;
        return 0;
    }

    Piece_Surfaces = new SDL_Surface*[13];

    Piece_Surfaces[wPawn] = IMG_Load("../img/wPawn.png");
    if (Piece_Surfaces[wPawn] == NULL) {
        cout << "Could not load white pawn img" << endl;
        return 0;
    }

    Piece_Surfaces[wKnight] = IMG_Load("../img/wKnight.png");
    if (Piece_Surfaces[wKnight] == NULL) {
        cout << "Could not load white knight img" << endl;
        return 0;
    }

	Piece_Surfaces[wBishop] = IMG_Load("../img/wBishop.png");
    if (Piece_Surfaces[wBishop] == NULL) {
        cout << "Could not load white bishop img" << endl;
        return 0;
    }

    Piece_Surfaces[wRook] = IMG_Load("../img/wRook.png");
    if (Piece_Surfaces[wRook] == NULL) {
        cout << "Could not load white rook img" << endl;
        return 0;
    }

    Piece_Surfaces[wQueen] = IMG_Load("../img/wQueen.png");
    if (Piece_Surfaces[wQueen] == NULL) {
        cout << "Could not load white queen img" << endl;
        return 0;
    }

    Piece_Surfaces[wKing] = IMG_Load("../img/wKing.png");
    if (Piece_Surfaces[wKing] == NULL) {
        cout << "Could not load white king img" << endl;
        return 0;
    }


    Piece_Surfaces[bPawn] = IMG_Load("../img/bPawn.png");
    if (Piece_Surfaces[bPawn] == NULL) {
        cout << "Could not load black pawn img" << endl;
        return 0;
    }

    Piece_Surfaces[bKnight] = IMG_Load("../img/bKnight.png");
    if (Piece_Surfaces[bKnight] == NULL) {
        cout << "Could not load black knight img" << endl;
        return 0;
    }

	Piece_Surfaces[bBishop] = IMG_Load("../img/bBishop.png");
    if (Piece_Surfaces[bBishop] == NULL) {
        cout << "Could not load black bishop img" << endl;
        return 0;
    }

    Piece_Surfaces[bRook] = IMG_Load("../img/bRook.png");
    if (Piece_Surfaces[bRook] == NULL) {
        cout << "Could not load black rook img" << endl;
        return 0;
    }

    Piece_Surfaces[bQueen] = IMG_Load("../img/bQueen.png");
    if (Piece_Surfaces[bQueen] == NULL) {
        cout << "Could not load black queen img" << endl;
        return 0;
    }

    Piece_Surfaces[bKing] = IMG_Load("../img/bKing.png");
    if (Piece_Surfaces[bKing] == NULL) {
        cout << "Could not load black king img" << endl;
        return 0;
    }

	return 1;
}

void close()
{
	SDL_FreeSurface( board );
	board = NULL;

	for (int i = 1; i < 13; i++) {
		if (Piece_Surfaces[i] != NULL) 
			SDL_FreeSurface(Piece_Surfaces[i]);
	}

	delete Piece_Surfaces;
	Piece_Surfaces = NULL;

	for (int i = 0; i < 8; i++) {
		delete BOARD[i];
	}
	delete BOARD;

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool visualise() {
	if (SDL_BlitSurface(board, NULL, gScreenSurface, NULL) == -1) {
        cout << "Error while blitting the board" << endl;
        return 0;
    }

    SDL_Rect dstrect;

    for (int row = 0; row < 8; row++) {
    	for (int column = 0; column < 8; column++) {
			if (BOARD[row][column] != 0) {
				dstrect.x = BORDER_OFFSET + BOARD_OFFSET * column;
				dstrect.y = BORDER_OFFSET + BOARD_OFFSET * row;
				dstrect.w = 75;
				dstrect.h = 75;
    			
    			if (SDL_BlitSurface(Piece_Surfaces[BOARD[row][column]], NULL, gScreenSurface, &dstrect) == -1 ){
        			cout << "Error while blitting piece" << endl;
        			return 0;
    			}		
    		}
    	}
    }

    SDL_UpdateWindowSurface(gWindow);
    return 1;
}

void init_board() {
	BOARD = new int*[8];

	for (int i = 0; i < 8; i++) {
		switch (i) {
			case 0:
				BOARD[i] = new int[8]{bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook};
				break;
			case 1:
				BOARD[i] = new int[8]{bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn};
				break;
			case 6:
				BOARD[i] = new int[8]{wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn};
				break;
			case 7:
				BOARD[i] = new int[8]{wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook};
				break;
			default:
				BOARD[i] = new int[8]{0, 0, 0, 0, 0, 0, 0, 0}; 	 	
		}		
	}
}

//g++ board.cpp -w -lSDL2 -lSDL2_image -o board
int main(int argc,char *argv[]){
    if (!init_SDL()) {
    	cout << "Failed to initialize SDL" << endl;
    	return -1;
    }

    if (!loadMedia()) {
    	cout << "Failed to load media" << endl;
    	return -1;
    }

    init_board();
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

    close();
    return 0;
}