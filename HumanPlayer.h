/*
 * HumanPlayer.h
 *
 *  Created on: 21/02/2021
 *      Author: Rabeeta Nasir
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

using namespace std;

class HumanPlayer: public Player {
public:
	HumanPlayer(int t, string name = "Human") :
			Player(t, name) {
	}
	void getMove(Board*, int&, int&);
};

void HumanPlayer::getMove(Board *board, int &x, int &y) {
	bool flag = false;
	int bs = board->getBoardSize();

	while (!flag) {
		cout << "Input row and column (x, y) between 1 to " << bs << " for "
				<< name << " player:" << endl;
		int row, col;
		cin >> row >> col;
		x = row - 1;
		y = col - 1;
		flag = board->validInput(x,
                           y);
		if (!flag)
			cout << "Invalid input! Please input again." << endl;
	}

	return;
}

#endif /* HUMANPLAYER_H_ */
