#ifndef BOARD_H
#define BOARD_H

#include <Windows.h>
#include <citizen.h>
#include <encounter.h>
#include <stdlib.h>
#include <time.h>
#include <QObject>
#include <iostream>
#include <stdexcept>
#include <string>

class Board : public QObject {
  Q_OBJECT

 private:
  Encounter* encounter;
  Citizen* citizens;
  int talkingMode;
  int xDim;
  int yDim;
  void printVillage();

 public:
  Board();
  Board(int x,
        int y,
        int share1,
        int share2,
        int share3,
        int share4,
        int talkMode);
  ~Board();
  void setParties(int share1, int share2, int share3, int size);
  void prepareEncounter(int talkMode);
  void setXDim(int x);
  void setYDim(int y);
  int getXDim();
  int getYDim();
  Citizen* getCitizens();
  void reset(int x,
             int y,
             int share1,
             int share2,
             int share3,
             int share4,
             int talkMode);
  bool isDictatorship();
};

#endif  // BOARD_H
