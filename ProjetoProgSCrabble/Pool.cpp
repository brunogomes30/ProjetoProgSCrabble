#include "Pool.h"

#include "Word.h"
#include<string>
#include<vector>
#include<iostream>
#include<ctime>

using namespace std;

Pool::Pool() {
	//Do nothing
}
Pool::Pool(vector<Word> words) {
	for (Word word : words) {
		addWord(word);
	}
}

char Pool::removeRandomLetter() {
	if (allLetters.size() == 0) {
		return '\0';
	}
	srand(clock());
	int random = rand() % allLetters.size();
	char c = allLetters[random];
	allLetters.erase(allLetters.begin() + random);
	return c;
}

void Pool::addWord(Word word) {
	for (int i = 0;i < word.value.length();i++)
		allLetters.push_back(word.value.at(i));
}

void Pool::addChar(char c) {
	allLetters.push_back(c);
}