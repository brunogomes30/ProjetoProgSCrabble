#ifndef PLAYER_GUARD
#define PLAYER_GUARD
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Player {
	public:	
			Player(string name, int color);
			
			/*
			 * Adds a letter to play
			 */
			void addLetter(char c);
			
			/*
			 * Replaces a letter from the player at the given index
			 * @param index - index of the letter
			 */
			void replaceLetter(char c, int index);
			
			/*
			 * Gets the nth index of the letter in the player
			 * @param c
			 * @param nth
			 */
			int getLetterIndex(char c, int nth = 1);
			
			/*
			 * Removes a letter at the given index
			 */
			void removeLetter(int index);

			//Gettes and setters
			string getName();
			void setName(string name);
			int getPoints();
			void setPoints(int points);
			vector<char> getLetters();
			void setLetters(vector<char> letters);
			int getColor();
			void setColor(int color);
	private:
			vector<char> letters;
			string name;
			int points;
			int color;
			
			
};
#endif