#ifndef BOARD_H
#define BOARD_H

#include <Windows.h>
#include <barrier.h>
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
  int xDim;
  int yDim;
  int size;
  void initPositions();
  void initCitizens(int persons);
  void initBarriers();
  void printVillage();
  void updatePos(std::shared_ptr<BaseEntity> cit,
                 std::shared_ptr<Position> pos);

  // neue version
  std::vector<std::shared_ptr<Position>> positions;
  std::vector<std::shared_ptr<BaseEntity>> entities;

 public:
  Board();
  Board(int x, int y, int persons);
  ~Board();
  void setXDim(int x);
  void setYDim(int y);
  int getXDim();
  int getYDim();
  void reset(int x, int y, int persons);
  bool isDictatorship();

  // neue version
  void moveWest(std::shared_ptr<BaseEntity> citizen);
  void moveEast(std::shared_ptr<BaseEntity> citizen);
  void moveNorth(std::shared_ptr<BaseEntity> citizen);
  void moveSouth(std::shared_ptr<BaseEntity> citizen);
  std::shared_ptr<Position> getPosition(int index);
  std::vector<std::shared_ptr<BaseEntity>>* getBaseEntities();
  void initEncounter(std::shared_ptr<BaseEntity> citizen);
  void resetTalkingStatus();
};

#endif  // BOARD_H
