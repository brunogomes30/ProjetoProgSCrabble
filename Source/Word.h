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
		
		

		/*
		 * Calculates the next index to play in the current word
		 */
		void calculateIndexToPlay();

		Word();
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
		vector<Letter*> getLetters();
		void setLetters(vector<Letter *> letters);
private:
		vector<Letter*> letters;
		string value;
		bool isHorizontal;
		int xPos;
		int yPos;
		int indexToPlay;
		int lettersRemaining;
};
#endif