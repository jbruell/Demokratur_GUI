#include "citizen.h"

Citizen::Citizen() {
  party = 1;
}

Citizen::Citizen(int pParty) {
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
    setColor(Qt::red);
  } else if (party == 1) {
    setColor(Qt::yellow);
  } else if (party == 2) {
    setColor(Qt::green);
  } else if (party == 3) {
    setColor(Qt::cyan);
  }
}

bool Citizen::isCurrentlyTalking() {
  return currentlyTalking;
}

void Citizen::setCurrentlyTalking(bool talking) {
  currentlyTalking = talking;
}
