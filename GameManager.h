#pragma once

#include "Difficulty.h"
#include "BoardManager.h"
#include "ComputerAI.h"
#include "ComputerEasy.h"
#include "ComputerNormal.h"
#include "ComputerHard.h"

class GameManager
{
private:
	int m_Difficulty;
	int m_Move;
	bool m_IsPlaying;
	bool m_bGameLoopFlag;
	bool m_IsAgainstPlayer;
	char m_Player;
	char m_Computer;
	char m_GameTurn;
	ComputerAI* pComputerAI;

	int askNumber(string text, int high, int low = 1);
	char askYesNo(string question);
	void showInstruction();
	void showMenu();
	void askDifficulty();
	void askPlayerTurn();
	void askPlayAgain();
	void announceWinner(char winner);
	char opponent(char symbol);
	void resetGame();
	void configureComputerAI();
	void playGame();

public:
	BoardManager m_BoardManager;

	GameManager();
	~GameManager();

	char getPlayerSymbol();
	char getComputerSymbol();

	void startGame();
	int askPlayerMove();
};

