#include <iostream>
#include <fstream>
#include "common.h"
#include "Word.h"
#include "Colors.h"
#include "Board.h"

using namespace std;

int main()
{
    Board newboard;
    boardsize();
    insertwords();
    exportboard();
    

}


void insertwords()
{
    cout << "insert a word you wish to put on the board or \"stop\" if you wish to terminate the board creation, you can also insert all position, direction and name at once (ex: Ak H eggs)";
    string newword;
    string orientation;
    cin >> newword;
    while (cin.fail() || !indict() || !isvalid())
    {
        if (cin.fail())
        {
            clearCin();
            cout << "please insert a string";
            cin >> newword;
        }
        if (!indict())
        {
            cout << "that string is not in our dictionary";
            cin >> newword;
        }
        if (!isvalid())
        {
            cout << "that word is not valid, ";//explicar pq
        }
    cout << "what is the orientation of that word? (horizontal or vertical)"
    cin >> orientaion;
    {

    }
    }
}

bool indict()
{
    ifstream inStream;
    inStream.open("WORDS.txt");
    bool wordfound = false;
    while (!eof() & !wordfound)
    {
        //next line
    }
}

void boardsize()
{
    cout << "Insert board length";
    int length = sizevalidator();
    newboard.setSizeX(length);
    cout << "Insert board wideness";
    int width = sizevalidator();
    newboard.setSizeY(width);
}

int sizevalidator()
{
	int theinput;
	cin >> theinput;
	while ((cin.fail() || (theinput < 2 || theinput > 20)))
	{
		if (cin.fail())
		{
			clearCin();
			cout << "Please insert an integer";
			cin >> theinput;
		}
        if (theinput < 2 || theinput > 20)
        {
            clearCin();
            cout << "Please insert an integer from 2 to 20";
            cin >> theinput;
        }
    }
}

void exportboard()
{
    ofstream outfile("board.txt");
    for(int i=0; i< wordsnum; i++)
    {
        outfile << posicions[i]<< directions[i] << " " << words[i] << endl;
    }
    outfile.close();
}