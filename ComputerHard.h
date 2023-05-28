#pragma once

#include "ComputerAI.h"

class GameManager;

class ComputerHard : public ComputerAI
{
private:
	GameManager& rGameManager;
	char m_ComputerSymbol;
	char m_PlayerSymbol;
	int findBestMove(char* board, vector<int> validMoves);
	int minimax(char* board, vector<int> validMoves, int depth, bool isMax, int alpha, int beta);
	int evaluate(const char* board, int depth);
public:
	ComputerHard(GameManager& _rGameManager);
	virtual ~ComputerHard();
	int move() override;
};

