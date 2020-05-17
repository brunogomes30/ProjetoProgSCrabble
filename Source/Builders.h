#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "common.h"
#include "Word.h"
#include "Board.h"


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