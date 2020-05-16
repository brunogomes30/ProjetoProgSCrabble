#ifndef POOL_GUARD
#define POOL_GUARD

#include "Word.h"
#include<string>
#include<vector>
#include<iostream>


class Pool {
public:
		/*
		 * Adds a word to the pool
		 * @param word
		 */
		void addWord(Word word);

		/*
		 * Removes and returns a random letter from the pool
		 */
		char removeRandomLetter();

		/* 
		 * Adds a letter/char to the pool
		 */
		void addChar(char c);

		/*
		 * Returns true if pool isn't empty
		 */
		bool canRemoveLetter();


		Pool();
		Pool(std::vector<Word> words);

		//getters and setters
		std::vector<char> getAllLetters();
private:	
		std::vector<char> allLetters;
};

#endif