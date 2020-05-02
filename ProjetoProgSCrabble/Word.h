#ifndef WORD_GUARD
#define WORD_GUARD

#include "Letter.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Letter;
class Word {

public:	string value;
		bool isHorizontal;
		int xPos;
		int yPos;
		int indexToPlay;
		int lettersRemaining;
		vector<Letter*> letters;
		Word();
		void calculateIndexToPlay();
		Word(string str, int y, int x, bool isHorizontal);
};
#endif