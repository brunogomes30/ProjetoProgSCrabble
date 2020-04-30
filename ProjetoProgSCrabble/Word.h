#ifndef WORD_GUARD
#define WORD_GUARD

#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Word {
public:	string value;
		bool isHorizontal;
		int xPos;
		int yPos;
		int indexToPlay;
		Word(string str, int y, int x, bool isHorizontal);
};
#endif