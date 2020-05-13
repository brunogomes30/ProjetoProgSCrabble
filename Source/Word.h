#ifndef WORD_GUARD
#define WORD_GUARD

#include "Letter.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Letter;
class Word {

public:	
		vector<Letter*> letters;
		Word();
		void calculateIndexToPlay();
		Word(string str, int y, int x, bool isHorizontal);

		//getters and setters
		bool getIsHorizontal();
		void setIsHorizontal(bool isHorizontal);
		int getXPos();
		void setXPos(int xPos);
		int getYPos();
		void setYPos(int yPos);
		string getValue();
		void setValue(string value);
		int getLettersRemaining();
		void setLettersRemaining(int lettersRemaining);
		int getIndexToPlay();
		void setIndexToPlay();
private:
		string value;
		bool isHorizontal;
		int xPos;
		int yPos;
		int indexToPlay;
		int lettersRemaining;
};
#endif