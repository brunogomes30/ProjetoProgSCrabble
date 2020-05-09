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
public:		int sizeY;
			int sizeX;
			vector<vector<Letter*>> field;
			map<string, Word> words;
			map<int, Letter> lettersMap;
			
			bool readBoardFromFile(string path);
			void printBoard();
			Board();
			Board(string path);
			bool fillTile(int y, int x, Player &player);

private:	void reset_board(int sizeY, int sizeX);
			void fillMaps();
			/*
			 *	Returns true if successful
			 */
			bool insertWord(Word word);

};

#endif