#include "ComputerNormal.h"
#include "GameManager.h"

ComputerNormal::ComputerNormal(GameManager& _rGameManager) : 
	rGameManager(_rGameManager),
    ComputerAI({ 4,0,2,6,8,1,3,5,7 })
{}

ComputerNormal::~ComputerNormal() {
	m_ValidMove.clear();
}

int ComputerNormal::move() {
    //delete last player move from valid move list
    //won't delete anything if player moves second (last move still set to -1)
    deleteMove(lastPlayerMove);

    //copy board
    char board[NUM_SQUARES];
    int move = -1;
	for (size_t i = 0; i < NUM_SQUARES; i++)
	{
		board[i] = rGameManager.m_BoardManager.getBoardElement(i);
	}

    //check next move
    char computer = rGameManager.getComputerSymbol();
    char player = rGameManager.getPlayerSymbol();
    for (unsigned int index = 0; index < m_ValidMove.size(); index++)
    {
        //if computer can win on next move, make that move
        board[m_ValidMove[index]] = computer;
        if (rGameManager.m_BoardManager.boardWinner(board) == computer) {
            move = m_ValidMove[index];
            //delete AI move from valid move list
            m_ValidMove.erase(m_ValidMove.begin() + index);
            return move;
        }
        //if player can win on next move, block that move
        board[m_ValidMove[index]] = player;
        if (rGameManager.m_BoardManager.boardWinner(board) == player) {
            move = m_ValidMove[index];
            //delete AI move from valid move list
            m_ValidMove.erase(m_ValidMove.begin() + index);
            return move;
        }
        // done checking this move, undo it
        board[m_ValidMove[index]] = EMPTY;
    }

    //since no one can win on the next move, pick best open square
    move = m_ValidMove[0];
    m_ValidMove.erase(m_ValidMove.begin());

    return move;
}