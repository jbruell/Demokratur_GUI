#ifndef BOARD_H
#define BOARD_H

#include <barrier.h>
#include <baseentity.h>
#include <citizen.h>
#include <encounter.h>
#include <position.h>
#include <QObject>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class Board : public QObject {
  Q_OBJECT

 private:
  int xDim;
  int yDim;
  int size;
  Encounter* encounter;
  std::vector<std::shared_ptr<Position>> positions;
  std::vector<std::shared_ptr<BaseEntity>> entities;

  void initPositions();
  void initCitizens(int persons);
  void initBarriers();
  void updatePos(std::shared_ptr<BaseEntity> cit,
                 std::shared_ptr<Position> pos);
  void initEncounter(std::shared_ptr<BaseEntity> citizen);

 public:
  Board(int x, int y, int persons);
  ~Board();
  int getXDim();
  void setXDim(int x);
  int getYDim();
  void setYDim(int y);
  int getSize();
  std::shared_ptr<Position> getPosition(int index);
  std::vector<std::shared_ptr<BaseEntity>>* getBaseEntities();

  void moveWest(std::shared_ptr<BaseEntity> citizen);
  void moveEast(std::shared_ptr<BaseEntity> citizen);
  void moveNorth(std::shared_ptr<BaseEntity> citizen);
  void moveSouth(std::shared_ptr<BaseEntity> citizen);
  void reset(int x, int y, int persons);
  void resetTalkingStatus();
  bool isDictatorship();
};

#endif  // BOARD_H
