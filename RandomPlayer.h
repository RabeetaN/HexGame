//
// Created by Rabeeta Nasir on 24/03/2021.
//

#ifndef HEXGAMEBASECODE_RANDOMPLAYER_H
#define HEXGAMEBASECODE_RANDOMPLAYER_H

#endif //HEXGAMEBASECODE_RANDOMPLAYER_H
using namespace std;

class RandomPlayer: public Player {
public:
    RandomPlayer(int t, string name = "Random") : Player(t, name){}
    void getMove(Board *board, int &x, int &y) override {
        int index = rand() % board->emptyCells.size();
        auto it = board->emptyCells.begin();
        advance(it, index);
        x = it->x;
        y = it->y;
        return;
    }
};