#ifndef GAME_GUARD
#define GAME_GUARD

#include "Board.h"
#include "Player.h"
#include "Pool.h"
#include<string>
#include<vector>
#include<iostream>

class Game {
public:	
		Game(std::string pathToBoard, int numPlayers);

		/*
		 * Prints the labels of the colors
		 */
		void showBoardLabels();

		/*
		 * The game's main loop
		 */
		void playGame();

		

private:
		
		int numPlayers;
		bool isGameFinished;
		Pool gamePool;
		Board board;
		std::vector<Player> players;
		int currentPlayer;
	

		/*
		 * currentPlayer plays a tile in the position (y, x)
		 */
		bool playTile(int y, int x);

		/*
		 * Asks for the players name, and initializes them
		 */

		void askForPlayers();

		/*
		 * Prints the players letters and points
		 */
		void showPlayersInfo();

		/*
		 * Checks if players has an available move
		 */
		bool checkIfHasAvailableMove(Player player);

		/*
		 * Checks if players has the letter c
		 * @param c
		 */
		bool checkIfPlayerHasLetter(char c);

		/*
		 * Fills the game pool 
		 */
		void fillPool();

		/*
		 * Removes the letters from the player, and gives 2 random letters from the pool
		 * @param c1
		 * @param c2
		 */
		bool switchLettersFromPlayer(char c1, char c2);

		/*
		 * Remove the letter from the player, and gives 1 random letter from the pool
		 * @param c
		 */
		bool switchLetterFromPlayer(char c);

		/*
		 * Verifies  if the games has finished
		 */
		bool checkEndCondition();

		/*
		 * Removes a letter from the currentPlayer
		 * @param c
		 */
		void removeLetterFromPlayer(char c);

		/*
		 * Adds a random letter to the currentPlayer, returns true if possible
		 */
		bool addRandomLetterToPlayer();

		/*
		 * Sets which tiles can be played by the currentPlayer
		 */
		void changeCanPlay();

		/*
		 * Ends the game and prints the score of the players 
		 */
		void endGame();

		/*
		 * Returns a vector of char that has the letters available to play
		 */
		std::vector<char> getLettersAvailable();
};
#endif
