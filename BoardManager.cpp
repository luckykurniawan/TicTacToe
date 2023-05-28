#include "BoardManager.h"

BoardManager::BoardManager() {
	initBoard();
}

BoardManager::~BoardManager() {
}

void BoardManager::initBoard() {
	for (size_t i = 0; i < NUM_SQUARES; i++)
		m_Board[i] = EMPTY;
}

bool BoardManager::isMoveLegal(int move) {
	return isMoveLegalOnBoard(m_Board, move);
}

bool  BoardManager::isMoveLegalOnBoard(const char* board, int move) {
	return board[move] == EMPTY;
}

void BoardManager::displayBoard() {
	system("cls");
	cout << "\n\n\t   Tic Tac Toe\n\n\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << ((m_Board[0] == EMPTY) ? '1' : m_Board[0]) << "  |  " << ((m_Board[1] == EMPTY) ? '2' : m_Board[1]) << "  |  " << ((m_Board[2] == EMPTY) ? '3' : m_Board[2]) << '\n';
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << ((m_Board[3] == EMPTY) ? '4' : m_Board[3]) << "  |  " << ((m_Board[4] == EMPTY) ? '5' : m_Board[4]) << "  |  " << ((m_Board[5] == EMPTY) ? '6' : m_Board[5]) << '\n';
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << ((m_Board[6] == EMPTY) ? '7' : m_Board[6]) << "  |  " << ((m_Board[7] == EMPTY) ? '8' : m_Board[7]) << "  |  " << ((m_Board[8] == EMPTY) ? '9' : m_Board[8]) << '\n';
	cout << "\t     |     |     \n\n";
}

char BoardManager::winner() {
	return boardWinner(m_Board);
}

char  BoardManager::boardWinner(const char* board) {
	for (size_t row = 0; row < 8; row++)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
			return board[WINNING_ROWS[row][0]];
		}
	}

	if (std::count(board, board + NUM_SQUARES, EMPTY) == 0)
		return TIE;

	return NO_ONE;
}


void BoardManager::markBoard(int index, char sign) {
	m_Board[index] = sign;
}

char BoardManager::getBoardElement(int index) {
	return m_Board[index];
}