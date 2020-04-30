// ProjetoProgSCrabble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Board.h"
#include <iostream>

int main()
{
	Board board = Board();
	board.readBoardFromFile("board1.txt");
	board.printBoard();
}
