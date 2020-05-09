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
	for (int i = 0;i < str.length();i++) {
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
		if (!letters[i]->isFilled)
			break;
		if(indexToPlay < value.length()) 
			indexToPlay++;	
	}
}