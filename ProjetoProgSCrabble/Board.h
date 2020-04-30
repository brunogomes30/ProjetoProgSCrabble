#ifndef BOARD_GUARD
#define BOARD_GUARD

#include "Word.h"
#include "Letter.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Board {


public:		int sizeY;
			int sizeX;
			vector<vector<Letter>> field;

			
			bool readBoardFromFile(string path);
			void printBoard();

private:	void reset_board(int sizeY, int sizeX);
			
			/*
			 *	Returns true if successful
			 */
			bool insertWord(Word word);

};

#endif