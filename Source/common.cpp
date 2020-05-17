#include "common.h"
#include <Windows.h>
#include <iostream>

using namespace std; 

void setconsolecolor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}


void clear() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	//cout << "\x1B[2J\x1B[H";
	system("cls");
}

void clearCin() {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
}

/*
 *	Checks if string is in the format "Xx"
 */
bool checkPosition(string s) { 
	if (s.length() != 2) return false;
	return 'A' <= s.at(0) && s.at(0) <= 'Z' && 'a' <= s.at(1) && s.at(1) <= 'z';
}


