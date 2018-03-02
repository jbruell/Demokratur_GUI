#include "citizen.h"

Citizen::Citizen() {
  party = 1;
}

Citizen::Citizen(int pParty) {
  party = pParty;
}

Citizen::~Citizen() {}

int Citizen::GetParty() {
  return party;
}

void Citizen::SetParty(int pParty) {
  party = pParty;
}
