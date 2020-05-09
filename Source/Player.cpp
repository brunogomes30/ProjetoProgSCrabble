#include "Player.h"

#include "Pool.h"
#include<string>
#include<vector>
#include<iostream>

Player::Player(string name) {
	this->name = name;
	this->points = 0;
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
