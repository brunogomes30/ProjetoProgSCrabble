#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "common.h"
#include "Word.h"
#include "Board.h"
#include <filesystem>


using namespace std;
namespace fs = std::experimental::filesystem;

bool wordIsValid(Board board, Word word)
{
    //Validate position of the word based on the size
	int endY = word.getIsHorizontal() ? word.getYPos() : word.getYPos() + word.getValue().length();
	int endX = word.getIsHorizontal() ? word.getXPos() + word.getValue().length()  : word.getXPos();

	if (word.getXPos() < 0 || word.getYPos() < 0 || endX >= board.getSizeX() || endY >= board.getSizeY())
		return false;
	
	//Validate if board is correct with the inserted word
    return board.insertWord(word) && board.checksIsValid();
}


void setPos(Word &word) {
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

string getWordOrEnd(vector<string> aDictionary)
{
    string word;
    cout << "Insert the word:" << endl;
    cin >> word;
    while (cin.fail()) {
		cin >> word;
        if (!binarySearch(aDictionary, word)) {
            cout << "That is not in our dictionary, please insert another one." << endl;
            cin >> word;
		}
		else break;
    }
    return word;
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



int sizeValidator() {
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

void boardSize(Board &board) {
    clear();
    cout << "Insert board length" << endl;
    int length = sizeValidator();
    cout << "Insert board width" << endl;
    int width = sizeValidator();
    if (length * width < 14)
    {
        cout << "You need a bigger board" << endl;
        boardSize(board);
    }
	board.reset_board(length, width);
}

string addWord(vector<string> dictionary, Board &board) {
	cout << "Insert the word you want to add" << endl;
	Word word = Word();
	word.setValue(getWordOrEnd(dictionary));
	setPos(word);
	if (wordIsValid(board, word)) {
		board.insertWord(word);
		return "Added word successfully.";
	}
	else 
		return "Couldn't add word " + word.getValue();
	
}

string remove(Board &board) {

	cout << "Insert the word you want to remove" << endl;
	Word word = Word();
	string name;

	setPos(word);

	name = board.findWord(word.getYPos(), word.getXPos(), word.getIsHorizontal()).getValue();
	word.setValue(name);

	if (board.removeWord(word))
		return "Removed succesfully.";
	else
		return "Couldn't remove word " + name + ".";
}

string moveWord(Board &board) {
	cout << "Insert the word you want to move" << endl;
	Word word = Word();
	string name;
	
	setPos(word);

	name = board.findWord(word.getYPos(), word.getXPos(), word.getIsHorizontal()).getValue();
	word.setValue(name);
	
	if (!board.removeWord(word))
		return "Word doesn't exist.";
	cout << endl;
	cout << "Insert the position values to move:" << endl;
	setPos(word);
	if (wordIsValid(board, word)) {
		board.insertWord(word);
		return "Added word successfully.";
	}
	else
		return "Couldn't add word " + word.getValue();
}
void finishBoard(Board board) {
	cout << "Enter a path with the filename of the board(with .txt extension) or just the filename(Will be saved in the default location)" << endl;
	string path;
	getline(cin, path);
	if (path.find_first_of('\\') != -1) {
		path += ".txt";
	}
	else {
		string currentPath = fs::current_path().string();
		currentPath = currentPath.substr(0, currentPath.find_last_of('\\'));
		path = "\\ScrabbleJunior\\Boards\\" +  currentPath + path + ".txt";
	}
    
	ofstream outfile(path);
	outfile << board.getSizeY() << " X " << board.getSizeX() << endl;
	vector<Word> words = board.getAllWords();
    for (Word word : words) {
        outfile << char(word.getYPos() + 'A') << char(word.getXPos() + 'a') << " " << (word.getIsHorizontal() ? 'H' : 'V') << " " << word.getValue() << endl;    }
    outfile.close();
    cout << "Your board is stored at the path:" << endl;
	cout << path << endl;
}

string getAction() {
	string action;
	cout << "Options:" << endl;
	cout << "\t 'add' - to add a word." << endl;
	cout << "\t 'remove' - to remove a word." << endl;
	cout << "\t 'move' - to move a word." << endl;
	cout << "\t 'exit' - to exit the application withouth saving." << endl;
	cout << "\t 'finish' - to finish and save the board." << endl;
	cout << "Option -> ";
	cin >> action;
	clearCin();
	while (action != "exit" && action != "add" && action != "move" && action != "remove" && action != "finish")
	{
		cout << "There is no option " << action << endl;
		cout << "Option -> ";
		cin >> action;
	}
	return action;
}

int main(){
    vector<string> dictionary;
    bool stop = false;
    Board board;
    Word newWord;
    dictFill("WORDS.txt", dictionary);
    boardSize(board);
	string output = "";
    while (!stop) {
		clear();
		cout << output << endl;
		board.printBoard();
		string action;
		action = getAction();
		if (action == "add") {
			output = addWord(dictionary, board);
		}
		else if (action == "remove") {
			output = remove(board);
		}
		else if (action == "move") {
			output = moveWord(board);
		}
		else if (action == "exit") {
			stop = true;
		}
		else if (action == "finish") {

			finishBoard(board);
			stop = true;
		}
    }
	system("pause");
    //exportBoard("board.txt");
}