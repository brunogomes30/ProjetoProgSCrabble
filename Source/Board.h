#ifndef BOARD_GUARD
#define BOARD_GUARD

#include "Word.h"
#include "Letter.h"
#include "Player.h"
#include<string>
#include<vector>
#include<iostream>
#include<map>
using namespace std;

class Board {
public:		

			/* 
			 * Reads board from file, initializes the board
			 */
			bool readBoardFromFile(string path);
			
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
			Board(string path);
			
			/* 
			 * Function to call to play a tile, returns false if it can't be played
			 */
			bool fillTile(int y, int x, Player &player);
			
			//getters and setters
			int getSizeY();
			void setSizeY(int sizeY);
			int getSizeX();
			void setSizeX(int sizeX);
			vector<vector<Letter*>> getField();
			void setField(vector<vector<Letter*>> field);

private:	
			vector<vector<Letter*>> field;
			map<int, Word> words;
			map<int, Letter> lettersMap;
			int sizeY;
			int sizeX;

			/*
			 * resets the board, filling all the tiles with empty letters
			 */
			void reset_board(int sizeY, int sizeX);

			/*
			 * Updates the maps
			 */
			void fillMaps();
			/*
			 *	Returns true if successful
			 */
			bool insertWord(Word word);

};

#endif