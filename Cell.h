//
// Created by Rabeeta Nasir on 31/03/2021.
//

#ifndef HEXGAMEBASECODE_CELL_H
#define HEXGAMEBASECODE_CELL_H

#endif //HEXGAMEBASECODE_CELL_H
using namespace std;

class Cell{
public:
    int x, y;
    Cell(int xx, int yy){
        x = xx;
        y = yy;
    }

    bool operator==(const Cell& a) const{
        if(a.x == x && a.y == y){
            return true;
        }
        else{
            return false;
        }
    }

};