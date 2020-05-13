#include "Board.h"
#include "Game.h"
#include "common.h"
#include <iostream>
#include <filesystem>


/*
 * Play game
 */
void playGame();

/*
 * Board Builder
 */
void buildBoard();
string chooseBoard();
string getFileFromPath(string path);
int main()
{
	cout << "Scrabble junior game for 2, 3 or 4 players." << endl;
	int numPlayers;
	do {
		cout << "Number of players (2 to 4) -> ";
		cin >> numPlayers;
		clearCin();
	} while (2 > numPlayers || numPlayers > 4);

	string boardPath = chooseBoard();
	Game game = Game(boardPath, numPlayers);
	clear();
	game.playGame();
	
}


namespace fs = std::experimental::filesystem;

string getFileFromPath(string path) {
	int index = 0;
	for (int i = path.size() - 1; i >= 0; i--) {
		if (path.at(i) == '\\') {
			index = i;
			break;
		}
	}
	return path.substr(index + 1);
}

string chooseBoard() {
	string currentPath = fs::current_path().string();
	string path = currentPath + "\\Boards";

	cout << "Available Boards:" << endl;
	vector<string> availableFiles;
	int i = 0;
	for (const auto & entry : fs::directory_iterator(path)) {
		availableFiles.push_back(getFileFromPath(entry.path().string()));
		std::cout << "\t" << ++i << " - " << getFileFromPath(entry.path().string()) << endl;
	}
	cout << endl;
	int n;
	do {
		cout << "Choose a file(By number)\nNumber-> ";
		cin >> n;
		clearCin();
	} while (n < 1 && n > availableFiles.size());

	string boardPath = currentPath + "\\Boards\\" + availableFiles[n - 1];
	Board board = Board(boardPath);
	clear();
	cout << "Board preview:" << endl;
	board.printBoard();
	string answer;
	do {
		cout << "Select board?(y or n)" << endl;
		cout << "Answer -> ";
		cin >> answer;
		clearCin();

		if (answer == "y" || answer == "Y")
			return boardPath;
		else if (answer == "n" || answer == "N")
			return chooseBoard();

	} while (answer != "y" || answer != "Y" || answer != "n" || answer != "N");
}

