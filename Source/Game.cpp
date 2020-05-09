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
			newPlayer.letters.push_back(gamePool.removeRandomLetter());
		players.push_back(newPlayer);
	}
	this->players = players;
}


void Game::showPlayersInfo() {
	cout << "Players information: " << endl;
	for (Player player : players) {
		cout << player.name << "'s letters" << ": ";
		setconsolecolor(LIGHTBLUE, BLACK);
		for (char c : player.letters) {
			cout << c << " ";
		}
		setconsolecolor(WHITE, BLACK);
		cout << endl;
		
		cout << "Points: ";
		setconsolecolor(LIGHTBLUE, BLACK);
		cout << player.points << endl << endl;
		setconsolecolor(WHITE, BLACK);
	}
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
	int indexOfChar = players[currentPlayer].getLetterIndex(board.field[y][x]->value);
	if (indexOfChar == -1)
		return false;
	bool isSuccess = board.fillTile(y, x, players[currentPlayer]);
	return isSuccess;
}



void Game::fillPool() {
	gamePool = Pool();
	for (int y = 0;y < board.sizeY;y++) for (int x = 0;x < board.sizeX;x++) {
		if(board.field[y][x]->value != ' ') gamePool.addChar(board.field[y][x]->value);
	}
	/*
	for (map<string, Word>::iterator it = board.words.begin();it != board.words.end(); it++) {
		gamePool.addWord(it->second);
	}
	*/
}

vector<char> Game::getLettersAvailable() {
	vector<char> lettersAvailable;
	for (int y = 0;y < board.sizeY;y++) {
		for (int x = 0;x < board.sizeX;x++) {
			if (board.field[y][x]->isAvailable && !board.field[y][x]->isFilled) {
				lettersAvailable.push_back(board.field[y][x]->value);
			}
		}
	}
	return lettersAvailable;
}

bool Game::checkIfHasAvailableMove(Player player) {
	vector<char> lettersAvailable = getLettersAvailable();
	

	for (char c1 : lettersAvailable) for (char c2 : player.letters) {
		if (c1 == c2) return true;
	}
	return false;
}

bool Game::switchLetterFromPlayer(char c) {
	int indexOfChar = players[currentPlayer].getLetterIndex(c);
	if (indexOfChar == -1)
		return false;

	players[currentPlayer].letters.erase(players[currentPlayer].letters.begin() + indexOfChar);
	players[currentPlayer].letters.insert(players[currentPlayer].letters.begin() + indexOfChar, gamePool.removeRandomLetter());

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
	
	players[currentPlayer].letters.erase(players[currentPlayer].letters.begin() + index1);
	players[currentPlayer].letters.insert(players[currentPlayer].letters.begin() + index1, gamePool.removeRandomLetter());

	players[currentPlayer].letters.erase(players[currentPlayer].letters.begin() + index2);
	players[currentPlayer].letters.insert(players[currentPlayer].letters.begin() + index2, gamePool.removeRandomLetter());
	return true;
}

void Game::removeLetterFromPlayer(char c) {
	int index = players[currentPlayer].getLetterIndex(c);
	if (index != -1)
		players[currentPlayer].letters.erase(players[currentPlayer].letters.begin() + index);
}

void Game::addRandomLetterToPlayer() {
	players[currentPlayer].letters.push_back(gamePool.removeRandomLetter());
}
bool Game::checkIfPlayerHasLetter(char c) {
	int indexOfChar = players[currentPlayer].getLetterIndex(c);
	return indexOfChar != -1;
}

bool Game::checkEndCondition() {
	return getLettersAvailable().size() == 0;
}

void Game::changeCanPlay() {
	for (int y = 0;y < board.sizeY; y++) for (int x = 0;x < board.sizeX;x++) {
		if (checkIfPlayerHasLetter(board.field[y][x]->value)) {
			board.field[y][x]->canPlay = true;
		} else {
			board.field[y][x]->canPlay = false;
		}
	}
}

void Game::endGame() {
	sort(players.begin(), players.end(),
		[](Player const & a, Player const & b) -> bool
		{ return a.points < b.points; });
	cout << "Points:\n";
	for (int i = 1; i <= players.size(); i++) {
		cout << i << " - " << players[i - 1].name << " - " << players[i - 1].points << " points.";
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
		bool canPlay = checkIfHasAvailableMove(players[currentPlayer]);
		int playNum = 1;
		do {
			clear();
			
			changeCanPlay();
			showPlayersInfo();
			board.printBoard();
			showBoardLabels();

			if (checkEndCondition()) {
				endGame();
				break;
			}
			cout << players[currentPlayer].name << "'s turn to play." << endl;

			bool validInput;
			string position;
			if (canPlay) {
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
					playNum++;
					removeLetterFromPlayer(board.field[y][x]->value);
				}
				canPlay = checkIfHasAvailableMove(players[currentPlayer]);
			}
			else {
				while(true) {
					cout << "Choose which letters to switch(ex: 'C A' ):";
					char c1, c2;
					cin >> c1 >> c2;
					if (!switchLettersFromPlayer(c1, c2)) 
						cout << "Can't switch letters '" << c1 << "' and '" << c2 << "'." << endl;
				}
				playNum++;
			}
		} while (playNum <= 2);
		for (int i = 1;i < playNum;i++) // adds the same amount for letters that were played
			addRandomLetterToPlayer();
		currentPlayer = (currentPlayer + 1) % numPlayers;
		
	}
}
