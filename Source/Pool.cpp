#include "Pool.h"

#include "Word.h"
#include<string>
#include<vector>
#include<iostream>
#include<ctime>

using namespace std;

Pool::Pool() {
	//Do nothing
	srand(clock());
}
Pool::Pool(vector<Word> words) {
	srand(clock());
	for (Word word : words) {
		addWord(word);
	}
}

bool Pool::canRemoveLetter() {
	return allLetters.size() != 0;
}
char Pool::removeRandomLetter() {
	if (allLetters.size() == 0) {
		return '\0';
	}
	int random = rand() % allLetters.size();
	char c = allLetters[random];
	allLetters.erase(allLetters.begin() + random);
	return c;
}

void Pool::addWord(Word word) {
	for (int i = 0;i < word.getValue().length();i++)
		allLetters.push_back(word.getValue().at(i));
}

void Pool::addChar(char c) {
	allLetters.push_back(c);
}

//Getters and setters

vector<char> Pool::getAllLetters() {
	return allLetters;
}


