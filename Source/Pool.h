#ifndef POOL_GUARD
#define POOL_GUARD

#include "Word.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;

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
		Pool(vector<Word> words);

		//getters and setters
		vector<char> getAllLetters();
private:	
		vector<char> allLetters;
};

#endif