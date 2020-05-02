#ifndef PLAYER_GUARD
#define PLAYER_GUARD
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Player {
public:	string name;
		int points;
		vector<char> letters;
		Player(string name);
};
#endif