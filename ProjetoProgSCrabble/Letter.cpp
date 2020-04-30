#include "Letter.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

Letter::Letter(char value, int yPos, int xPos) {
	this->value = value;
	this->yPos = yPos;
	this->xPos = xPos;
	isAvailable = false;
	isFilled = false;
}