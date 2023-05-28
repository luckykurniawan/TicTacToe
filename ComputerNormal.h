#pragma once

#include "ComputerAI.h"

class GameManager;

class ComputerNormal : public ComputerAI
{
private:
	GameManager& rGameManager;
public:
	ComputerNormal(GameManager& _rGameManager);
	virtual ~ComputerNormal();
	int move() override;
};

