#include "Board.h"
#include "Word.h"
#include "Player.h"
#include "Colors.h"
#include "common.h"
#include <Windows.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;


Board::Board() {
	readBoardFromFile("board1.txt");
}

Board::Board(string path) {
	readBoardFromFile(path);
}

void Board::fillMaps() {
	for (map<string, Word>::iterator it = words.begin();it != words.end(); it++) {
		vector<Letter*> letters = it->second.letters;
		for (int i = 0;i < letters.size();i++) {
			int y = it->second.yPos;
			int x = it->second.xPos;
			if (it->second.isHorizontal) x += i;
			else y += i;
			it->second.letters[i] = &lettersMap[y * sizeY + x];
		}
	}
}


void Board::printBoard() {
	setconsolecolor(BLACK, DARKGRAY);
	cout << "   ";
	for (int x = 0; x < sizeX;x++)

		cout << " " <<char('a' + x) << " ";
	cout << "   ";
	setconsolecolor(WHITE, BLACK);
	cout << endl;
	
	for (int y = 0; y < sizeY; y++) {
		setconsolecolor(BLACK, DARKGRAY);
		cout << " " << char('A' + y) << " ";
		setconsolecolor(WHITE, BLACK);

		for (int x = 0; x < sizeX; x++) {
			if (field[y][x]->value == ' ')
				setconsolecolor(BLACK, BROWN);
			else if (field[y][x]->isFilled)
				setconsolecolor(RED, BROWN);
			else if (field[y][x]->isAvailable)
				setconsolecolor(GREEN, BROWN);
			else
				setconsolecolor(BLACK, BROWN);
			cout << " " << field[y][x]->value << " ";
		}
		setconsolecolor(BLACK, DARKGRAY);
		cout << "   ";
		cout << "\n";
		
		
	}
	setconsolecolor(BLACK, DARKGRAY);
	for (int x = 0; x < sizeX + 2;x++)
		cout << "   ";
	setconsolecolor(WHITE, BLACK);
	cout << endl;
}

void Board::reset_board(int sizeY, int sizeX) {
	this->sizeY = sizeY;
	this->sizeX = sizeX;
	vector<vector<Letter*>> field;
	for (int y = 0; y < sizeY; y++) {
		vector<Letter*> vector;
		for (int x = 0; x < sizeX; x++) {
			lettersMap[y*sizeY + x] = Letter(' ', y, x);
			vector.push_back(&lettersMap[y*sizeY + x]);
		}
		field.push_back(vector);
	}
	this->field = field;
}

bool Board::insertWord(Word word) {
	words[word.value] = word;
	for (int i = 0;i < word.value.length(); i++) {
		int y = word.yPos;
		int x = word.xPos;
		if (word.isHorizontal) x += i;
		else y += i;
		
		//Verifica se está vazio
		if (field[y][x]->value == ' ') {
			lettersMap[y*sizeY + x] = Letter(word.value.at(i), y, x);
			field[y][x] = &lettersMap[y*sizeY + x];
			words[word.value] = word;
			field[y][x]->includedIn.push_back(&words[word.value]);
		}
		else if (field[y][x]->value == word.value.at(i)) 
			field[y][x]->includedIn.push_back(&words[word.value]);
		else 
			return false;
		words[word.value].letters[i] = &lettersMap[y*sizeY + x];
	}
	field[word.yPos][word.xPos]->isAvailable = true;
	return true;
}

bool Board::readBoardFromFile(string path) {
	ifstream boardFile;
	stringstream ss;
	string line, dummy;

	boardFile.open("board1.txt", ios::in);
	//Read size
	getline(boardFile, line);
	ss = stringstream(line);
	ss >> sizeY >> dummy >> sizeX;
	reset_board(sizeY, sizeX);
	//Read the board
	do {
		getline(boardFile, line);
		ss = stringstream(line);
		string positions, direction, wordValue;
		ss >> positions >> direction >> wordValue;
		int yPos = positions.at(0) - 'A';
		int xPos = positions.at(1) - 'a';

		Word newWord = Word(wordValue, yPos, xPos, direction == "H");
		insertWord(newWord);
	} while (!boardFile.eof());
	fillMaps();
	return true;
}

bool Board::fillTile(int y, int x, Player &player) {
	//Check if positions are valid
	if (!(0 <= y && y < sizeY && 0 <= x && x < sizeX))
		return false;
	//Check if it's available
	if (!field[y][x]->isAvailable) 
		return false;

	field[y][x]->isAvailable = false;
	field[y][x]->isFilled = true;

	for (Word* word : field[y][x]->includedIn) {
		word->lettersRemaining--;
		//Finished word
		if (word->lettersRemaining == 0) {
			player.points++;
		} else if (word->letters[word->indexToPlay]->equals(field[y][x])) {
			word->calculateIndexToPlay();
			bool isAvailable= true;
			for (Word* word2 : word->letters[word->indexToPlay]->includedIn) {
				if (!word->letters[word->indexToPlay]->equals(word2->letters[word2->indexToPlay])) {
					isAvailable = false;
					break;
				}
			}
			word->letters[word->indexToPlay]->isAvailable = isAvailable;
		}
	}
	return true;
}

