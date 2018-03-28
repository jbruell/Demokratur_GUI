#include "baseentity.h"

BaseEntity::BaseEntity() {}

BaseEntity::~BaseEntity() {}

void BaseEntity::setPosition(std::shared_ptr<Position> position) {
  pos = position;
}

std::shared_ptr<Position> BaseEntity::getPosition() {
  return pos;
}

void BaseEntity::setBrush(QBrush* pBrush) {
  brush = pBrush;
}

QBrush* BaseEntity::getBrush() {
  return brush;
}

bool BaseEntity::isCitizen() {
  return citizen;
}

void BaseEntity::setCitizen(bool cit) {
  citizen = cit;
}
