#ifndef POSITION_H
#define POSITION_H

#include <headers.h>
#include <memory>

class BaseEntity;

class Position {
 private:
  int x;
  int y;
  std::shared_ptr<BaseEntity> be;
  std::shared_ptr<Position> north;
  std::shared_ptr<Position> south;
  std::shared_ptr<Position> east;
  std::shared_ptr<Position> west;

 public:
  Position(int xCoordinate, int yCoordinate);
  ~Position();
  int getX();
  int getY();
  std::shared_ptr<BaseEntity> getBaseEntity();
  void setBaseEntity(std::shared_ptr<BaseEntity> baseEntity);
  std::shared_ptr<Position> getNorth();
  std::shared_ptr<Position> getSouth();
  std::shared_ptr<Position> getEast();
  std::shared_ptr<Position> getWest();
  void setNorth(std::shared_ptr<Position> pos);
  void setSouth(std::shared_ptr<Position> pos);
  void setEast(std::shared_ptr<Position> pos);
  void setWest(std::shared_ptr<Position> pos);
};

#endif  // POSITION_H
