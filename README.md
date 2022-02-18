# Chess AI

![alt text](https://github.com/viethan/Chess-AI/blob/main/img/readmeImg/chess!!!.png?raw=true)

* Written in C++, using SDL for visualisation

## GameState

* When a game starts, a GameState object is initialised, and is in scope for the duration of the match
* The GameState object tracks the history of the game, whose turn it is and contains a Board*
* It also allows the user to pick his side, and makes sure to check if the game has reached a conclusion
* Using defensive programming principles, a new Board* is returned whenever we Board::make_move()

![alt text](https://github.com/viethan/Chess-AI/blob/main/img/readmeImg/gamestate.png?raw=true)

## Board

* Board constructor will create an object which contains the initial default layout of the game
* It will generate a new Board* when instructed to make_move(), and will update its flags
* Flags such as the turn, if castling or en passant are available 
* Unless instructed otherwise, the Board constructor will also generate all possible moves available to make
* When a user inputs a move, it will check if it's in the vector
* Moves generated are also carefully filtered in order to align with the rules of the game

![alt text](https://github.com/viethan/Chess-AI/blob/main/img/readmeImg/board.png?raw=true)

## Minimax

* Minimax implementation with Alpha-Beta pruning
* Uses a simplied evaluation function, which provides a score based on positions and chess pieces present ([link](https://www.chessprogramming.org/Simplified_Evaluation_Function))
* The game tree finishes recursing when depth reaches zero, or it detects that no moves are available - stalemate or loss
* The depth can easily be changed in the header file, allowing for better moves in exchange for mote time spent on the computation

![alt text](https://github.com/viethan/Chess-AI/blob/main/img/readmeImg/minimax.png?raw=true)

## Future Improvements

* Sort the moves for better pruning
* Implement openings and endgame tables
* Improve the eval function
* Differentiate moves with the same value (especial those +/- inf)
* Option to resign to AI
* Multiplayer
* Paramaterized piece promotion (currently both sides promote to queen automatically)
