#ifndef POOL_GUARD
#define POOL_GUARD

#include "Word.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Pool {
public:
		void addWord(Word word);
		char removeRandomLetter();
		void addChar(char c);
		bool canRemoveLetter();
		Pool();
		Pool(vector<Word> words);

		//getters and setters
		vector<char> getAllLetters();
private:	
		vector<char> allLetters;
};

#endif