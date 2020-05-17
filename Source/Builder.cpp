#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "common.h"
#include "Word.h"
#include "Board.h"



using namespace std;

bool wordIsValid(Board board, Word word, vector<string> wordsVector)
{
    //Validate position of the word based on the size
	int endY = word.getIsHorizontal() ? word.getYPos() : word.getYPos() + word.getValue().length();
	int endX = word.getIsHorizontal() ? word.getXPos() + word.getValue().length()  : word.getXPos();

	if (word.getXPos() < 0 || word.getYPos() < 0 || endX >= board.getSizeX() || endY >= board.getSizeY())
		return false;
	
	//Validate if board is correct with the inserted word
    return board.insertWord(word) && board.checksIsValid();
}


void setPos(Word &word)
{
	cout << "Insert the position of the first letter in the board(ex: Aa)";
	string pos;
	do {
		cin >> pos;
		clearCin();
	} while (!checkPosition(pos));
	word.setYPos(pos.at(0) - 'A');
	word.setXPos(pos.at(1) - 'a');

	cout << "Insert the position of the first letter in the board(ex: V or H)";
	string direction;
	do {
		cin >> direction;
		clearCin();

	} while (direction != "V" && direction != "H" && direction != "v" && direction != "h");

	word.setIsHorizontal(direction == "H" || direction == "h");
}


bool binarySearch(vector<string> vector, string word) {
    int l = 0, h = (int)vector.size() - 1;
    while (l < h) {
        int m = (l + h) / 2;
        if (vector[m] == word) {
            return true;
        }
        if (vector[m] > word) {
            h = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    return false;
}

string getWordOrEnd(vector<string> aDictionary, bool endingBool)
{
    string aWord;
    cout << "Insert a word you would want to put on the board or type \"stopandstore\" if you want to terminate the board creation, " << endl;
    cin >> aWord;
    if (aWord == "stopandstore") {
        endingBool = true;
    }
    while ((cin.fail() || !binarySearch(aDictionary, aWord)) && !endingBool) {
        if (cin.fail()) {
            clearCinStr();
            cin >> aWord;
        }
        if (!binarySearch(aDictionary, aWord)) {
            cout << "That is not in our dictionary, please insert another one." << endl;
            cin >> aWord;
        }
    }
    return aWord;
}

bool streamlineOrientation(string theorientation) {
    return !(theorientation == "v" || theorientation == "V" || theorientation == "Vertical" || theorientation == "vertical");
}

bool validOrientation(string theorientation) {
    return (theorientation == "v" || theorientation == "V" || theorientation == "h" || theorientation == "H" || theorientation == "Vertical" || theorientation == "Horizontal" || theorientation == "vertical" || theorientation == "horizontal");
}

void dictFill(string filename, vector<string> &aDictionary) {
    ifstream inStream;
    inStream.open(filename);
    string dictword;
    if (!inStream.is_open())
    {
        cout << "Failed to open " << filename << endl;
    }
    while (getline(inStream, dictword))//(!inStream.eof())
    {
        //cout << dictword;
        aDictionary.push_back(dictword);
    }
    inStream.close();
}



int sizeValidator()
{
    int theinput;
    cin >> theinput;
    while ((cin.fail() || (theinput < 1 || theinput > 20)))
    {
        if (cin.fail())
        {
            clearCin();
            cout << "Please insert an integer" << endl;
            cin >> theinput;
        }
        if (theinput < 1 || theinput > 20)
        {
            clearCin();
            cout << "Please insert an integer from 1 to 20" << endl;
            cin >> theinput;
        }
    }
    return theinput;
}

void boardSize(Board &board)
{
    clear();
    cout << "Insert board length" << endl;
    int length = sizeValidator();
    cout << "Insert board wideness" << endl;
    int width = sizeValidator();
    if (length * width < 14)
    {
        cout << "You need a bigger board" << endl;
        boardSize(board);
    }
	board.reset_board(length, width);
}


void exportBoard(vector<string> pos, vector<string> orientacao, vector<string> palavras, string filename)
{
    ofstream outfile(filename);
    for (size_t i = 0; i < palavras.size(); i++)
    {
        outfile << pos[i] << " " << orientacao[i] << " " << palavras[i] << endl;
    }
    outfile.close();
    cout << "Your board is now stored at board.txt" << endl;
}


int main(){
    vector<string> dictionary;
    vector<string> words;
    vector<string> orientations;
    vector<string> posicions;
    bool stop = false;
    Board newboard;
    Word newWord;
    dictFill("WORDS.txt", dictionary);
    boardSize(newboard);
    while (!stop) {
		newboard.printBoard();
        newWord.setValue(getWordOrEnd(dictionary, stop));
        if (newWord.getValue() == "stopandstore") {
            stop = true;
        }
        else {
            setPos(newWord);
			clear();
            if (wordIsValid(newboard, newWord, words)) {
				newboard.insertWord(newWord);

            }
            else
            {
                clear();
                cout << "The word you entered is invalid in this position, please try a new position or introduce a different. You can also stop." << endl;
            }
        }
    }
    exportBoard(orientations, posicions, words, "board.txt");
}