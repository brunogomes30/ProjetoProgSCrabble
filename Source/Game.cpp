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
	int colors[4] = { BLUE, RED, GREEN, MAGENTA };
	string name;
	//getline(cin, name); //Used to prevent a bug
	for (int i = 1; i <= numPlayers; i++) {
		setconsolecolor(colors[i - 1], BLACK);
		cout << "Name of player " << i << ": ";
		
		getline(cin, name);
		Player newPlayer = Player(name, colors[i - 1]);
		for (int i = 0;i < 7;i++)
			//newPlayer.letters.push_back('v');
			newPlayer.addLetter(gamePool.removeRandomLetter());
		players.push_back(newPlayer);
	}
	setconsolecolor(WHITE, BLACK);
	this->players = players;
}


void Game::showPlayersInfo() {
	cout << "Players information: " << endl;
	for (Player player : players) {
		setconsolecolor(player.getColor(), BLACK);
		cout << player.getName();
		setconsolecolor(WHITE, BLACK);
		cout << "'s letters" << ": ";
		setconsolecolor(player.getColor(), BLACK);
		for (char c : player.getLetters()) {
			cout << c << " ";
		}
		setconsolecolor(WHITE, BLACK);
		cout << endl;
		
		cout << "Points: ";
		setconsolecolor(player.getColor(), BLACK);
		cout << player.getPoints() << endl << endl;
		setconsolecolor(WHITE, BLACK);
	}
	//cout << "Pool size: " << gamePool.getAllLetters().size() << endl;
}

void Game::showBoardLabels() {
	setconsolecolor(RED, BLACK);
	cout << "Red - Tile is filled";
	setconsolecolor(WHITE, BLACK);
	cout << endl;
	setconsolecolor(BLUE, BLACK);
	cout << "Blue - Tile is available to play";
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

	if (addRandomLetterToPlayer()) {
		gamePool.addChar(c);
	}

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
	if (addRandomLetterToPlayer()){
		gamePool.addChar(c1);
	}

	if(addRandomLetterToPlayer()){
		gamePool.addChar(c2);
	}
	return true;
}

void Game::removeLetterFromPlayer(char c) {
	int index = players[currentPlayer].getLetterIndex(c);
	if (index != -1)
		players[currentPlayer].removeLetter(index);
}

bool Game::addRandomLetterToPlayer() {
	if (gamePool.canRemoveLetter()) players[currentPlayer].addLetter(gamePool.removeRandomLetter());
	return gamePool.canRemoveLetter();
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
	//Bubble sort (Doesn't need a good algorithm to sort the scores) 
	bool flag = true;
	while (flag) {
		flag = false;
		for (size_t i = 0;i < players.size() - 1;i++) {
			if (players[i].getPoints() < players[i + 1].getPoints()) {
				
				Player p1 = players[i];
				players[i] = players[i + 1];
				players[i + 1] = p1;
				flag = true;
			}
		}
	}

	//Print the scores
	cout << "Points:\n";
	for (size_t i = 1; i <= players.size(); i++) {
		cout << i << " - " << players[i - 1].getName() << " with " << players[i - 1].getPoints() << " points." << endl;
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
			bool canPlay = checkIfHasAvailableMove(players[currentPlayer]);
			changeCanPlay();

			//Print information
			clear();
			showPlayersInfo();
			board.printBoard();
			showBoardLabels();
			if (checkEndCondition()) {
				endGame();
				break;
			}

			//Input 
			cout << endl;
			setconsolecolor(players[currentPlayer].getColor(), BLACK);
			cout << players[currentPlayer].getName();
			setconsolecolor(WHITE, BLACK);
			cout << "'s turn to play." << endl;

			bool validInput;
			string position;
			if (canPlay) {
				//Has a letter to play
				do {
					if (playNum == 1) cout << "Position to play: ";
					else cout << "Second position to play: ";
					cin >> position;
					clearCin();
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
			else if(playNum == 1 && gamePool.getAllLetters().size() != 0) {
				//Didn't play a letter, and can't play any
				while(true) {
					bool switch2Letters = gamePool.getAllLetters().size() > 1;
					
					if (switch2Letters) cout << "Choose which letters to switch(ex: 'C A'): ";
					else cout << "Choose which letter to switch(ex : 'C'):";
					
					char c1, c2;
					cin >> c1;
					if (switch2Letters) cin >> c2;
					clearCin();

					if (switch2Letters && !switchLettersFromPlayer(c1, c2))
						cout << "Can't switch letters '" << c1 << "' and '" << c2 << "'." << endl;
					else if(!switch2Letters && switchLetterFromPlayer(c1))
						cout << "Can't switch letter '" << c1 << "'. " << endl;
					else break;
				}
				//playNum = 1;
				break;
			}
			else //Skip turn
				break;
		} while (playNum <= 2);
		for (int i = 1;i < playNum;i++) // adds the same amount for letters that were played
			addRandomLetterToPlayer();
		currentPlayer = (currentPlayer + 1) % numPlayers;
	}
}
