#include "citizen.h"

Citizen::Citizen() {
  party = 1;
}

Citizen::Citizen(int pParty) {
  party = pParty;
}

Citizen::~Citizen() {}

int Citizen::getParty() {
  return party;
}

void Citizen::setParty(int pParty) {
  party = pParty;
}
