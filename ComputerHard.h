#pragma once

#include "ComputerAI.h"
#include <random>

class GameManager;

class ComputerHard : public ComputerAI
{
private:
	GameManager& rGameManager;
	char m_ComputerSymbol;
	char m_PlayerSymbol;
	bool mIsFirstMove;
	int findBestMove(char* board, vector<int> validMoves);
	int minimax(char* board, vector<int> validMoves, int depth, bool isMax, int alpha, int beta);
	int evaluate(const char* board, int depth);
	int getFirstMove();
public:
	ComputerHard(GameManager& _rGameManager);
	virtual ~ComputerHard();
	int move() override;
};

