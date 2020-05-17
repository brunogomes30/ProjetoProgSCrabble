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
		vector<Letter*> letters = it->second.getLetters();
		for (size_t i = 0;i < letters.size();i++) {
			int y = it->second.getYPos();
			int x = it->second.getXPos();
			if (it->second.getIsHorizontal()) x += i;
			else y += i;
			letters[i] = &lettersMap[y * sizeY + x];
		}
		it->second.setLetters(letters);
	}
}


void Board::printBoard() {
	int backgroundColor = LIGHTGRAY;
	int borderColor = BLACK;

	setconsolecolor(WHITE, borderColor);
	cout << "   ";
	for (int x = 0; x < sizeX;x++)

		cout << " " <<char('a' + x) << " ";
	cout << "   ";
	setconsolecolor(WHITE, BLACK);
	cout << endl;
	
	for (int y = 0; y < sizeY; y++) {
		setconsolecolor(WHITE, borderColor);
		cout << " " << char('A' + y) << " ";
		setconsolecolor(WHITE, BLACK);
		

		for (int x = 0; x < sizeX; x++) {

			if (field[y][x]->getValue() == ' ')
				setconsolecolor(BLACK, backgroundColor);
			else if (field[y][x]->getIsFilled())
				setconsolecolor(RED, backgroundColor);
			else if (field[y][x]->getIsAvailable() && field[y][x]->getCanPlay())
				setconsolecolor(BLUE, backgroundColor);
			else
				setconsolecolor(BLACK, backgroundColor);
			
			cout << " " << field[y][x]->getValue() << " ";

		}
		setconsolecolor(BLACK, borderColor);
		cout << "   ";
		cout << "\n";
		
		
	}
	setconsolecolor(BLACK, borderColor);
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

Word Board::findWord(int yPos, int xPos, bool isHorizontal) {
	return words[yPos * sizeY + xPos + isHorizontal * sizeX*sizeY];
}

vector<Word> Board::getAllWords() {
	vector<Word> vector;
	for (map<int, Word>::iterator it = words.begin();it != words.end(); it++) {
		vector.push_back(it->second);
	}
	return vector;
}

bool Board::insertWord(Word word) {
	words[(word.getYPos() * sizeY + word.getXPos()) + sizeY * sizeX * word.getIsHorizontal()] = word;
	vector<Letter*> letters;
	for (size_t i = 0;i < word.getValue().length(); i++) {
		int y = word.getYPos();
		int x = word.getXPos();
		if (word.getIsHorizontal()) x += i;
		else y += i;
		
		if (y < 0 || y >= sizeY || x < 0 || x >= sizeX) return false;
		
		if (field[y][x]->getValue() == ' ') {
			//If it's empty, create a new Letter
			lettersMap[y*sizeY + x] = Letter(word.getValue().at(i), y, x);
			field[y][x] = &lettersMap[y*sizeY + x];
			words[word.getYPos() * sizeY + word.getXPos() + sizeY * sizeX * word.getIsHorizontal()] = word;
			
			field[y][x]->addWord(&words[word.getYPos() * sizeY + word.getXPos() + sizeY * sizeX * word.getIsHorizontal()]);
		}
		else if (field[y][x]->getValue() == word.getValue().at(i)) {
			field[y][x]->addWord(&words[word.getYPos() * sizeY + word.getXPos() + sizeY * sizeX * word.getIsHorizontal()]);
		}
		else 
			//It's invalid
			return false;
		letters.push_back(&lettersMap[y*sizeY + x]);
	}
	words[word.getYPos() * sizeY + word.getXPos() + sizeY * sizeX * word.getIsHorizontal()].setLetters(letters);
	field[word.getYPos()][word.getXPos()]->setIsAvailable(true);
	return true;
}

bool Board::readBoardFromFile(string path) {
	return readBoardFromFile(path, 0);
}

bool Board::readBoardFromFile(string path, int numOfPlayers) {
	ifstream boardFile;
	stringstream ss;
	string line, dummy ="";
	int numOfLetters = 0;
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
	catch (...) {
		return false;
	}

	//Count letters
	for (int y = 0; y < sizeY; y++) for (int x = 0; x < sizeX; x++) {
		if (field[y][x]->getValue() != ' ') 
			numOfLetters += 1;
	}

	return numOfLetters > numOfPlayers * 7;
}

bool Board::removeWord(Word word) {
	int y = word.getYPos();
	int x = word.getXPos();
	bool found = false;
	//Check if word exists
	for (map<int, Word>::iterator it = words.begin();it != words.end(); it++) {
		Word w = it->second;
		if (w == word) {
			found = true;
			break;
		}
	}
	if (!found) return false;

	for (Letter* letter : words[word.getYPos()*sizeY + word.getXPos() + sizeY * sizeX * word.getIsHorizontal()].getLetters()) {

		vector<Word*> includedIn = letter->getIncludedIn();
		if (includedIn.size() >= 2) {
			//Find word
			int indexOfWord;
			for (size_t i = 0;i < includedIn.size(); i++) {
				if (*includedIn[i] == word) {
					indexOfWord = i;
					break;
				}
			}
			includedIn.erase(includedIn.begin() + indexOfWord);
		}
		else {
			includedIn.pop_back();
			letter->setValue(' ');
		}
		letter->setIncludedIn(includedIn);
	}
	words.erase(word.getYPos()*sizeY + word.getXPos() + sizeY * sizeX * word.getIsHorizontal());
	return true;
}

bool Board::checksIsValid() {
	Board newBoard = Board();
	newBoard.reset_board(sizeY, sizeX);
	bool isReadingWord = false;
	//Read horizontal
	Word newWord;
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0;x < sizeX; x++) {
			if (!isReadingWord && field[y][x]->getValue() != ' ') {
				isReadingWord = true;
				string firstLetter = "";
				firstLetter = firstLetter + field[y][x]->getValue();
				newWord = Word(firstLetter, y, x, true);
			}
			else if (isReadingWord && field[y][x]->getValue() != ' ') {
				newWord.setValue(newWord.getValue() + field[y][x]->getValue());
			}
			else if (isReadingWord && field[y][x]->getValue() == ' ') {
				isReadingWord = false;
				if (newWord.getValue().length() > 1) newBoard.insertWord(newWord);
			}
		}
		if (isReadingWord) {
			isReadingWord = false;
			if (newWord.getValue().length() > 1) newBoard.insertWord(newWord);
		}
	}

	//Read Vertical
	for (int x = 0;x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			if (!isReadingWord && field[y][x]->getValue() != ' ') {
				isReadingWord = true;
				string firstLetter = "";
				firstLetter = firstLetter + field[y][x]->getValue();
				newWord = Word(firstLetter, y, x, false);
			}
			else if (isReadingWord && field[y][x]->getValue() != ' ') {
				newWord.setValue(newWord.getValue() + field[y][x]->getValue());
			}
			else if(isReadingWord && field[y][x]->getValue() == ' '){
				isReadingWord = false;
				if(newWord.getValue().length() > 1) newBoard.insertWord(newWord);
			}
		}
		if (isReadingWord) {
			isReadingWord = false;
			if (newWord.getValue().length() > 1) newBoard.insertWord(newWord);
		}
	}

	return *this == newBoard;
	
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
		} else if (word->getLetters()[word->getIndexToPlay()]->equals(field[y][x])) {
			//Update indexToPlay in each word
			word->calculateIndexToPlay();

			//If letter to play in each words don't match, it isn't available to play
			bool isAvailable= true;
			for (Word* word2 : word->getLetters()[word->getIndexToPlay()]->getIncludedIn()) {
				if (!word->getLetters()[word->getIndexToPlay()]->equals(word2->getLetters()[word2->getIndexToPlay()])) {
					isAvailable = false;
					break;
				}
			}
			word->getLetters()[word->getIndexToPlay()]->setIsAvailable(isAvailable);
		}
	}
	return true;
}

bool Board::operator==(Board a){
	if (a.getSizeX() != getSizeX() || a.getSizeY() != getSizeY())
		return false;
	bool equal = true;
	for (int y = 0;y < sizeY;y++) for (int x = 0;x < sizeX; x++) {
		if (!a.getField()[y][x]->equals(getField()[y][x])) {
			equal = false;
			break;
		}
	}

	return equal;
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


