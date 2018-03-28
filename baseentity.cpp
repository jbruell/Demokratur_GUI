#include "baseentity.h"

// public methods

BaseEntity::BaseEntity() {}

BaseEntity::~BaseEntity() {}

std::shared_ptr<Position> BaseEntity::getPosition() {
  return pos;
}

void BaseEntity::setPosition(std::shared_ptr<Position> position) {
  pos = position;
}

QBrush* BaseEntity::getBrush() {
  return brush;
}

void BaseEntity::setBrush(QBrush* pBrush) {
  brush = pBrush;
}

bool BaseEntity::isCitizen() {
  return citizen;
}

void BaseEntity::setCitizen(bool cit) {
  citizen = cit;
}
