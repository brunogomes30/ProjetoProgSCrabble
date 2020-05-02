#include "Board.h"
#include "Game.h"
#include "common.h"
#include <iostream>


/*
 * Play game
 */
void playGame();

/*
 * Board Builder
 */
void buildBoard();

int main()
{

	//The user chooses if he wants to create a board or play a game
	
	cout << "Select Option:" << endl;
	cout << "\t1 - Play a game" << endl;
	cout << "\t2 - Create a board" << endl;
	cout << "Option -> ";
	int option;
	do{
	cin >> option;
	if (option == 1) {
		playGame();
	}
	else if (option == 2) {
		buildBoard();
	}
	} while (option != 1 && option != 2);
	
	Board board = Board("board1.txt");
	board.printBoard();
	
}

void playGame() {
	clear();
	cout << "Ficheiro já escolhido \n";
	int numPlayers;
	do {
		cout << "Número de jogadores pretendido (2 a 4) ->";
		cin >> numPlayers;
	} while ( 2 < numPlayers || numPlayers > 4);

	string boardPath = "board1.txt";
	Game game = Game(boardPath, numPlayers);
	clear();
	game.playGame();
	
}

void buildBoard() {

}
