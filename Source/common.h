#ifndef COMMON_GUARD
#define COMMON_GUARD

#include<string>

/*
 * Clears the console screen
 */
void clear();

/*
 * Sets the foreground and text color of the output, arguments should be the colors defined in Colors.h
 */
void setconsolecolor(int textColor, int bgColor);

/*
 * Checks if the string s is in the format 'Xx', first char uppercase and second char lowercase 
 */
bool checkPosition(std::string s);

/*
 * Clears the input buffer
 */
void clearCin();

void clearCinStr();
#endif