#pragma once

#include <iostream>
#include "Constants.h"
class BoardManager
{
private:
	char m_Board[NUM_SQUARES];
public:
	BoardManager();
	~BoardManager();
	void initBoard();
	bool isMoveLegal(int move);
	bool isMoveLegalOnBoard(const char* board, int move);
	void displayBoard();
	char winner();
	char boardWinner(const char* board);
	void markBoard(int index, char sign);
	char getBoardElement(int index);
};