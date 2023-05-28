#include "ComputerEasy.h"

ComputerEasy::ComputerEasy() : m_mt(m_rd()),
ComputerAI({ 0,1,2,3,4,5,6,7,8 }) 
{}

ComputerEasy::~ComputerEasy() {}

int ComputerEasy::move() {
    //delete last player move from valid move list
    //won't delete anything if player moves second (last move still set to -1)
    deleteMove(lastPlayerMove);
    //select move randomly
    uniform_int_distribution<int> dist(0, m_ValidMove.size() - 1);
    int index = dist(m_mt);
    int move = m_ValidMove[index];
    //delete AI move from valid move list
    m_ValidMove.erase(m_ValidMove.begin() + index);
    return move;
}