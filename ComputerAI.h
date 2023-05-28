#pragma once
#include <vector>
#include <algorithm>
#include "Constants.h"

class ComputerAI {
protected:
	int lastPlayerMove = -1; //set to -1 to prevent AI deleting any move if AI moves first
	std::vector<int> m_ValidMove;
	std::vector<int>::iterator m_Iterator;
public:
	virtual int move() { return 0; };
	ComputerAI(std::vector<int> _validMove): m_ValidMove(_validMove){}
	virtual ~ComputerAI() {
		m_ValidMove.clear();
	};
	void setLastPlayerMove(int lastMove) {
		lastPlayerMove = lastMove;
	}
	void deleteMove(int move) {
		m_Iterator = find(m_ValidMove.begin(), m_ValidMove.end(), move);
		if (m_Iterator != m_ValidMove.end()) {
			m_ValidMove.erase(m_Iterator);
		}
	}
};