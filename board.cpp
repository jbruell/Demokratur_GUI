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
  citizens = new Citizen[x * y];
  setParties(share1, share2, share3, x * y);

  // TODO init vectors & update destructor
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

void Board::moveWest(std::shared_ptr<BaseEntity> citizen) {
  updatePos(citizen, citizen->getPosition()->getWest());
}
void Board::moveEast(std::shared_ptr<BaseEntity> citizen) {
  updatePos(citizen, citizen->getPosition()->getEast());
}
void Board::moveNorth(std::shared_ptr<BaseEntity> citizen) {
  updatePos(citizen, citizen->getPosition()->getNorth());
}
void Board::moveSouth(std::shared_ptr<BaseEntity> citizen) {
  updatePos(citizen, citizen->getPosition()->getSouth());
}

void Board::updatePos(std::shared_ptr<BaseEntity> cit,
                      std::shared_ptr<Position> pos) {
  cit->setPosition(pos);
  pos->setBaseEntity(cit);
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

void Board::prepareEncounter(int talkMode) {
  int size = xDim * yDim;
  int index = rand() % size;
  Citizen* c1 = &citizens[index];
  Citizen* c2;
  switch (talkMode) {
    case 0:
      switch (rand() % 4) {
        case 0:
          if (index - xDim < 0) {
            c2 = &citizens[size - 1 + index - xDim];
          } else {
            c2 = &citizens[index - xDim];
          }
          break;
        case 1:
          if (index + xDim >= size) {
            c2 = &citizens[index % xDim];
          } else {
            c2 = &citizens[index + xDim];
          }
          break;
        case 2:
          if (index % xDim == 0) {
            c2 = &citizens[index + xDim - 1];
          } else {
            c2 = &citizens[index - 1];
          }
          break;
        case 3:
          if (index % xDim == xDim - 1) {
            c2 = &citizens[index - xDim + 1];
          } else {
            c2 = &citizens[index + 1];
          }
          break;
      }
  }
  encounter->talk(c1, c2);
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
