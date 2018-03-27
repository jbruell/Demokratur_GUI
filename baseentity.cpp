#include "baseentity.h"

BaseEntity::BaseEntity() {}

BaseEntity::~BaseEntity() {}

void BaseEntity::setPosition(std::shared_ptr<Position> position) {
  pos = position;
}

std::shared_ptr<Position> BaseEntity::getPosition() {
  return pos;
}

void BaseEntity::setColor(QColor col) {
  color = col;
}

QColor BaseEntity::getColor() {
  return color;
}

bool BaseEntity::isCitizen() {
  return citizen;
}

bool BaseEntity::setCitizen(bool cit) {
  citizen = cit;
}
