#ifndef PLAYER_GUARD
#define PLAYER_GUARD
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Player {
	public:	
			Player(string name);
			void addLetter(char c);
			void replaceLetter(char c, int index);
			int getLetterIndex(char c, int nth = 1);
			void removeLetter(int index);

			//Gettes and setters
			string getName();
			void setName(string name);
			int getPoints();
			void setPoints(int points);
			vector<char> getLetters();
			void setLetters(vector<char> letters);
	private:
			string name;
			int points;
			vector<char> letters;
};
#endif