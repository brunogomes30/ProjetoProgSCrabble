#ifndef POOL_GUARD
#define POOL_GUARD

#include "Word.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Pool {
public:
	vector<char> allLetters;
	void addWord(Word word);
	char removeRandomLetter();
	void addChar(char c);
	Pool();
	Pool(vector<Word> words);
};

#endif