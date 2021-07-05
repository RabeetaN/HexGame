//
// Created by Rabeeta Nasir on 12/04/2021.
//

#ifndef HEXGAMEBASECODE_SMARTPLAYER_H
#define HEXGAMEBASECODE_SMARTPLAYER_H

#endif //HEXGAMEBASECODE_SMARTPLAYER_H
#include <list>
#include <queue>
#include<stack>

using namespace std;
class SmartPlayer: public Player {
public:
    stack<Cell> n;
    int moves = 0;
    SmartPlayer(int t, string name = "Smart") : Player(t, name) {}

    void getMove(Board *board, int &x, int &y) override {
        if (moves == 0) {
            int yc = rand() % board->getBoardSize();
            x = 0;
            y = yc;
            Cell c(x, y);
            n.push(c);
            moves++;
            return;
        }
        vector<Cell> sp = board->findPath(n);
            x = sp[1].x;
            y = sp[1].y;
            n.pop();
            n.push(sp[1]);
    }

};
