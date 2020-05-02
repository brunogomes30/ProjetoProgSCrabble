#include "Game.h"

#include "Colors.h"
#include "common.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

Game::Game(string pathToBoard,int numPlayers) {
	this->board = Board(pathToBoard);
	this->numPlayers = numPlayers;
}

void Game::askForPlayers() {
	vector<Player> players;
	string name;
	getline(cin, name); //Used to prevent a bug
	for (int i = 1; i <= numPlayers; i++) {
		cout << "Name of player " << i << ": ";
		
		getline(cin, name);
		Player newPlayer = Player(name);
		for (int i = 0;i < 7;i++)
			newPlayer.letters.push_back(gamePool.removeRandomLetter());
		players.push_back(newPlayer);
	}
	this->players = players;
}

void Game::showPlayersInfo() {
	cout << "Players information: " << endl;
	for (Player player : players) {
		cout << player.name << "'s letters" << ": ";
		setconsolecolor(BLUE, BLACK);
		for (char c : player.letters) {
			cout << c << " ";
		}
		setconsolecolor(WHITE, BLACK);
		cout << endl;
		
		cout << "Points: ";
		setconsolecolor(BLUE, BLACK);
		cout << player.points << endl << endl;
		setconsolecolor(WHITE, BLACK);
	}
}

bool Game::playTile(int y,int x) {
	vector<char> lettersFromPlayer = players[currentPlayer].letters;

	int indexOfChar = -1;
	for (int i = 0;i < (int) lettersFromPlayer.size();i++) {
		if (board.field[y][x]->value == lettersFromPlayer[i]) {
			indexOfChar = i;
			break;
		}
	}
	if (indexOfChar == -1) {
		return false;
	}
	bool isSuccess = board.fillTile(y, x, players[currentPlayer]);
	if (!isSuccess)
		return false;

	players[currentPlayer].letters.erase(players[currentPlayer].letters.begin() + indexOfChar);

	players[currentPlayer].letters.insert(players[currentPlayer].letters.begin() + indexOfChar, gamePool.removeRandomLetter());

	return true;
}

void Game::fillPool() {
	gamePool = Pool();
	for (map<string, Word>::iterator it = board.words.begin();it != board.words.end(); it++) {
		gamePool.addWord(it->second);
	}
}


bool Game::checkIfHasAvailableMove(Player player) {
	vector<char> lettersAvailable;
	for (int y = 0;y < board.sizeY;y++) {
		for (int x = 0;x < board.sizeX;x++) {
			if (board.field[y][x]->isAvailable && !board.field[y][x]->isFilled) {
				lettersAvailable.push_back(board.field[y][x]->value);
			}
		}
	}

	for (char c1 : lettersAvailable) for (char c2 : player.letters) {
		if (c1 == c2) return true;
	}
	return false;
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
			showPlayersInfo();
			board.printBoard();
			cout << players[currentPlayer].name << "'s turn to play." << endl;
			if (canPlay) {
				if (playNum == 1) cout << "Position to play: ";
				else cout << "Second position to play: ";
				string position;
				cin >> position;
				//TODO :: Check if position is valid
				int y = position.at(0) - 'A';
				int x = position.at(1) - 'a';
				playTile(y, x);
				canPlay = checkIfHasAvailableMove(players[currentPlayer]);
				playNum++;
			}
			else {
				cout << "Choose which letters to switch(ex: 'C A' ):";
				char c1, c2;
				cin >> c1 >> c2;
			}
		} while (playNum <= 2);
		currentPlayer = (currentPlayer + 1) % numPlayers;
		
	}
}
