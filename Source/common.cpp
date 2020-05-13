#include "common.h"
#include <Windows.h>
#include <iostream>

using namespace std; 

void setconsolecolor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}


void clear() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	cout << "\x1B[2J\x1B[H";
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


//Private
bool Rules::verifyIndexs(int y, int x) {
	return 0 <= y && y < lines && 0 <= y && y < columns;
}

	flags = false;
	bool isLastLetter = index == 0;
	bool isFirstLetter = index == word_size - 1;
	int y = index_l, x = index_c;

	//Se for a primeira letra, a letra atrás da mesma tem de estar vazia
	if (isFirstLetter) {
		if (direction == 'H' && index_c > 0 && actual_board[y][x - 1] != ' ') return false;
		else if (index_l > 0 && actual_board[y - 1][x] != ' ') return false;
	}

	//Se for a ultima letra, a letra depois da mesma tem de estar vazia
	else if (isLastLetter) {
		if (direction == 'H' && index_c < columns - 1 && actual_board[y][x + 1] != ' ') return false;
		else if (index_l < lines - 1 && actual_board[y + 1][x] != ' ') return false;
	}

	// Ver se em cima e em baixo está vazio, se for 'H', ver direita e esquerda  se for 'V'
	if (!intersection_char)
		for (int i = -1;i <= 1;i += 2) {
			if (direction == 'H') y = index_c + i;
			else x = index_l + i;
			if (verifyIndexes(y, x) && && actual_board[y][x] != ' ') return false;
		}

	flag_sides = true;
	return true;
