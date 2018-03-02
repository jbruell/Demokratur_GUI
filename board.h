#ifndef BOARD_H
#define BOARD_H

#include <citizen.h>
#include <encounter.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <string>


class Board {
private:
    Encounter *encounter;
    Citizen *citizens;
    int talkingMode;
    int xDim;
    int yDim;
    void prepareEncounter(int talkMode);
    void printVillage();
public:
    Board();
    Board(int x, int y, int share1, int share2, int share3, int share4, int talkMode);
    void start(int iterations);
    void setXDim(int x);
    void setYDim(int y);
    int getXDim();
    int getYDim();
    Citizen* getCitizens();
};

#endif // BOARD_H
