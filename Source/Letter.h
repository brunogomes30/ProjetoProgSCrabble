#ifndef LETTER_GUARD
#define LETTER_GUARD

#include "Word.h"

#include<string>
#include<vector>
#include<iostream>
class Word;

class Letter {
	public:	
			Letter();
			Letter(char value, int yPos, int xPos);

			/*
			 * Returns true if  both letters are equal 
			 */
			bool equals(Letter letter);

			/*
			 * Returns true if  both letters are equal
			 */
			bool equals(Letter *letter);

			/*
			 * Add word to the words vector that letter is included in
			 */
			void addWord(Word *word);

			//Getters and setters
			std::vector<Word*> getIncludedIn();
			void setIncludedIn(std::vector<Word*> includedIn);
			char getValue();
			void setValue(char value);
			bool getIsFilled();
			void setIsFilled(bool isFilled);
			bool getIsAvailable();
			void setIsAvailable(bool isAvailable);
			bool getCanPlay();
			void setCanPlay(bool canPlay);

	private:
			std::vector<Word*> includedIn;
			int yPos;
			int xPos;
			char value;
			int a, b = 2 * a;
			bool isFilled = false;
			bool isAvailable;
			bool canPlay; // used only in ScrabbleJunior
};
#endif