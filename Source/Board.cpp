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
//Teste
using namespace std;


Board::Board() {
	//readBoardFromFile("board1.txt");
}

Board::Board(string path) {
	readBoardFromFile(path);
}

void Board::fillMaps() {
	for (map<int, Word>::iterator it = words.begin();it != words.end(); it++) {
		vector<Letter*> letters = it->second.letters;
		for (size_t i = 0;i < letters.size();i++) {
			int y = it->second.getYPos();
			int x = it->second.getXPos();
			if (it->second.getIsHorizontal()) x += i;
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
			if (field[y][x]->getValue() == ' ')
				setconsolecolor(BLACK, BROWN);
			else if (field[y][x]->getIsFilled())
				setconsolecolor(RED, BROWN);
			else if (field[y][x]->getIsAvailable() && field[y][x]->getCanPlay())
				setconsolecolor(GREEN, BROWN);
			else
				setconsolecolor(BLACK, BROWN);
			
			cout << " " << field[y][x]->getValue() << " ";

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
	words[word.getYPos() * sizeY + word.getXPos()] = word;
	for (size_t i = 0;i < word.getValue().length(); i++) {
		int y = word.getYPos();
		int x = word.getXPos();
		if (word.getIsHorizontal()) x += i;
		else y += i;
		
		
		if (field[y][x]->getValue() == ' ') {
			//If it's empty, create a new Letter
			lettersMap[y*sizeY + x] = Letter(word.getValue().at(i), y, x);
			field[y][x] = &lettersMap[y*sizeY + x];
			words[word.getYPos() * sizeY + word.getXPos()] = word;
			
			field[y][x]->addWord(&words[word.getYPos() * sizeY + word.getXPos()]);
		}
		else if (field[y][x]->getValue() == word.getValue().at(i)) {
			field[y][x]->addWord(&words[word.getYPos() * sizeY + word.getXPos()]);
		}
		else 
			//It's invalid
			return false;
		words[word.getYPos() * sizeY + word.getXPos()].letters[i] = &lettersMap[y*sizeY + x];
	}
	field[word.getYPos()][word.getXPos()]->setIsAvailable(true);
	return true;
}

bool Board::readBoardFromFile(string path) {
	ifstream boardFile;
	stringstream ss;
	string line, dummy ="";
	try {
		boardFile.open(path, ios::in);
		//Read size 
		getline(boardFile, line);
		ss = stringstream(line);
		ss >> sizeY >> dummy >> sizeX;

		//If conditions don't meet, the file is in a incorrect format
		if (!(2 <= sizeY && sizeY <= 20 && 2 <= sizeX && sizeX <= 20 && dummy == "x")) return false;
		reset_board(sizeY, sizeX);
		//Read the board
		do {
			getline(boardFile, line);
			ss = stringstream(line);

			if (line == "") break; // empty line should be ignored

			string positions, direction, wordValue;
			ss >> positions >> direction >> wordValue;
			int yPos, xPos;
			if(checkPosition(positions) && (direction == "V" || direction == "H")){ // Checks if position is in a valid format
				yPos = positions.at(0) - 'A';
				xPos = positions.at(1) - 'a';
				Word newWord = Word(wordValue, yPos, xPos, direction == "H");
				if (!insertWord(newWord)) return false;
			}
			else return false; // File wasn't in a correct format
		} while (!boardFile.eof());
		fillMaps();
	}
	catch (int e) {
		return false;
	}
	return words.size() != 0;
}

bool Board::fillTile(int y, int x, Player &player) {
	//Check if positions are valid
	if (!(0 <= y && y < sizeY && 0 <= x && x < sizeX))
		return false;
	//Check if it's available
	if (!field[y][x]->getIsAvailable()) 
		return false;

	field[y][x]->setIsAvailable(false);
	field[y][x]->setIsFilled(true);

	for (Word* word : field[y][x]->getIncludedIn()) {
		word->setLettersRemaining(word->getLettersRemaining() - 1);
		if (word->getLettersRemaining() == 0) {
			//Finished word
			player.setPoints(player.getPoints() + 1);
		} else if (word->letters[word->getIndexToPlay()]->equals(field[y][x])) {
			//Update indexToPlay in each word
			word->calculateIndexToPlay();

			//If letter to play in each letters doesn't match, it isn't available to play
			bool isAvailable= true;
			for (Word* word2 : word->letters[word->getIndexToPlay()]->getIncludedIn()) {
				if (!word->letters[word->getIndexToPlay()]->equals(word2->letters[word2->getIndexToPlay()])) {
					isAvailable = false;
					break;
				}
			}
			word->letters[word->getIndexToPlay()]->setIsAvailable(isAvailable);
		}
	}
	return true;
}



//getters and setters
int Board::getSizeY() {
	return sizeY;
}
void Board::setSizeY(int sizeY) {
	this->sizeY = sizeY;
}
int Board::getSizeX() {
	return sizeX;
}
void Board::setSizeX(int sizeX) {
	this->sizeX = sizeX;
}

vector<vector<Letter*>> Board::getField() {
	return field;
}
void Board::setField(vector<vector<Letter*>> field) {
	this->field = field;
}


