#include "Player.h"

#include "Pool.h"
#include<string>
#include<vector>
#include<iostream>

Player::Player(string name) {
	this->name = name;
	this->points = 0;
}

void Player::addLetter(char c) {
	letters.push_back(c);
}
void Player::removeLetter(int index) {
	letters.erase(letters.begin() + index);
}
void Player::replaceLetter(char c, int index) {
	letters.erase(letters.begin() + index);
	if(c != '\0') letters.insert(letters.begin() + index, c);
}

int Player::getLetterIndex(char c, int nth) {

	int indexOfChar = -1;
	for (int i = 0;i < (int)letters.size();i++) {
		if (c == letters[i] && nth == 1) {
			indexOfChar = i;
			break;
		}
		else if (c == letters[i])
			nth--;
	}
	return indexOfChar;
}

//Getters and setters
string Player::getName() {
	return name;
}
void Player::setName(string name) {
	this->name = name;
}
int Player::getPoints() {
	return points;
}
void Player::setPoints(int points) {
	this->points = points;
}
vector<char> Player::getLetters() {
	return letters;
}
void Player::setLetters(vector<char> letters) {
	this->letters = letters;
}
