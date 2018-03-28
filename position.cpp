#include "position.h"

// public methods

Position::Position(int xCoordinate, int yCoordinate) {
  x = xCoordinate;
  y = yCoordinate;
  occupied = false;
}

Position::~Position() {}

int Position::getX() {
  return x;
}

int Position::getY() {
  return y;
}

bool Position::isOccupied() {
  return occupied;
}

std::shared_ptr<BaseEntity> Position::getBaseEntity() {
  return be;
}

void Position::setBaseEntity(std::shared_ptr<BaseEntity> baseEntity) {
  be = baseEntity;
  occupied = baseEntity != NULL;
}

std::shared_ptr<Position> Position::getNorth() {
  return north;
}

void Position::setNorth(std::shared_ptr<Position> pos) {
  north = pos;
}

std::shared_ptr<Position> Position::getSouth() {
  return south;
}

void Position::setSouth(std::shared_ptr<Position> pos) {
  south = pos;
}

std::shared_ptr<Position> Position::getEast() {
  return east;
}

void Position::setEast(std::shared_ptr<Position> pos) {
  east = pos;
}

std::shared_ptr<Position> Position::getWest() {
  return west;
}

void Position::setWest(std::shared_ptr<Position> pos) {
  west = pos;
}
