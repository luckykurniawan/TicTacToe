#include "ComputerHard.h"
#include "GameManager.h"

ComputerHard::ComputerHard(GameManager& _rGameManager):
    rGameManager(_rGameManager),
    ComputerAI({ 0,1,2,3,4,5,6,7,8 }),
    m_ComputerSymbol(rGameManager.getComputerSymbol()),
    m_PlayerSymbol(rGameManager.getPlayerSymbol())
{}

ComputerHard::~ComputerHard() {}

int ComputerHard::move() {
    //delete last player move from valid move list
    //won't delete anything if player moves second (last move still set to -1)
    deleteMove(lastPlayerMove);

    //copy board
    char board[NUM_SQUARES];
    for (size_t i = 0; i < NUM_SQUARES; i++)
    {
        board[i] = rGameManager.m_BoardManager.getBoardElement(i);
    }
    //decide move
    int move = findBestMove(board, m_ValidMove);
    //delete move from list of valid moves
    deleteMove(move);
    return move;
}

/// <summary>
/// return best move for the computer
/// </summary>
/// <param name="board">current state of the board</param>
/// <param name="validMoves">moves that can still be used</param>
/// <returns>board position (index) for the best move</returns>
int ComputerHard::findBestMove(char* board, vector<int> validMoves) {
    int bestVal = INT_MIN;
    int bestMove = -1;
    //check all moves that can still be used
    for (int i = 0; i < validMoves.size(); i++)
    {
        //make the move
        int move = validMoves.at(i);
        board[move] = m_ComputerSymbol;
        //delete from list of valid moves
        validMoves.erase(validMoves.begin() + i);
        //compute value for that move
        char changedBoard[NUM_SQUARES];
        for (size_t i = 0; i < NUM_SQUARES; i++)
        {
            changedBoard[i] = board[i];
        }
        //compute value for this move
        int moveVal = minimax(changedBoard, validMoves, 0, false, INT_MIN, INT_MAX);
        //undo the move
        board[move] = EMPTY;
        //readd move to list of valid moves
        validMoves.insert(validMoves.begin() + i, move);

        //if the value of that move is more than best value, update best move and value
        if (moveVal > bestVal) {
            bestMove = move;
            bestVal = moveVal;
        }
    }

    return bestMove;
}

/// <summary>
/// minimax function
/// </summary>
/// <param name="board">current state of the board</param>
/// <param name="validMoves">moves that can still be used</param>
/// <param name="depth">current tree branch depth</param>
/// <param name="isMax">is current move maximizing computer</param>
/// <param name="alpha">maximizer best move value until now</param>
/// <param name="beta">minimizer best move value until now</param>
/// <returns></returns>
int ComputerHard::minimax(char* board, vector<int> validMoves, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board, depth);

    if (score != INT_MIN)
        return score;

    if (validMoves.empty())
        return 0;

    //maximizing computer move
    if (isMax) {
        int best = INT_MIN;
        //check all moves that can still be used
        for (int i = 0; i < validMoves.size(); i++)
        {
            //make the move
            int move = validMoves.at(i);
            board[move] = m_ComputerSymbol;
            //delete from list of valid moves
            validMoves.erase(validMoves.begin() + i);
            //compute value for this move
            char changedBoard[NUM_SQUARES];
            for (size_t i = 0; i < NUM_SQUARES; i++)
            {
                changedBoard[i] = board[i];
            }
            //call minimax recursively and choose the maximum value
            best = max(best, minimax(changedBoard, validMoves, depth + 1, false, alpha, beta));
            //undo the move
            board[move] = EMPTY;
            //readd move to list of valid moves
            validMoves.insert(validMoves.begin() + i, move);
            //store maximizer best move value until current move
            alpha = max(alpha, best);
            //alpha-beta pruning
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    }
    //minimizing
    else {
        int best = INT_MAX;
        //check all moves that can still be used
        for (int i = 0; i < validMoves.size(); i++)
        {
            //make the move
            int move = validMoves.at(i);
            board[move] = m_PlayerSymbol;
            //delete from list of valid moves
            validMoves.erase(validMoves.begin() + i);
            //compute value for this move
            char changedBoard[NUM_SQUARES];
            for (size_t i = 0; i < NUM_SQUARES; i++)
            {
                changedBoard[i] = board[i];
            }
            //call minimax recursively and choose the minimum value
            best = min(best, minimax(changedBoard, validMoves, depth + 1, true, alpha, beta));
            //undo the move
            board[move] = EMPTY;
            //readd move to list of valid moves
            validMoves.insert(validMoves.begin() + i, move);
            //store minimizer best move value until current move
            beta = min(beta, best);
            //alpha-beta pruning
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    }
}

/// <summary>
/// minimax evaluation function
/// </summary>
/// <param name="board">current state of the board</param>
/// <param name="depth">current tree branch depth</param>
/// <returns>value of that move</returns>
int ComputerHard::evaluate(const char* board, int depth) {
    for (size_t row = 0; row < 8; row++)
    {
        //check board for the winner
        if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
            (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
            (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
            //if computer win
            if (board[WINNING_ROWS[row][0]] == m_ComputerSymbol)
                return 10 - depth;
            //if player win
            else if (board[WINNING_ROWS[row][0]] == m_PlayerSymbol)
                return depth - 10;
        }
    }
    //if no one wins
    return INT_MIN;
}