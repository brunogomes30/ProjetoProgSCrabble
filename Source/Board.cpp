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
	for (map<string, Word>::iterator it = words.begin();it != words.end(); it++) {
		vector<Letter*> letters = it->second.letters;
		for (int i = 0;i < letters.size();i++) {
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
	words[word.getValue()] = word;
	for (int i = 0;i < word.getValue().length(); i++) {
		int y = word.getYPos();
		int x = word.getXPos();
		if (word.getIsHorizontal()) x += i;
		else y += i;
		
		//Verifica se está vazio
		if (field[y][x]->getValue() == ' ') {
			lettersMap[y*sizeY + x] = Letter(word.getValue().at(i), y, x);
			field[y][x] = &lettersMap[y*sizeY + x];
			words[word.getValue()] = word;
			
			//field[y][x]->getIncludedIn().push_back(&words[word.value]);
			vector<Word *> v = field[y][x]->getIncludedIn();
			v.push_back(&words[word.getValue()]);
			field[y][x]->setIncludedIn(v);
		}
		else if (field[y][x]->getValue() == word.getValue().at(i)) {
			vector<Word *> v = field[y][x]->getIncludedIn();
			v.push_back(&words[word.getValue()]);
			field[y][x]->setIncludedIn(v);

		}
		//field[y][x]->getIncludedIn().push_back(&words[word.value])
		else 
			return false;
		words[word.getValue()].letters[i] = &lettersMap[y*sizeY + x];
	}
	field[word.getYPos()][word.getXPos()]->setIsAvailable(true);
	return true;
}

bool Board::readBoardFromFile(string path) {
	ifstream boardFile;
	stringstream ss;
	string line, dummy;
	try {
		boardFile.open(path, ios::in);
		//Read size 
		getline(boardFile, line);
		ss = stringstream(line);
		ss >> sizeY >> dummy >> sizeX;
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
				insertWord(newWord);
			}

			
		} while (!boardFile.eof());
		fillMaps();
	}
	catch (int e) {
		return false;
	}
	return true;
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
		//Finished word
		if (word->getLettersRemaining() == 0) {
			player.setPoints(player.getPoints() + 1);
		} else if (word->letters[word->getIndexToPlay()]->equals(field[y][x])) {
			word->calculateIndexToPlay();
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


