#ifndef GAME_GUARD
#define GAME_GUARD

#include "Board.h"
#include "Player.h"
#include "Pool.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Game {
public:	int numPlayers;
		bool isGameFinished;
		Pool gamePool;
		Board board;
		vector<Player> players;
		int currentPlayer;
		Game(string pathToBoard, int numPlayers);
		void showBoardLabels();
		void playGame();
		bool playTile(int y, int x);

private:void askForPlayers();
		void showPlayersInfo();
		bool checkIfHasAvailableMove(Player player);
		bool checkIfPlayerHasLetter(char c);
		void fillPool();
		bool switchLettersFromPlayer(char c1, char c2);
		bool switchLetterFromPlayer(char c);
		bool checkEndCondition();
		void removeLetterFromPlayer(char c);
		void addRandomLetterToPlayer();
		void changeCanPlay();
		void endGame();
		vector<char> getLettersAvailable();
};
#endif