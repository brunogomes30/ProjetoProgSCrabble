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
			bool readBoardFromFile(string path);
			void printBoard();
			Board();
			Board(string path);
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
			map<string, Word> words;
			map<int, Letter> lettersMap;
			int sizeY;
			int sizeX;
			void reset_board(int sizeY, int sizeX);
			void fillMaps();
			/*
			 *	Returns true if successful
			 */
			bool insertWord(Word word);

};

#endif