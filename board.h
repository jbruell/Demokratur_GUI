#ifndef BOARD_H
#define BOARD_H

#include <Windows.h>
#include <baseentity.h>
#include <citizen.h>
#include <encounter.h>
#include <position.h>
#include <stdlib.h>
#include <time.h>
#include <QObject>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Board : public QObject {
  Q_OBJECT

 private:
  Encounter* encounter;
  Citizen* citizens;
  int talkingMode;
  int xDim;
  int yDim;
  int size;
  void initPositions();
  void initCitizens();
  void printVillage();
  void updatePos(std::shared_ptr<BaseEntity> cit,
                 std::shared_ptr<Position> pos);

  // neue version
  std::vector<std::shared_ptr<Position>> positions;
  std::vector<std::shared_ptr<BaseEntity>> entities;

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

  // neue version
  void moveWest(std::shared_ptr<BaseEntity> citizen);
  void moveEast(std::shared_ptr<BaseEntity> citizen);
  void moveNorth(std::shared_ptr<BaseEntity> citizen);
  void moveSouth(std::shared_ptr<BaseEntity> citizen);
  std::shared_ptr<Position> getPosition(int index);
  std::vector<std::shared_ptr<BaseEntity>>* getBaseEntities();
  void initEncounter(std::shared_ptr<BaseEntity> citizen);
};

#endif  // BOARD_H
