#include <board.h>

Board::Board() {
  // new Board(10, 10, 25, 25 ,25, 25, 0);
}

Board::Board(int x, int y, int persons) {
  if (persons > x * y) {
    throw std::invalid_argument("Village is too small for Citizens");
  }
  encounter = new Encounter();

  xDim = x;
  yDim = y;
  size = x * y;

  // TODO init vectors & update destructor
  initPositions();
  initCitizens(persons);
}

Board::~Board() {
  delete encounter;
}

void Board::initPositions() {
  for (int i = 0; i < yDim; i++) {
    for (int j = 0; j < xDim; j++) {
      std::shared_ptr<Position> sharedPtr(new Position(j, i));
      positions.push_back(std::move(sharedPtr));
    }
  }

  for (int i = 0; i < size; i++) {
    std::shared_ptr<Position> pos = positions.at(i);
    int x = pos->getX();
    int y = pos->getY();

    // north
    if (y == 0) {
      pos->setNorth(positions.at(size - xDim + i));
    } else {
      pos->setNorth(positions.at(i - xDim));
    }

    // south
    if (y == yDim - 1) {
      pos->setSouth(positions.at(i % xDim));
    } else {
      pos->setSouth(positions.at(i + xDim));
    }

    // west
    if (x == 0) {
      pos->setWest(positions.at(i + xDim - 1));
    } else {
      pos->setWest(positions.at(i - 1));
    }

    // east
    if (x == xDim - 1) {
      pos->setEast(positions.at(i - xDim + 1));
    } else {
      pos->setEast(positions.at(i + 1));
    }
  }
}

void Board::initCitizens(int persons) {
  entities.clear();
  for (int i = 0; i < persons; i++) {
    int temp = rand() % size;
    if (!positions.at(temp)->isOccupied()) {
      std::shared_ptr<Citizen> cit(new Citizen(i % 4));
      entities.push_back(std::move(cit));
      updatePos(entities.at(i), positions.at(temp));
    } else {
      i--;
    }
  }
}

void Board::moveWest(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  if (!pos->getWest()->isOccupied()) {
    pos->setBaseEntity(NULL);
    updatePos(citizen, pos->getWest());
  }
}
void Board::moveEast(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  if (!pos->getEast()->isOccupied()) {
    pos->setBaseEntity(NULL);
    updatePos(citizen, pos->getEast());
  }
}
void Board::moveNorth(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  if (!pos->getNorth()->isOccupied()) {
    pos->setBaseEntity(NULL);
    updatePos(citizen, pos->getNorth());
  }
}
void Board::moveSouth(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  if (!pos->getSouth()->isOccupied()) {
    pos->setBaseEntity(NULL);
    updatePos(citizen, pos->getSouth());
  }
}

void Board::updatePos(std::shared_ptr<BaseEntity> cit,
                      std::shared_ptr<Position> pos) {
  cit->setPosition(pos);
  pos->setBaseEntity(cit);
  initEncounter(cit);
}

std::shared_ptr<Position> Board::getPosition(int index) {
  return positions.at(index);
}

std::vector<std::shared_ptr<BaseEntity>>* Board::getBaseEntities() {
  return &entities;
}

void Board::initEncounter(std::shared_ptr<BaseEntity> citizen) {
  if (std::static_pointer_cast<Citizen>(citizen)->isCurrentlyTalking()) {
    return;
  }
  std::shared_ptr<Position> pos = citizen->getPosition();
  // TODO Interface für jede Eigenschaft ( zb Movable, Talkable, etc)
  std::shared_ptr<BaseEntity> neighbour = NULL;
  if (pos->getNorth()->getBaseEntity() != NULL &&
      pos->getNorth()->getBaseEntity()->isCitizen()) {
    if (!std::static_pointer_cast<Citizen>(pos->getNorth()->getBaseEntity())
             ->isCurrentlyTalking()) {
      neighbour = pos->getNorth()->getBaseEntity();
    }
  } else if (pos->getSouth()->getBaseEntity() != NULL &&
             pos->getSouth()->getBaseEntity()->isCitizen()) {
    if (!std::static_pointer_cast<Citizen>(pos->getSouth()->getBaseEntity())
             ->isCurrentlyTalking()) {
      neighbour = pos->getSouth()->getBaseEntity();
    }
  } else if (pos->getEast()->getBaseEntity() != NULL &&
             pos->getEast()->getBaseEntity()->isCitizen()) {
    if (!std::static_pointer_cast<Citizen>(pos->getEast()->getBaseEntity())
             ->isCurrentlyTalking()) {
      neighbour = pos->getEast()->getBaseEntity();
    }
  } else if (pos->getWest()->getBaseEntity() != NULL &&
             pos->getWest()->getBaseEntity()->isCitizen()) {
    if (!std::static_pointer_cast<Citizen>(pos->getWest()->getBaseEntity())
             ->isCurrentlyTalking()) {
      neighbour = pos->getWest()->getBaseEntity();
    }
  }
  if (neighbour != NULL) {
    std::static_pointer_cast<Citizen>(citizen)->setCurrentlyTalking(true);
    std::static_pointer_cast<Citizen>(neighbour)->setCurrentlyTalking(true);
    encounter->talk(std::static_pointer_cast<Citizen>(citizen),
                    std::static_pointer_cast<Citizen>(neighbour));
  }
}

void Board::resetTalkingStatus() {
  for (std::shared_ptr<BaseEntity> entity : entities) {
    if (entity->isCitizen()) {
      std::static_pointer_cast<Citizen>(entity)->setCurrentlyTalking(false);
    }
  }
}

bool Board::isDictatorship() {
  bool citizen = false;
  int i;
  for (i = 0; !citizen && i < entities.size(); i++) {
    citizen = entities.at(i)->isCitizen();
  }
  int party = std::static_pointer_cast<Citizen>(entities.at(i))->getParty();
  for (; i < entities.size(); i++) {
    if (entities.at(i)->isCitizen()) {
      if (std::static_pointer_cast<Citizen>(entities.at(i))->getParty() !=
          party) {
        return false;
      }
    }
  }
  return true;
}

void Board::setXDim(int x) {
  xDim = x;
}

void Board::setYDim(int y) {
  yDim = y;
}

int Board::getXDim() {
  return xDim;
}

int Board::getYDim() {
  return yDim;
}

void Board::reset(int x, int y, int persons) {
  if (persons > x * y) {
    throw std::invalid_argument("Village is too small for Citizens");
  }

  xDim = x;
  yDim = y;
  size = x * y;

  // TODO init vectors & update destructor
  initPositions();
  initCitizens(persons);
}

namespace talk_modes {
const unsigned int north_south_east_west = 0;
const unsigned int diagonal = 1;
const unsigned int all = 2;
}  // namespace talk_modes
