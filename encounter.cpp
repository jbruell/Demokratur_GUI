#include "encounter.h"

Encounter::Encounter() {}

void Encounter::talk(Citizen* c1, Citizen* c2) {
  switch (rand() % 2) {
    case 0:
      c1->setParty(c2->getParty());
      break;
    case 1:
      c2->setParty(c1->getParty());
      break;
  }
}
