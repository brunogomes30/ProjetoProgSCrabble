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