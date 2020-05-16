#ifndef WORD_GUARD
#define WORD_GUARD

#include "Letter.h"
#include<string>
#include<vector>
#include<iostream>

class Letter;
class Word {

public:	
		
		

		/*
		 * Calculates the next index to play in the current word
		 */
		void calculateIndexToPlay();

		Word();
		Word(std::string str, int y, int x, bool isHorizontal);

		//getters and setters
		bool getIsHorizontal();
		void setIsHorizontal(bool isHorizontal);
		int getXPos();
		void setXPos(int xPos);
		int getYPos();
		void setYPos(int yPos);
		std::string getValue();
		void setValue(std::string value);
		int getLettersRemaining();
		void setLettersRemaining(int lettersRemaining);
		int getIndexToPlay();
		void setIndexToPlay();
		std::vector<Letter*> getLetters();
		void setLetters(std::vector<Letter *> letters);
private:
		std::vector<Letter*> letters;
		std::string value;
		bool isHorizontal;
		int xPos;
		int yPos;
		int indexToPlay;
		int lettersRemaining;
};
#endif