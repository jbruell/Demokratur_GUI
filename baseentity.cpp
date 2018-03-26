#include "baseentity.h"

BaseEntity::BaseEntity() {}

BaseEntity::~BaseEntity() {}

void BaseEntity::setPosition(std::shared_ptr<Position> position) {
  pos = position;
}

std::shared_ptr<Position> BaseEntity::getPosition() {
  return pos;
}
