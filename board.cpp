#include <board.h>

Board::Board() {
  // new Board(10, 10, 25, 25 ,25, 25, 0);
}

Board::Board(int x,
             int y,
             int share1,
             int share2,
             int share3,
             int share4,
             int talkMode) {
  if (share1 + share2 + share3 + share4 != 100) {
    throw std::invalid_argument("Shares do not add up to 100 percent");
  }
  encounter = new Encounter();

  xDim = x;
  yDim = y;
  size = x * y;

  talkingMode = talkMode;
  // citizens = new Citizen[x * y];
  // setParties(share1, share2, share3, x * y);

  // TODO init vectors & update destructor
  initPositions();
  initCitizens();
  // updatePos(entities.at(0), positions.at(100));
}

Board::~Board() {
  delete encounter;
  delete[] citizens;
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

void Board::initCitizens() {
  for (int i = 0; i < 10; i++) {
    std::shared_ptr<Citizen> cit(new Citizen(rand() % 4));
    entities.push_back(std::move(cit));
    updatePos(entities.at(i), positions.at(10 * i));
    // updatePos(cit, positions.at(10 * i));
  }
}

void Board::moveWest(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  pos->setBaseEntity(NULL);
  updatePos(citizen, pos->getWest());  // TODO check if occupied
}
void Board::moveEast(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  pos->setBaseEntity(NULL);
  updatePos(citizen, pos->getEast());
}
void Board::moveNorth(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  pos->setBaseEntity(NULL);
  updatePos(citizen, pos->getNorth());
}
void Board::moveSouth(std::shared_ptr<BaseEntity> citizen) {
  std::shared_ptr<Position> pos = citizen->getPosition();
  pos->setBaseEntity(NULL);
  updatePos(citizen, pos->getSouth());
}

void Board::updatePos(std::shared_ptr<BaseEntity> cit,
                      std::shared_ptr<Position> pos) {
  cit->setPosition(pos);
  pos->setBaseEntity(cit);
}

std::shared_ptr<Position> Board::getPosition(int index) {
  return positions.at(index);
}

std::vector<std::shared_ptr<BaseEntity>>* Board::getBaseEntities() {
  return &entities;
}

void Board::setParties(int share1, int share2, int share3, int size) {
  int p1 = share1 * (size / 100);
  int p2 = p1 + share2 * (size / 100);
  int p3 = p2 + share3 * (size / 100);

  for (int i = 0; i < size; i++) {
    int party;
    if (i < p1) {
      party = 0;
    } else if (i < p2) {
      party = 1;
    } else if (i < p3) {
      party = 2;
    } else {
      party = 3;
    }
    Citizen* c = new Citizen(party);
    citizens[i] = *c;
  }
}

void Board::initEncounter(std::shared_ptr<BaseEntity> citizen) {
  //  std::shared_ptr<Position> pos = citizen->getPosition();
  //  // TODO Interface für jede Eigenschaft ( zb Movable, Talkable, etc)
  //  std::shared_ptr<BaseEntity> neighbour = NULL;
  //  if (pos->getNorth()->getBaseEntity() != NULL) {
  //    neighbour = pos->getNorth()->getBaseEntity();
  //  } else if (pos->getSouth()->getBaseEntity() != NULL) {
  //    neighbour = pos->getSouth()->getBaseEntity();
  //  } else if (pos->getEast()->getBaseEntity() != NULL) {
  //    neighbour = pos->getEast()->getBaseEntity();
  //  } else if (pos->getWest()->getBaseEntity() != NULL) {
  //    neighbour = pos->getWest()->getBaseEntity();
  //  }
  //  if (neighbour != NULL && neighbour->isCitizen()) {
  //    encounter->talk(citizen, casted_neighbour);
  //  }
}

bool Board::isDictatorship() {
  int party = citizens[0].getParty();
  int size = xDim * yDim;
  for (int i = 0; i < size; i++) {
    if (citizens[i].getParty() != party) {
      return false;
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

Citizen* Board::getCitizens() {
  return citizens;
}

void Board::reset(int x,
                  int y,
                  int share1,
                  int share2,
                  int share3,
                  int share4,
                  int talkMode) {
  if (share1 + share2 + share3 + share4 != 100) {
    throw std::invalid_argument("Shares do not add up to 100 percent");
  }
  setXDim(x);
  setYDim(y);
  setParties(share1, share2, share3, xDim * yDim);
}

namespace talk_modes {
const unsigned int north_south_east_west = 0;
const unsigned int diagonal = 1;
const unsigned int all = 2;
}  // namespace talk_modes
