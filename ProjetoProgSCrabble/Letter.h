#ifndef LETTER_GUARD
#define LETTER_GUARD

#include "Word.h"

#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Letter {
	public:	vector<Word> includedIn;
			int yPos;
			int xPos;
			char value;
			bool isFilled = false;
			bool isAvailable;

			Letter(char value, int yPos, int xPos);
};
#endif