#ifndef LETTER_GUARD
#define LETTER_GUARD

#include "Word.h"

#include<string>
#include<vector>
#include<iostream>
class Word;
using namespace std;
class Letter {
	public:	
			Letter();
			Letter(char value, int yPos, int xPos);
			bool equals(Letter letter);
			bool equals(Letter *letter);

			//Getters and setters
			vector<Word*> getIncludedIn();
			void setIncludedIn(vector<Word*> includedIn);
			char getValue();
			void setValue(char value);
			bool getIsFilled();
			void setIsFilled(bool isFilled);
			bool getIsAvailable();
			void setIsAvailable(bool isAvailable);
			bool getCanPlay();
			void setCanPlay(bool canPlay);

	private:
			vector<Word*> includedIn;
			int yPos;
			int xPos;
			char value;
			bool isFilled = false;
			bool isAvailable;
			bool canPlay; // use only in ScrabbleJunior
};
#endif