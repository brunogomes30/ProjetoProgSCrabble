#include "Board.h"
#include "Game.h"
#include "common.h"
#include <iostream>
#include <filesystem>
#include <sstream>
using namespace std;
/*
 * Play game
 */
void playGame();

/*
 * Board Builder
 */
void buildBoard();
string chooseBoard(int numOfPlayers);
string getFileFromPath(string path);
int main() {
	cout << "Scrabble junior game for 2, 3 or 4 players." << endl;
	int numPlayers;
	do {
		cout << "Number of players (2 to 4) -> ";
		cin >> numPlayers;
		clearCin();
	} while (2 > numPlayers || numPlayers > 4);

	string boardPath = chooseBoard(numPlayers);
	if (boardPath != "") {
		Game game = Game(boardPath, numPlayers);
		clear();
		game.playGame();
	}	
}


namespace fs = std::experimental::filesystem;

string getFileFromPath(string path) {
	int index = path.find_last_of('\\');
	return path.substr(index + 1);
}

string chooseBoard(int numOfPlayers) {
	clear();
	string currentPath = fs::current_path().string(); 
	string path = currentPath + "\\Boards";		      

	//Prints all available boards
	cout << "Available Boards with at least " << numOfPlayers * 7 << " letters :" << endl;
	vector<string> availableFiles;
	int i = 1;
	for (const auto & entry : fs::directory_iterator(path)) {
		string filePath = entry.path().string();

		// Checks if file is in a correct format for the board
		if (Board().readBoardFromFile(filePath, numOfPlayers)) {
			availableFiles.push_back(getFileFromPath(filePath));
			std::cout << "\t" << i++ << " - " << getFileFromPath(filePath) << endl;
		}
	}
	cout << endl;
	
	string answer, boardPath;
	int n = -1;
	do {
		cout << "Choose a file( Insert number or full path) or write 'exit' to stop the program" << endl;
		getline(cin, answer); //Use getline because path can have spaces
		if (answer == "exit") break;
		if (answer.find("\\") == -1) {
			//Input is a number
			stringstream ss = stringstream(answer);
			ss >> n; 
		}
		else {
			//Input is full path, so n should be ignored
			n = -1;
			break;
		}
		
	} while (n < 1 && n > (int) availableFiles.size());
	if (answer == "exit") return "";
	if(n != -1) boardPath = currentPath + "\\Boards\\" + availableFiles[n - 1]; // Answer is a number
	else boardPath = answer;													// Answer is the full path

	Board board = Board(boardPath);
	clear();
	cout << "Board preview:" << endl;
	board.printBoard();
	
	do {
		cout << "Select board?(y or n)" << endl;
		cout << "Answer -> ";
		cin >> answer;
		clearCin();
		//Function must select a valid board
		if (answer == "y" || answer == "Y")
			return boardPath;
		else if (answer == "n" || answer == "N")
			return chooseBoard(numOfPlayers);

	} while (answer != "y" || answer != "Y" || answer != "n" || answer != "N");
	return "";
}

