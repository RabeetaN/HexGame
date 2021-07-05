/*
 * HexGame.h
 *
 *  Created on: 21/02/2021
 *      Author: Rabeeta Nasir
 */

#ifndef HEXGAME_H_
#define HEXGAME_H_

class HexGame {
private:
	Board *board;
	Player *player[2];
public:
	HexGame(Board *b, Player *p1, Player *p2) {
		board = b;
		player[0] = p1;
		player[1] = p2;
	}

	void play();
};

void HexGame::play() {
	bool won = false;
	board->printBoard();

	while (!won || !board->isFull()) {

		int playerType = board->getTurn();
		int playerIndex = (playerType == player[0]->getType()) ? 0 : 1;
		int x = -1;
		int y = -1;


        player[playerIndex]->getMove(board, x, y);
		cout << player[playerIndex]->getPlayerName() << " plays " << " ("
				<< x + 1 << ", " << y + 1 << "):" << endl;

		if (!board->addMove(playerType, x, y))
			return;

		Cell c(x, y);
        board->printNeighbour(board->neighbours(playerType, c));

        board->printBoard();
		won = board->checkWinningStatus(playerType);
        if(won == true) {
            cout << player[playerIndex]->getPlayerName() << " player wins!" << endl;
            return;
        }
	}

}

#endif /* HEXGAME_H_ */
