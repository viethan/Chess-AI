#include "GameState.h"

Board* init_main(bool colour);

GameState::GameState() {
    this->status = CONTINUE;
    this->userColour = selectPlayer();

    // in case the user quits at the menu
    if (this->status == CONTINUE) {    
        if (this->userColour == WHITE) this->usersTurn = true;
        else this->usersTurn = false;
        this->history = std::vector<std::string>();
        this->board = init_main(this->userColour); // colour to rotate board or not
        if (this->board == NULL) this->status = QUIT;
    }
}

GameState::~GameState() {
    // only if a game was played to begin with
    if (this->board != NULL) {
        std::cout << "Game Over!" << std::endl;
        delete this->board;
    }
}

int GameState::selectPlayer() {
    bool player;
    std::string input;
    
    while(true) {
        std::cout << "Enter 0 for White, 1 for Black, 2 for Random" << std::endl;
        std::cout << "Type quit in order to exit" << std::endl;
        std::cin >> input;
        
        if (input.compare("quit") == 0) { 
            this->status = QUIT;
            return -1;
        }

        if (input.size() == 1) {
            // player wants to play white/black        
            if (input[0] == '0' || input[0] == '1') {
                player = input[0] - '0';
                break; 
            }

            // player chose to play a random colour
            if (input[0] == '2') {
                srand(static_cast<unsigned int>(time(nullptr))); 
                player = rand() % 2;
                break;        
            }
        }  
    }

    if (player == WHITE) std::cout << "You are white" << std::endl;
    else std::cout << "You are black" << std::endl;
    return player;
}

void GameState::visualise() {
    visBoard(this->board->pos, this->userColour);
}

void GameState::userMoves() {
    std::string input;
    pieceMove userMove;
    
    while (true) {
        std::cout << "Your next move: " << std::endl;
        std::cin >> input;

        if (input.compare("quit") == 0) { 
            this->status = QUIT;
            return;
        }

        if (pieceMove::string2move(input, &userMove) && 
            this->board->check_move(userMove)) {
                if (this->userColour == WHITE) this->history.push_back("White " + input);    
                else this->history.push_back("Black " + input);

                Board* newBoard;
                newBoard = this->board->make_move(userMove, true);
                delete this->board;
                this->board = newBoard;
                break;
        }

        std::cout << "bad input" << std::endl;
    }

    this->usersTurn = false;
    status_check(); // new board
}

void GameState::AIMoves() {
    pieceMove AIMove = getOptimalMove(this->board, !this->userColour);
    std::string srcCol(1, 'a' + AIMove.srcCol), destCol(1, 'a' + AIMove.destCol);
    std::string srcRow(1, '1' + (7-AIMove.srcRow)), destRow(1, '1' + (7-AIMove.destRow));
    
    if (!(this->userColour) == WHITE)
        this->history.push_back("White " + srcCol + srcRow + destCol + destRow);    
    else
        this->history.push_back("Black " + srcCol + srcRow + destCol + destRow);

    Board* newBoard;
    newBoard = this->board->make_move(AIMove, true);
    delete this->board;
    this->board = newBoard;

    this->usersTurn = true;
    status_check(); // new board
}

void GameState::printHistory() {
    std::cout << "\033[2J\033[1;1H"; // clears the screen
    for (std::vector<std::string>::iterator it = history.begin(); it != history.end(); it++) {
        std::cout << *it << std::endl;
    }
}

// it will checked the status of the game
// after the AI/user played the move
void GameState::status_check() {
    // new board
    int newStatus = this->board->gameOver();    
    
    if (newStatus != CONTINUE) {
        if (newStatus == LOSE) {
            if (this->board->turn == WHITE) history.push_back("Black wins");
            else this->history.push_back("White wins");
        } else if (newStatus == STALEMATE) {
            this->history.push_back("Stalemate");
        }
    }

    this->status = newStatus;
} 

// closes the previous game's window
// initialises SDL
// loads the media into memory
// returns a new board with default setup
Board* init_main(bool colour) { 
    if (SDL_WasInit(SDL_INIT_EVERYTHING)) close_visualise();
    if (!init_SDL()) {
        std::cout << "Failed to initialize SDL" << std::endl;
        return NULL;
    }

    if (!loadMedia(colour)) {
        std::cout << "Failed to load media" << std::endl;
        return NULL;
    }

    return new Board();
}