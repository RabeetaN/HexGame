/*
 * BaseBoard.h
 *
 *  Created on: 21/02/2021
 *      Author: Rabeeta Nasir
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <windows.h>
#include<list>
#include <Cell.h>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

class Board {
private:
    int boardSize;
    int turn;
    int **grid;
    bool **visited;
public:
    list <Cell> emptyCells;

    Board(int bs) {
        boardSize = bs;
        grid = new int *[boardSize];
        for (int i = 0; i < boardSize; i++)
            grid[i] = new int[boardSize];

        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++) {
                grid[i][j] = 0;
            }
        visited = new bool *[boardSize];
        for (int i = 0; i < boardSize; i++)
            visited[i] = new bool[boardSize];

        turn = 1;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                Cell c(i, j);
                emptyCells.push_back(c);
            }
        }
    }

    virtual ~Board() {

        for (int i = 0; i < boardSize; i++)
            delete[] grid[i];

        delete[] grid;

        for (int i = 0; i < boardSize; i++)
            delete[] visited[i];

        delete[] visited;
    }

    Board(Board &cboard) {
        boardSize = cboard.getBoardSize();

        grid = new int *[boardSize];
        for (int i = 0; i < boardSize; i++)
            grid[i] = new int[boardSize];

        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                grid[i][j] = 0;

        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++) {
                grid[i][j] = cboard.getGrid(i, j);
            }

        turn = cboard.getTurn();
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                Cell c(i, j);
                emptyCells.push_back(c);
            }
        }
    }

    int getBoardSize() const {
        return boardSize;
    }

    int getGrid(int x, int y) {
        return grid[x][y];
    }

    int getTurn() const {
        return turn;
    }

    bool validInput(int, int);

    bool addMove(int playerType, int x, int y);

    void printBoard();

    char printPlayer(int);

    void redBorder() const;

    bool straightWin(int);

    stack <Cell> neighbours(int, Cell &);

    void printNeighbour(stack<Cell> n);

    bool checkWinningStatus(int player) {
        if (straightWin(player) || dfs(player)) {
            return true;
        } else {
            return false;
        }
    }

    void initialiseVisited() {
        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++) {
                visited[i][j] = false;
            }
    }

    bool atGoal(int player, Cell c) {
        if (player == 1) {
            if (c.x == boardSize - 1 && grid[c.x][c.y] == player) {
                return true;
            }
        } else if (player == -1) {
            if (c.y == boardSize - 1 && grid[c.x][c.y] == player) {
                return true;
            }
        }
        return false;
    }

    void addToStack(int player, stack <Cell> &t) {
        if (player == 1) {
            for (int i = 0; i < boardSize; i++) {
                if (grid[0][i] == player) {
                    Cell c(0, i);
                    t.push(c);
                }
            }
        }
        if (player == -1) {
            for (int i = 0; i < boardSize; i++) {
                if (grid[i][0] == player) {
                    Cell c(0, i);
                    t.push(c);
                }
            }
        }
    }

    bool dfs(int player) {
        initialiseVisited();
        stack <Cell> track;
        addToStack(player, track);
        while (!track.empty()) {
            Cell current = track.top();
            track.pop();
            if (atGoal(player, current)) {
                return true;
            } else if (!visited[current.x][current.y]) {
                visited[current.x][current.y] = true;
                stack <Cell> cellN = neighbours(player, current);
                while (!cellN.empty()) {
                    if (!visited[cellN.top().x][cellN.top().y]) {
                        track.push(cellN.top());
                    }
                    cellN.pop();
                }
            }
        }
        return false;
    }

    vector<Cell> findPath(stack<Cell> n){
        initialiseVisited();
        vector<Cell> shortestPath;
        stack <Cell> cellN;
        while (!n.empty()) {
            Cell current = n.top();
            n.pop();
            if (current.x == boardSize-1) {
                shortestPath.push_back(current);
                return shortestPath;
            }
            else {
                visited[current.x][current.y] = true;
                cellN = emptyNeighbours(current);
                while (!cellN.empty()) {
                    if (!visited[cellN.top().x][cellN.top().y]) {
                        n.push(cellN.top());
                        cellN.pop();
                    }
                    else {
                        cellN.pop();
                    }
                }
                shortestPath.push_back(current);
            }
        }
    }

    stack<Cell> emptyNeighbours(Cell &c){
        stack<Cell> n;
        for (int i = 0; i > -2; i--) {
            if ((c.x + 1) < boardSize && (c.x + 1) >= 0 && (c.y + i) >= 0 && (c.y + i) < boardSize && grid[c.x + 1][c.y + i] == 0) {
                Cell temp((c.x + 1), (c.y + i));
                n.push(temp);
            }
        }
        return n;

    }

    bool isFull() {
        return emptyCells.empty();
    }

    void removeMove(int &x, int &y) {
        Cell temp(x, y);
        emptyCells.remove(temp);
    }



};

bool Board::validInput(int x, int y) {
	if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
		cout << "Move (" << x + 1 << ", " << y + 1 << ") out of range!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	return true;
}

bool Board::addMove(int playerType, int x, int y) {

	if (playerType != turn) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	grid[x][y] = playerType;
	removeMove(x, y);

    turn = -1 * turn;
	return true;
}

bool Board:: straightWin(int player) {
    int count;
    if (player == 1) {
        for (int j = 0; j < boardSize; j++) {
            count = 0;
            for (int i = 0; i < boardSize; i++) {
                if (grid[i][j] == player) {
                    count++;
                }
            }
            if (count == boardSize) {
                return true;
            }
        }
    }
    else if (player == -1){
        for (int j = 0; j < boardSize; j++) {
            count = 0;
            for (int i = 0; i < boardSize; i++) {
                if (grid[j][i] == player) {
                    count++;
                }
            }
            if (count == boardSize) {
                return true;
            }
        }
    }
   return false;
}

stack<Cell> Board:: neighbours(int player, Cell &c){
    stack<Cell> n;
    for (int j = 1; j > -2; j--){
        for (int i = 1; i > -2; i--) {
            if (j != i && (c.x + j) < boardSize && (c.x + j) >= 0 && (c.y + i) >= 0 && (c.y + i) < boardSize && grid[c.x + j][c.y + i] == player) {
                Cell temp((c.x + j), (c.y + i));
                n.push(temp);
            }
        }
    }
    return n;
}

void Board::printNeighbour(stack<Cell> n){
    cout << "Player neighbours: ";
    while(!n.empty()){
        cout << "(" << n.top().x  + 1 << ", " << n.top().y + 1 << ")";
        n.pop();
    }
    cout << endl;
}

void Board::printBoard() {
	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		if (j < 9)
			cout << j + 1 << "   ";
		else
			cout << j + 1 << "  ";
	}
	cout << endl;

	cout << "   ";

    redBorder();

	for (int i = 0; i < boardSize; i++) {
		for (int k = 0; k < i; k++)
			cout << "  ";

		if (i < 9)
			cout << " " << i + 1 << " ";
		else
			cout << i + 1 << " ";

		for (int j = 0; j < boardSize; j++) {
			if (grid[i][j] == 0) {
				if (j == 0) {
					cout << "|   |";
				} else {
					cout << "   |";
				}
			} else if (grid[i][j] == 1) {
				if (j == 0) {
					cout << "|";
					cout << printPlayer(1) << "|";
				} else {
					cout << printPlayer(1) << "|";
				}
			} else {
				if (j == 0) {
					cout << "|";
					cout << printPlayer(-1) << "|";
				} else {
					cout << printPlayer(-1) << "|";
				}
			}
		}
		cout << endl;
	}

	for (int k = 0; k <= boardSize; k++)
		cout << "  ";

    redBorder();

	cout << endl;
}

char Board::printPlayer(int player) {
    if (player == 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << " R";
    } else if (player == -1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        cout << " B";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return ' ';
}

void Board::redBorder() const{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int j = 0; j < boardSize; j++) {
        cout << "----";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << endl;
}

#endif /* BOARD_H_ */
