#pragma once
#include <random>
#include "ComputerAI.h"

class ComputerEasy : public ComputerAI 
{
private:
	random_device m_rd;
	mt19937 m_mt;
public:
	ComputerEasy();
	virtual ~ComputerEasy();
	int move() override;
};

