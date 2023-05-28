#include "GameManager.h"

GameManager::GameManager() :
	m_Difficulty(0), 
	m_Move(0), 
	m_IsPlaying(true), 
	m_bGameLoopFlag(true),
	m_IsAgainstPlayer(false), 
	m_Player('*'), 
	m_Computer('*'), 
	m_GameTurn('X'), 
	pComputerAI(0) 
{}

GameManager::~GameManager() {}

char GameManager::getPlayerSymbol() {
	return m_Player;
}
char GameManager::getComputerSymbol() {
	return m_Computer;
}

int GameManager::askNumber(string text, int high, int low) {
	int number = 0;
	cout << text << " (" << low << " - " << high << "): ";
	cin >> number;
	while (cin.fail() || number > high || number < low)
	{
		if (cin.fail()) {
			cout << "Please input only numbers." << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			number = 0;
		}
		else if (number > high || number < low) {
			cout << "Please input numbers between " << low << " and " << high << ".\n";
		}
		
		cout << text << " (" << low << " - " << high << "): ";
		cin >> number;
	}
	return number;
}

char GameManager::askYesNo(string question) {
	char answer;
	do
	{
		cout << question << " (y/n): ";
		cin >> answer;
	} while (answer != 'y' && answer != 'n');
	return answer;
}

void GameManager::showInstruction() {
	system("cls");
	cout << "Make your move known by entering a number, 1-9. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << "\t     |     |     \n";
	cout << "\t  1  |  2  |  3  \n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  4  |  5  |  6  \n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  7  |  8  |  9  \n\n";
}

void GameManager::showMenu() {
	string question = "Menu\n1 - Play against player\n2 - Play against computer\n3 - Quit\n";
	int choice = askNumber(question, 3);
	switch (choice)
	{
	case 1:
		m_IsAgainstPlayer = true;
		m_IsPlaying = true;
		break;
	case 2:
		m_IsAgainstPlayer = false;
		m_IsPlaying = true;
		break;
	case 3:
		m_IsPlaying = false;
		m_bGameLoopFlag = false;
		break;
	default:
		break;
	}
}

void GameManager::askDifficulty() {
	string question = "Choose the difficulty\n1 - Easy\n2 - Normal\n3 - Hard\n";
	m_Difficulty = askNumber(question, 3);
}

/// <summary>
/// ask if player wants to go first or not, 
/// </summary>
/// <returns>X if first</returns>
void GameManager::askPlayerTurn() {
	char answer = askYesNo("Do you want to go first?");
	if (answer == 'y') m_Player = X;
	else m_Player = O;
	m_Computer = opponent(m_Player);
}

void GameManager::askPlayAgain() {
	char answer = askYesNo("Do you want to play again?");
	if (answer == 'n') m_IsPlaying = false;
}

void GameManager::announceWinner(char winner) {
	if (winner != TIE) cout << winner << "'s won.\n";
	else cout << "It's a tie\n";
}

/// <summary>
/// set computer's symbol according to player symbol
/// </summary>
/// <param name="symbol">player's symbol</param>
/// <returns>O if player's symbol is X and vice versa</returns>
char GameManager::opponent(char symbol) {
	if (symbol == X) return O;
	else return X;
}

void GameManager::resetGame() {
	m_GameTurn = 'X';
	m_Move = 0;
}

void GameManager::configureComputerAI() {
	switch (m_Difficulty)
	{
	case Easy:
		pComputerAI = new ComputerEasy();
		break;
	case Normal:
		pComputerAI = new ComputerNormal(*this);
		break;
	case Hard:
		pComputerAI = new ComputerHard(*this);
		break;
	default:
		break;
	}
}

void GameManager::playGame() {
	resetGame();
	m_BoardManager.initBoard();
	m_BoardManager.displayBoard();
	while (m_BoardManager.winner() == NO_ONE)
	{
		if (m_GameTurn == m_Computer && !m_IsAgainstPlayer)
		{
			m_BoardManager.markBoard(pComputerAI->move(), m_Computer);
		}
		else {
			//if playing against player show whose turn it is
			if (m_IsAgainstPlayer)
				cout << m_GameTurn << "'s turn.\n";

			m_Move = askPlayerMove();
			if (!m_IsAgainstPlayer) {
				m_BoardManager.markBoard(m_Move, m_Player);
				pComputerAI->setLastPlayerMove(m_Move);
			}
			else {
				m_BoardManager.markBoard(m_Move, m_GameTurn);
			}		
		}
		m_BoardManager.displayBoard();
		m_GameTurn = opponent(m_GameTurn);
	}
	announceWinner(m_BoardManager.winner());
	if (!m_IsAgainstPlayer) {
		delete pComputerAI;
		pComputerAI = 0;
	}
}

void GameManager::startGame() {
	while (m_bGameLoopFlag) {
		showInstruction();
		showMenu();
		while (m_IsPlaying) {
			if (!m_IsAgainstPlayer)
			{
				askDifficulty();
				askPlayerTurn();
				configureComputerAI();
			}		
			playGame();
			askPlayAgain();
		}
	}
}

int GameManager::askPlayerMove() {
	int move = askNumber("Enter a number : ", NUM_SQUARES) - 1;
	while (!m_BoardManager.isMoveLegal(move))
	{
		cout << "That square is already occupied\n";
		move = askNumber("Enter a number : ", NUM_SQUARES) - 1;
	}
	return move;
}
