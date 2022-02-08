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

bool init()
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

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void visualise() {
	if ( SDL_BlitSurface(board, NULL, gScreenSurface, NULL) == -1 ) {
        	cout<<"Couldnt do board blitting " << endl;
    	}

    	if (SDL_BlitSurface(Piece_Surfaces[1] ,NULL,gScreenSurface,NULL) == -1 ){
        	cout<<"could not do clear image blitting "<< endl;
    	}

    	SDL_UpdateWindowSurface( gWindow );
}

int main(int argc,char *argv[]){
    

    if (!init()) {
    	cout << "Failed to initialize" << endl;
    	return -1;
    }

    if (!loadMedia()) {
    	cout << "Failed to load media" << endl;
    	return -1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
    	while (SDL_PollEvent(&e)) {
    		if (e.type == SDL_QUIT) quit = true;
    	}

    	visualise();
    }    

    close();
    return 0;
}




// //Loads individual image
// SDL_Surface* loadSurface( std::string path );

// SDL_Surface* loadSurface( std::string path )
// {
// 	//The final optimized image
// 	SDL_Surface* optimizedSurface = NULL;

// 	//Load image at specified path
// 	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
// 	if( loadedSurface == NULL )
// 	{
// 		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
// 	}
// 	else
// 	{
// 		//Convert surface to screen format
// 		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
// 		if( optimizedSurface == NULL )
// 		{
// 			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
// 		}

// 		//Get rid of old loaded surface
// 		SDL_FreeSurface( loadedSurface );
// 	}

// 	return optimizedSurface;
// }