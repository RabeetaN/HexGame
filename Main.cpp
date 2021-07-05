/*
 * Main.cpp
 *
 *  Created on: 21/02/2021
 *      Author: Rabeeta Nasir
 *
 *      I hereby certify that no other part of this submission has been copied from any other
        sources, including the Internet, books or other student’s work except the ones I have
        listed below. No part of the code has been written/produced for me by another person
        or copied from any other source.
        I hold a copy of this assignment that I can produce if the original is lost or damaged
 */

#include<iostream>
#include<string>

using namespace std;

#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"
#include "HexGame.h"
#include <time.h>

int main() {
    srand(time(0));

    int boardSize = 5;
	cout <<"Input the size of board:" << endl;
    cin >> boardSize;
	if (boardSize < 3)
		boardSize = 3;
    char a, b;
    Board *board = new Board(boardSize);

    Player *p1 = new HumanPlayer(1, "Human (Red)");
    Player *p2 = new RandomPlayer(-1, "Random (Blue)");
    Player *p3 = new RandomPlayer(1, "Random (red)");
    Player *p4 = new SmartPlayer(1, "Smart (Red)");

    cout <<"Choose two players from: Human(h), Random(r), Smart(s)" << endl;
    cin >> a >> b;
    if (a == 'h' && b == 'r'){
        HexGame game(board, p1, p2);
        game.play();
    }
    else if (a == 'r' && b == 'r'){
        HexGame game(board, p2, p3);
        game.play();
    }

	delete board;
	delete p1;
	delete p2;
    delete p3;
    delete p4;

//	system("pause");
	return 0;
}

