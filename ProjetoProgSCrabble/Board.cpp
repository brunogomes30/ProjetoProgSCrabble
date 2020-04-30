#include "Board.h"
#include "Word.h"
#include <Windows.h>
#include "Colors.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

void setconsolecolor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
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
			if (field[y][x].value == ' ')
				setconsolecolor(BLACK, BROWN);
			else if (field[y][x].isFilled)
				setconsolecolor(RED, BROWN);
			else if (field[y][x].isAvailable)
				setconsolecolor(GREEN, BROWN);
			else
				setconsolecolor(BLACK, BROWN);

			cout << " " << field[y][x].value << " ";
		}
		setconsolecolor(BLACK, DARKGRAY);
		cout << "   ";
		cout << "\n";
		
		
	}
	setconsolecolor(BLACK, DARKGRAY);
	for (int x = 0; x < sizeX + 2;x++)
		cout << "   ";
	setconsolecolor(WHITE, BLACK);
}

void Board::reset_board(int sizeY, int sizeX) {
	this->sizeY = sizeY;
	this->sizeX = sizeX;
	vector<vector<Letter>> field;
	for (int y = 0; y < sizeY; y++) {
		vector<Letter> vector;
		for (int x = 0; x < sizeX; x++) {
			vector.push_back(Letter(' ', y, x));
		}
		field.push_back(vector);
	}
	this->field = field;
}

bool Board::insertWord(Word word) {
	for (int i = 0;i < word.value.length(); i++) {
		int y = word.yPos;
		int x = word.xPos;
		if (word.isHorizontal) x += i;
		else y += i;
		//Verifica se está vazio
		if (field[y][x].value == ' ') {
			field[y][x] = Letter(word.value.at(i), y, x);
		}
		else if (field[y][x].value == word.value.at(i)) {
			field[y][x].includedIn.push_back(word);
		}
		else 
			return false;
	}
	field[word.yPos][word.xPos].isAvailable = true;
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
	return true;
}

