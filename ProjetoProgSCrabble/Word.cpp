#include "Word.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

Word::Word(string str, int y, int x, bool isHorizontal) {
	this->value = str;
	this->yPos = y;
	this->xPos = x;
	this->indexToPlay = 0;
	this->isHorizontal = isHorizontal;
}