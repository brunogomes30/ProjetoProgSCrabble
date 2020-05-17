#ifndef BOARD_GUARD
#define BOARD_GUARD

#include "Word.h"
#include "Letter.h"
#include "Player.h"
#include<string>
#include<vector>
#include<iostream>
#include<map>


class Board {
public:		

			/*
			 * Reads board from file, initializes the board
			 */
			bool readBoardFromFile(std::string path);

			/*
			* Reads board from file, initializes the board, and checks if can be played by the number of players provided
			* @param path
			* @param numOfPlayers
			*/
			bool readBoardFromFile(std::string path, int numOfPlayers);
			
			/*
			 * Prints board with all the information(If tile can be play, if it's filled, etc...)
			 */
			void printBoard();
			
			/*
		     * Default constructor, does nothing 
			 */
			Board();
			
			/*
			 * Constructor that calls readBoardFromFile
			 */
			Board(std::string path);
			
			/* 
			 * Function to call to play a tile, returns false if it can't be played
			 */
			bool fillTile(int y, int x, Player &player);

			/*
			 *	Returns true if successful
			 */
			bool insertWord(Word word);
			
			bool removeWord(Word word);

			/*
			 * Returns true if board is valid
			 */
			bool checksIsValid();

			bool operator ==(Board a);

			/*
			 * resets the board, filling all the tiles with empty letters
			 */
			void reset_board(int sizeY, int sizeX);

			/*
			 * Returns a word based on its position and direction
			 */
			Word findWord(int yPos, int xPos, bool isHorizontal);

			/*
			 * Returns all words
			 */
			std::vector<Word> getAllWords();

			//getters and setters
			int getSizeY();
			void setSizeY(int sizeY);
			int getSizeX();
			void setSizeX(int sizeX);
			std::vector<std::vector<Letter*>> getField();
			void setField(std::vector<std::vector<Letter*>> field);

private:	
			std::vector<std::vector<Letter*>> field;
			std::map<int, Word> words;
			std::map<int, Letter> lettersMap;
			int sizeY;
			int sizeX;

			

			/*
			 * Updates the maps
			 */
			void fillMaps();

			

};

#endif