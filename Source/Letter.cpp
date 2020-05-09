#include "Letter.h"
#include<string>
#include<iostream>

using namespace std;

Letter::Letter() {
	Letter(' ', 0, 0);
}

Letter::Letter(char value, int yPos, int xPos) {
	this->value = value;
	this->yPos = yPos;
	this->xPos = xPos;
	isAvailable = false;
	isFilled = false;
	canPlay = false;
	includedIn.reserve(2);
}

bool Letter::equals(Letter letter) {
	return letter.value == value && letter.yPos == yPos && letter.xPos == xPos;
}
bool Letter::equals(Letter *letter) {
	return letter->value == value && letter->yPos == yPos && letter->xPos == xPos;
}