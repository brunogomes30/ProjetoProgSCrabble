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

void Letter::addWord(Word *word) {
	includedIn.push_back(word);
}

//Getters and setters
vector<Word*> Letter::getIncludedIn() {
	return includedIn;
}
void Letter::setIncludedIn(vector<Word*> includedIn) {
	this->includedIn = includedIn;
}
char Letter::getValue() {
	return value;
}
void Letter::setValue(char value) {
	this->value = value;
}
bool Letter::getIsFilled() {
	return isFilled;
}
void Letter::setIsFilled(bool isFilled) {
	this->isFilled = isFilled;
}
bool Letter::getIsAvailable() {
	return isAvailable;
}
void Letter::setIsAvailable(bool isAvailable) {
	this->isAvailable = isAvailable;
}
bool Letter::getCanPlay() {
	return canPlay;
}
void Letter::setCanPlay(bool canPlay) {
	this->canPlay = canPlay;
}