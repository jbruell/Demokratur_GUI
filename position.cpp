#include "position.h"

Position::Position(int xCoordinate, int yCoordinate) {
  x = xCoordinate;
  y = yCoordinate;
}

Position::~Position() {}

int Position::getX() {
  return x;
}

int Position::getY() {
  return y;
}

void Position::setBaseEntity(std::shared_ptr<BaseEntity> baseEntity) {
  be = baseEntity;
}

std::shared_ptr<BaseEntity> Position::getBaseEntity() {
  return be;
}

std::shared_ptr<Position> Position::getNorth() {
  return north;
}

std::shared_ptr<Position> Position::getSouth() {
  return south;
}

std::shared_ptr<Position> Position::getEast() {
  return east;
}

std::shared_ptr<Position> Position::getWest() {
  return west;
}

void Position::setNorth(std::shared_ptr<Position> pos) {
  north = pos;
}

void Position::setSouth(std::shared_ptr<Position> pos) {
  south = pos;
}

void Position::setEast(std::shared_ptr<Position> pos) {
  east = pos;
}

void Position::setWest(std::shared_ptr<Position> pos) {
  west = pos;
}