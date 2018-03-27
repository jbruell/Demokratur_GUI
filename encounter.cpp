#include "encounter.h"

Encounter::Encounter() {}

void Encounter::talk(std::shared_ptr<Citizen> citizen1,
                     std::shared_ptr<Citizen> citizen2) {
  switch (rand() % 2) {
    case 0:
      citizen1->setParty(citizen2->getParty());
      break;
    case 1:
      citizen2->setParty(citizen1->getParty());
      break;
  }
}
