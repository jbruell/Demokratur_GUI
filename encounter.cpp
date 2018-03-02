#include "encounter.h"

Encounter::Encounter() {}

void Encounter::talk(Citizen* c1, Citizen* c2) {
  switch (rand() % 2) {
    case 0:
      c1->SetParty(c2->GetParty());
      break;
    case 1:
      c2->SetParty(c1->GetParty());
      break;
  }
}
