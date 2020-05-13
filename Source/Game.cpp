#include "Game.h"
#include "Board.h"
#include "Colors.h"
#include "common.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;

Game::Game(string pathToBoard,int numPlayers) {
	this->board = Board(pathToBoard);
	this->numPlayers = numPlayers;
}


void Game::askForPlayers() {
	vector<Player> players;
	string name;
	//getline(cin, name); //Used to prevent a bug
	for (int i = 1; i <= numPlayers; i++) {
		cout << "Name of player " << i << ": ";
		
		getline(cin, name);
		Player newPlayer = Player(name);
		for (int i = 0;i < 7;i++)
			//newPlayer.letters.push_back('v');
			newPlayer.addLetter(gamePool.removeRandomLetter());
		players.push_back(newPlayer);
	}
	this->players = players;
}


void Game::showPlayersInfo() {
	cout << "Players information: " << endl;
	for (Player player : players) {
		cout << player.getName() << "'s letters" << ": ";
		setconsolecolor(LIGHTBLUE, BLACK);
		for (char c : player.getLetters()) {
			cout << c << " ";
		}
		setconsolecolor(WHITE, BLACK);
		cout << endl;
		
		cout << "Points: ";
		setconsolecolor(LIGHTBLUE, BLACK);
		cout << player.getPoints() << endl << endl;
		setconsolecolor(WHITE, BLACK);
	}
	cout << "Pool size: " << gamePool.getAllLetters().size() << endl;
}

void Game::showBoardLabels() {
	setconsolecolor(RED, BLACK);
	cout << "Red - Tile is filled";
	setconsolecolor(WHITE, BLACK);
	cout << endl;
	setconsolecolor(GREEN, BLACK);
	cout << "Green - Tile is available to play";
	setconsolecolor(WHITE, BLACK);
	cout << endl;

}

bool Game::playTile(int y,int x) {
	int indexOfChar = players[currentPlayer].getLetterIndex(board.getField()[y][x]->getValue());
	if (indexOfChar == -1)
		return false;
	bool isSuccess = board.fillTile(y, x, players[currentPlayer]);
	return isSuccess;
}



void Game::fillPool() {
	gamePool = Pool();
	for (int y = 0;y < board.getSizeY();y++) for (int x = 0;x < board.getSizeX();x++) {
		if(board.getField()[y][x]->getValue() != ' ') gamePool.addChar(board.getField()[y][x]->getValue());
	}
	
}

vector<char> Game::getLettersAvailable() {
	vector<char> lettersAvailable;
	for (int y = 0;y < board.getSizeY();y++) {
		for (int x = 0;x < board.getSizeX();x++) {
			if (board.getField()[y][x]->getIsAvailable() && !board.getField()[y][x]->getIsFilled()) {
				lettersAvailable.push_back(board.getField()[y][x]->getValue());
			}
		}
	}
	return lettersAvailable;
}

bool Game::checkIfHasAvailableMove(Player player) {
	vector<char> lettersAvailable = getLettersAvailable();
	

	for (char c1 : lettersAvailable) for (char c2 : player.getLetters()) {
		if (c1 == c2) return true;
	}
	return false;
}

bool Game::switchLetterFromPlayer(char c) {
	int indexOfChar = players[currentPlayer].getLetterIndex(c);
	if (indexOfChar == -1)
		return false;

	players[currentPlayer].replaceLetter(gamePool.removeRandomLetter(), indexOfChar);

	//players[currentPlayer].letters.erase(players[currentPlayer].letters.begin() + indexOfChar);
	//if(gamePool.canRemoveLetter()) players[currentPlayer].letters.insert(players[currentPlayer].letters.begin() + indexOfChar, gamePool.removeRandomLetter());

	return true;
}

bool Game::switchLettersFromPlayer(char c1, char c2) {
	//if (!('A' <= c1 && c1 <= 'Z' && 'A' <= c2 && c2 <= 'Z'))
	//	return false;
	int index1 = players[currentPlayer].getLetterIndex(c1);
	int index2;
	if (c1 == c2)
		index2 = players[currentPlayer].getLetterIndex(c2, 2);
	else
		index2 = players[currentPlayer].getLetterIndex(c2);
	if (index1 == -1 || index2 == -1) 
		return false;
	if (gamePool.canRemoveLetter()){
		players[currentPlayer].replaceLetter(gamePool.removeRandomLetter(), index1);
		gamePool.addChar(c1);
	}

	if(gamePool.canRemoveLetter()){
		players[currentPlayer].replaceLetter(gamePool.removeRandomLetter(), index2);
		gamePool.addChar(c2);
	}
	return true;
}

void Game::removeLetterFromPlayer(char c) {
	int index = players[currentPlayer].getLetterIndex(c);
	if (index != -1)
		players[currentPlayer].removeLetter(index);
}

void Game::addRandomLetterToPlayer() {
	if (gamePool.canRemoveLetter()) players[currentPlayer].addLetter(gamePool.removeRandomLetter());
}
bool Game::checkIfPlayerHasLetter(char c) {
	int indexOfChar = players[currentPlayer].getLetterIndex(c);
	return indexOfChar != -1;
}

bool Game::checkEndCondition() {
	return getLettersAvailable().size() == 0;
}

void Game::changeCanPlay() {
	for (int y = 0;y < board.getSizeY(); y++) for (int x = 0;x < board.getSizeX();x++) {
		if (checkIfPlayerHasLetter(board.getField()[y][x]->getValue())) {
			board.getField()[y][x]->setCanPlay(true);
		} else {
			board.getField()[y][x]->setCanPlay(false);
		}
	}
}

void Game::endGame() {
	/*sort(players.begin(), players.end(),
		[](Player const & a, Player const & b) -> bool
		{ return a.getPoints() < b.getPoints(); });*/
	cout << "Points:\n";
	for (int i = 1; i <= players.size(); i++) {
		cout << i << " - " << players[i - 1].getName() << " - " << players[i - 1].getPoints() << " points.";
	}
	isGameFinished = true;
}


void Game::playGame() {
	clear();
	fillPool();
	askForPlayers();

	isGameFinished = false;
	currentPlayer = 0;
	while (!isGameFinished) {
		int playNum = 1;
		do {
			clear();
			bool canPlay = checkIfHasAvailableMove(players[currentPlayer]);

			changeCanPlay();
			showPlayersInfo();
			board.printBoard();
			showBoardLabels();

			if (checkEndCondition()) {
				endGame();
				break;
			}

			//Input 
			cout << players[currentPlayer].getName() << "'s turn to play." << endl;
			bool validInput;
			string position;
			if (canPlay) {
				//Has a letter to play
				do {
					if (playNum == 1) cout << "Position to play: ";
					else cout << "Second position to play: ";
					cin >> position;
					clearCin();
					//TODO :: Check if position is valid
					validInput = checkPosition(position);
				} while (!validInput);

				int y = position.at(0) - 'A';
				int x = position.at(1) - 'a';
				if (playTile(y, x)) {
					//Play was sucessfull
					playNum++;
					removeLetterFromPlayer(board.getField()[y][x]->getValue());
				}
				//canPlay = checkIfHasAvailableMove(players[currentPlayer]);
			}
			else if(playNum < 2 && gamePool.getAllLetters().size() != 0) {
				//Didn't play a letter, and can't play any
				while(true) {
					if (gamePool.getAllLetters().size() != 1) {
						//Switch 2 letters
						cout << "Choose which letters to switch(ex: 'C A' ):";
						char c1, c2;
						cin >> c1 >> c2;
						clearCin();
						if (!switchLettersFromPlayer(c1, c2))
							cout << "Can't switch letters '" << c1 << "' and '" << c2 << "'." << endl;
						else break;
					} else {
						//Switch 1 letter because pool only has 1 available
						cout << "Choose which letter to switch(ex : 'C'):";
						char c;
						cin >> c;
						clearCin();
						if (checkIfPlayerHasLetter(c)) {
							players[currentPlayer].replaceLetter(gamePool.removeRandomLetter(), players[currentPlayer].getLetterIndex(c));
						}
						else break;
					}
				}
				break;
			}
			else 
				//Skip turn
				break;

		} while (playNum <= 2);
		for (int i = 1;i < playNum;i++) // adds the same amount for letters that were played
			addRandomLetterToPlayer();
		currentPlayer = (currentPlayer + 1) % numPlayers;
	}
}
