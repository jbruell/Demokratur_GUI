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

  talkingMode = talkMode;
  citizens = new Citizen[x * y];
  setParties(share1, share2, share3, x * y);
}

Board::~Board() {
  delete encounter;
  delete[] citizens;
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
