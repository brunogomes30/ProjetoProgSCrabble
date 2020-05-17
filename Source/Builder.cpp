#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "common.h"
#include "Word.h"
#include "Board.h"



using namespace std;

bool advancedValidator(vector<string> wordsVector, Board aBoard, Word aword)
{
    string astr;
    vector<string> newVector;
    int k;
    vector<string> wordsv2 = wordsVector;
    wordsv2.push_back(aword.getValue());
    for (int i = 0; i < aBoard.getSizeX(); i++) {
        for (int j = 0; j < aBoard.getSizeY(); j++)
        {
            if (aBoard.getField()[aword.getXPos()][aword.getYPos() - 1]->getValue() == ' ' && aBoard.getField()[aword.getXPos()][aword.getYPos() + 1]->getValue() != ' ')
            {
                k = 1;
                astr = "";
                while (aBoard.getField()[aword.getXPos()][aword.getYPos() + k]->getValue() != ' ')
                {
                    astr.push_back(aBoard.getField()[aword.getXPos() + k][aword.getYPos()]->getValue());
                    k++;
                }
            }
            newVector.push_back(astr);


            if (aBoard.getField()[aword.getXPos() - 1][aword.getYPos()]->getValue() == ' ' && aBoard.getField()[aword.getXPos() + 1][aword.getYPos() + 1]->getValue() != ' ')
            {
                astr = "";
                k = 1;
                while (aBoard.getField()[aword.getXPos() + k][aword.getYPos()]->getValue() != ' ')
                {
                    astr.push_back(aBoard.getField()[aword.getXPos() + k][aword.getYPos()]->getValue());
                    k++;
                }
            }
            newVector.push_back(astr);
        }
    }
    sort(newVector.begin(), newVector.end());
    sort(wordsv2.begin(), wordsv2.end());
    if (newVector != wordsv2)
    {
        return false;
    }
    return true;
}

bool wordIsValid(Board aboard, Word aword, vector<string> wordsVector)
{
    if (aword.getXPos() > aboard.getSizeX() || aword.getYPos() > aboard.getSizeY())
    {
        return false;
    }
    if (aword.getIsHorizontal())
    {
        if (aword.getXPos() + aword.getValue().size() > (size_t)aboard.getSizeX())
        {
            return false;
        }
        for(size_t i=0; i<aword.getValue().size(); i++)
        {
            if (aword.getValue()[i] != aboard.getField()[aword.getXPos()+i][aword.getYPos()]->getValue())
            {
                return false;
            }
        }
    }
    else 
    {
        if (aword.getYPos() + aword.getValue().size() > (size_t)aboard.getSizeY())
        {
            return false;
        }
        for(size_t i=0; i<aword.getValue().size(); i++)
        {
            if (aword.getValue()[i] != aboard.getField()[aword.getXPos()][aword.getYPos()+1]->getValue())
            {
                return false;
            }
        }
    }
    advancedValidator(wordsVector, aboard, aword);
}


void setPos(Word aWord)
{
    string xpos;
    char ypos;
    clear();
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
            cout << "That was not a valid letter of the y axis of the board." << endl;
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


bool binarySearch(vector<string> vector, string word)
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

string getWordOrEnd(vector<string> aDictionary, bool endingBool)
{
    string aWord;
    cout << "Insert a word you would want to put on the board or type \"stopandstore\" if you want to terminate the board creation, " << endl;
    cin >> aWord;
    if (aWord == "stopandstore")
    {
        endingBool = true;
    }
    while ((cin.fail() || !binarySearch(aDictionary, aWord)) && !endingBool)
    {
        if (cin.fail())
        {
            clearCinStr();
            cin >> aWord;
        }
        if (!binarySearch(aDictionary, aWord))
        {
            cout << "That is not in our dictionary, please insert another one." << endl;
            cin >> aWord;
        }
    }
    return aWord;
}

bool streamlineOrientation(string theorientation)
{
    return !(theorientation == "v" || theorientation == "V" || theorientation == "Vertical" || theorientation == "vertical");
}

bool validOrientation(string theorientation)
{
    return (theorientation == "v" || theorientation == "V" || theorientation == "h" || theorientation == "H" || theorientation == "Vertical" || theorientation == "Horizontal" || theorientation == "vertical" || theorientation == "horizontal");
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



void dictFill(string filename, vector<string> aDictionary)
{
    ifstream inStream;
    inStream.open(filename);
    string dictword;
    if (!inStream.is_open())
    {
        cout << "Failed to open " << filename << endl;
    }
    while (getline(inStream, dictword))//(!inStream.eof())
    {
        cout << dictword;
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

void boardSize(Board aBoard)
{
    clear();
    cout << "Insert board length" << endl;
    int length = sizeValidator();
    cout << "Insert board wideness" << endl;
    int width = sizeValidator();
    if (length * width < 14)
    {
        cout << "You need a bigger board" << endl;
        boardSize(aBoard);
    }
    aBoard.setSizeX(length);
    aBoard.setSizeY(width);
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
    while (!stop)
    {
        newWord.setValue(getWordOrEnd(dictionary, stop));
        if (newWord.getValue() == "stopandstore")
        {
            stop = true;
        }
        else
        {
            newboard.printBoard();
            newWord.setIsHorizontal(getOrientation());
            setPos(newWord);
            if (wordIsValid(newboard, newWord, words))
            {
                newboard.insertWord(newWord);
                saveword(newWord, orientations, words, posicions);
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