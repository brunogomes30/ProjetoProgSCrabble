#include "Word.h"
#include "Letter.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

Word::Word() {
	value = "";
	yPos = 0;
	xPos = 0;
	indexToPlay = 0;
	isHorizontal = true;
	lettersRemaining = 0;
}


Word::Word(string str, int y, int x, bool isHorizontal) {
	this->value = str;
	vector<Letter*> letters(str.length());
	for (size_t i = 0;i < str.length();i++) {
		if (isHorizontal) letters[i] = &Letter(str.at(i), y, x + i);
		else letters[i] = &Letter(str.at(i), y + i, x);
	}
	this->yPos = y;
	this->xPos = x;
	this->indexToPlay = 0;
	this->isHorizontal = isHorizontal;
	this->letters = letters;
	lettersRemaining = str.length();
}

void Word::calculateIndexToPlay() {
	for (int i = indexToPlay; i < value.length(); i++) {
		if (!letters[i]->getIsFilled())
			break;
		if(indexToPlay < value.length()) 
			indexToPlay++;	
	}
}

//Getters and setters

bool Word::getIsHorizontal() {
	return isHorizontal;
}
void Word::setIsHorizontal(bool isHorizontal) {
	this->isHorizontal = isHorizontal;
}
int Word::getXPos() {
	return xPos;
}
void Word::setXPos(int xPos) {
	this->xPos = xPos;
}
int Word::getYPos() {
	return yPos;
}
void Word::setYPos(int yPos) {
	this->yPos = yPos;
}
string Word::getValue() {
	return value;
}
void Word::setValue(string value) {
	this->value = value;
}
int Word::getLettersRemaining() {
	return lettersRemaining;
}
void Word::setLettersRemaining(int lettersRemaining) {
	this->lettersRemaining = lettersRemaining;
}
int Word::getIndexToPlay() {
	return indexToPlay;
}
void Word::setIndexToPlay() {
	this->indexToPlay = indexToPlay;
}
vector<Letter*> Word::getLetters() {
	return letters;
}
void Word::setLetters(vector<Letter *> letters) {
	this->letters = letters;
}