#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <citizen.h>

class Encounter {
 public:
  Encounter();
  ~Encounter();
  void talk(std::shared_ptr<Citizen> citizen1,
            std::shared_ptr<Citizen> citizen2);
};

#endif  // ENCOUNTER_H
