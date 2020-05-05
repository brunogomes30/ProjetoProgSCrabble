#ifndef COMMON_GUARD
#define COMMON_GUARD

#include<string>
using namespace std;
/*
 * Clears the console screen
 */
void clear();
void setconsolecolor(int textColor, int bgColor);
bool checkPosition(string s);
void checkCinFail();
#endif