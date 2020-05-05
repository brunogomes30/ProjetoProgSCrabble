#include "Letter.h"
#include<string>
#include<iostream>

using namespace std;

Letter::Letter() {
	value = ' ';
	yPos = 0;
	xPos = 0;
	isAvailable = false;
	isFilled = false;
	includedIn.reserve(2);
}

Letter::Letter(char value, int yPos, int xPos) {
	this->value = value;
	this->yPos = yPos;
	this->xPos = xPos;
	isAvailable = false;
	isFilled = false;
	includedIn.reserve(2);
}

bool Letter::equals(Letter letter) {
	return letter.value == value && letter.yPos == yPos && letter.xPos == xPos;
}
bool Letter::equals(Letter *letter) {
	return letter->value == value && letter->yPos == yPos && letter->xPos == xPos;
}