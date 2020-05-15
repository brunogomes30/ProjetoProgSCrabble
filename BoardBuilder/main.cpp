#include <iostream>
#include <fstream>
#include <vector>
#include "common.h"
#include "Word.h"
#include "Colors.h"
#include "Board.h"


using namespace std;

vector<string> dictionary;
vector<string> words;
vector<string> directions;
vector<string> posicions;
bool stop = false;
Board newboard;

int main()
{
    dictFill("WORDS.txt");
    boardSize();
    while (stop == false)
    {
        Word newWord;
        newWord.setValue(getWordOrEnd());
        newWord.setIsHorizontal(getOrientation());
        setPos();
        if (wordIsValid(newboard, newWord))
        {
            newboard.insertWord(newWord);
            saveword();
        }
        else
        {
            invalidWord();
        }
    }
    exportBoard();
}

bool wordIsValid(Board aboard, Word aword)
{
    //dafsgdh
}
void invalidWord()
{
    cout << "cycka blyat";
}
void setPos()
{
    cout << ""; //
}

void saveword()
{
    //guarda nos vetores
}

void clearCinStr()
{
    clearCin();
    cout << "please insert a string";
}

string getWordOrEnd()
{
    string aWord;
    cout << "Insert a word you would want to put on the board or type \"stopbuilding\" if you want to terminate the board creation, ";
    cin >> aWord;
    if (aWord == "stopbuilding")
    {
        stop == true;
    }
    while (cin.fail() || !binarySearch(dictionary, aWord))
    {
        if (cin.fail());
        {
            clearCinStr();
            cin >> aWord;
        }
        if (!binarySearch(dictionary, aWord))
        {
            cout << "That string is not in our dictionary, please insert another one.";
            cin >> aWord;
        }
    }
    return aWord;
}

bool getOrientation()
{
    string aOrientation;
    cout << "what is the orientation of that word? (horizontal or vertical)";
    cin >> aOrientation;
    while (cin.fail() || !validOrientation(aOrientation))
    {
        if (cin.fail())
        {
            clearCinStr();
            cin >> aOrientation;
        }
        else
        {
            clearCin();
            cout << "That string was not a valid orientation, please input a new one. (Horizontal or Vertical)";
            cin >> aOrientation;
        }
    }
    return streamlineOrientation(aOrientation);
}

string getPos()
{

}
bool validOrientation(string theorientation)
{
    if (theorientation == "v" || theorientation == "V" || theorientation == "h" || theorientation == "H" || theorientation == "Vertical" || theorientation == "Horizontal" || theorientation == "vertical" || theorientation == "horizontal")
    {
    return true;
    }
    else
    {
        return false;
    }

}

bool streamlineOrientation(string theorientation)
{
    if (theorientation == "v" || theorientation == "V" || theorientation == "Vertical" || theorientation == "vertical")
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool dictFill(string filename)
{
    ifstream inStream;
    inStream.open(filename);
    string dictword;
    while (!getline(inStream, dictword).eof())
    {
        dictionary.push_back(dictword);
    }
    inStream.close();
}

int binarySearch(vector<string> vector, string word)
{
    int l = 0, h = (int)vector.size() - 1;
    while (l < h)
    {
        int m = (l + h) / 2;
        if (vector[m] == word)
        {
            return true;
        }
        if (vector[m] > word)
        {
             h = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return false;
}
void boardSize()
{
    cout << "Insert board length";
    int length = sizeValidator();
    newboard.setSizeX(length);
    cout << "Insert board wideness";
    int width = sizeValidator();
    newboard.setSizeY(width);
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
			cout << "Please insert an integer";
			cin >> theinput;
		}
        if (theinput < 1 || theinput > 20)
        {
            clearCin();
            cout << "Please insert an integer from 1 to 20";
            cin >> theinput;
        }
    }
}

void exportBoard()
{
    ofstream outfile("board.txt");
    for(int i=0; i< words.size(); i++)
    {
        outfile << posicions[i] << " " << directions[i] << " " << words[i] << endl;
    }
    outfile.close();
    cout << "Your board is now stored at board.txt";
}