#include "citizen.h"

// public methods

Citizen::Citizen(int pParty) {
  QBrush* brush = new QBrush(Qt::SolidPattern);
  setBrush(brush);
  setParty(pParty);
  setCitizen(true);
  currentlyTalking = false;
}

Citizen::~Citizen() {}

int Citizen::getParty() {
  return party;
}

void Citizen::setParty(int pParty) {
  party = pParty;
  if (party == 0) {
    getBrush()->setColor(Qt::red);
  } else if (party == 1) {
    getBrush()->setColor(Qt::yellow);
  } else if (party == 2) {
    getBrush()->setColor(Qt::green);
  } else if (party == 3) {
    getBrush()->setColor(Qt::cyan);
  }
}

bool Citizen::isCurrentlyTalking() {
  return currentlyTalking;
}

void Citizen::setCurrentlyTalking(bool talking) {
  currentlyTalking = talking;
}
