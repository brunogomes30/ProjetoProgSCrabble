#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "common.h"
#include "Word.h"
#include "Colors.h"
#include "Board.h"



using namespace std;


int main()
{
    vector<string> dictionary;
    vector<string> words;
    vector<string> orientations;
    vector<string> posicions;
    bool stop = false;
    Board newboard;
    Word newWord;
    dictFill("WORDS.txt", dictionary);
    boardSize(newboard);
    while (stop == false)
    {
        newWord.setValue(getWordOrEnd(dictionary, stop));
        newWord.setIsHorizontal(getOrientation());
        setPos(newWord);
        if (wordIsValid(newboard, newWord))
        {
            newboard.insertWord(newWord);
            saveword(newWord, orientations, words, posicions);
        }
        else
        {
            invalidWord();
        }
    }
    exportBoard(orientations, posicions, words);
}

bool wordIsValid(Board aboard, Word aword)
{
    if (aword.getXPos() > aboard.getSizeX() || aword.getYPos() > aboard.getSizeY())
    {
        return false;
    }
    if (aword.getIsHorizontal())
    {
        if (aword.getXPos() + aword.getValue().size() > aboard.getSizeX())
        {
            return false;
        }
        for(int i=0; i<aword.getValue().size(); i++)
        {
            if (aword.getValue()[i] != field[aword.getXPos()+i][aword.getYPos()])
            {
                return false;
            }
        }
    else 
    {
        if (aword.getYPos() + aword.getValue().size() > aboard.getSizeY())
        {
            return false;
        }
        for(int i=0; i<aword.getValue().size(); i++)
        {
            if (aword.getValue()[i] != field[aword.getXPos()][aword.getYPos()+1])
            {
                return false;
            }
        } 
    
}
void invalidWord()
{
    cout << "The word you entered is invalid in this position, please try a new position or introduce a new one. You can also stop.";
}
void setPos(Word aWord)
{
    string xpos;
    char ypos;
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
        aWord.setXPos(int(xpos[0])-97);
        aWord.setYPos(int(xpos[1])-97);
    }
    else
    {
        xpos = tolower(xpos[0]);
        cout << "Please input the letter corresponding to the position of the first letter of the desired word in the y axis" << endl;
        cin >> ypos;
        while (cin.fail() || !isalpha(ypos))
        {
            clearCin();
            cout << "That was not a valid letter of the y axis of the board.";
            cin >> ypos;
        }
        aWord.setXPos(xpos[0]-97);
        aWord.setYPos(ypos-97);
    }
    

}

void saveword(Word aWord, vector<string> directionVector, vector<string> wordNameVector, vector<string> posVector)
{
    wordNameVector.push_back(aWord.getValue());
    if (aWord.getIsHorizontal())
    {
        directionVector.push_back("H");
    }
    else
    {
        directionVector.push_back("W");
    }
    posVector.push_back(to_string((aWord.getXPos())) + to_string(aWord.getYPos()));
}

void clearCinStr()
{
    clearCin();
    cout << "Please insert a string";
}

string getWordOrEnd(vector<string> aDictionary, bool endingBool)
{
    string aWord;
    cout << "Insert a word you would want to put on the board or type \"stopbuilding\" if you want to terminate the board creation, ";
    cin >> aWord;
    if (aWord == "stopbuilding")
    {
        endingBool == true;
    }
    while (cin.fail() || !binarySearch(aDictionary, aWord))
    {
        if (cin.fail());
        {
            clearCinStr();
            cin >> aWord;
        }
        if (!binarySearch(aDictionary, aWord))
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

bool dictFill(string filename, vector<string> aDictionary)
{
    ifstream inStream;
    inStream.open(filename);
    string dictword;
    while (!getline(inStream, dictword).eof())
    {
        aDictionary.push_back(dictword);
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

void boardSize(Board aBoard)
{
    cout << "Insert board length" << endl;
    int length = sizeValidator();
    aBoard.setSizeX(length);
    cout << "Insert board wideness" << endl;
    int width = sizeValidator();
    aBoard.setSizeY(width);
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

void exportBoard(vector<string> pos, vector<string> orientação, vector<string> palavras)
 {
    ofstream outfile("board.txt");
    for(int i=0; i< palavras.size(); i++)
    {
        outfile << pos[i] << " " << orientação[i] << " " << palavras[i] << endl;
    }
    outfile.close();
    cout << "Your board is now stored at board.txt" << endl;
}