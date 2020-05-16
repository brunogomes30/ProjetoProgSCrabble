#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "common.h"
#include "Word.h"
#include "Colors.h"
#include "Board.h"



using namespace std;

vector<string> dictionary;
vector<string> words;
vector<string> orientations;
vector<string> posicions;
bool stop = false;
Board newboard;
Word newWord;

int main()
{
    dictFill("WORDS.txt");
    boardSize();
    while (stop == false)
    {
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
    //dafsgdhghdjfkgfhdgssthdjfkgjhtgsrfgsthdyjfkugfjhdgsrfragtshdyjfdhsg
}
void invalidWord()
{
    cout << "The word you entered is invalid in this position, please try a new position or introduce a new one. You can also stop.";
}
void setPos()
{
    string xpos;
    string ypos;
    cout << "Please input the letter corresponding to the position of the first letter of the desired word in the x axis or that same letter followed by the letter corresponding to the position of the first letter of the desired word in the y axis" << endl;
    cin >> xpos;
    while (cin.fail()|| xpos.size() > 2 || xpos.size() == 0)
    {
        if (cin.fail())
        {
            clearCinStr();
            cin >> xpos;
        }
        else
        {
            cout << "That was not a valid position. Please input a valid one." << endl;
            cin >> xpos;
        }
        
    }
    if (xpos.size() == 2)
    {
        for(int i=0; i<2; i++) 
        {
            xpos[i] = tolower(xpos[i]);
        }
        newWord.setXPos(int(xpos[0])-)97;
        newWord.setYPos(int(xpos[1])-97);
    }
    else
    {
        xpos = tolower(xpos[0]);
        cout << "Please input the letter corresponding to the position of the first letter of the desired word in the y axis" << endl;
        cin >> ypos;
    }
    

}

void saveword()
{
    words.push_back(newWord.getValue());
    if (newWord.getIsHorizontal());
    {
        orientations.push_back("H");
    }
    else
    {
        orientations.push_back("W");
    }
    //posicions.push_back wieuhfmpqcwg9qehrmhepoxmergu9pqerhcgiqaegx08qperghk
}

void clearCinStr()
{
    clearCin();
    cout << "Please insert a string";
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
    cout << "what is the orientation of that word? (horizontal or vertical)" << endl;
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
            cout << "That string was not a valid orientation, please input a new one. (Horizontal or Vertical)" << endl;
            cin >> aOrientation;
        }
    }
    return streamlineOrientation(aOrientation);
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
    cout << "Insert board length" << endl;
    int length = sizeValidator();
    newboard.setSizeX(length);
    cout << "Insert board wideness" << endl;
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
}

void exportBoard()
{
    ofstream outfile("board.txt");
    for(int i=0; i< words.size(); i++)
    {
        outfile << posicions[i] << " " << orientations[i] << " " << words[i] << endl;
    }
    outfile.close();
    cout << "Your board is now stored at board.txt" << endl;
}