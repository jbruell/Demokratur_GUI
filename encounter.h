#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <Windows.h>
#include <citizen.h>
#include <time.h>
#include <iostream>

class Encounter {
 public:
  Encounter();
  void talk(std::shared_ptr<Citizen> citizen1,
            std::shared_ptr<Citizen> citizen2);
};

#endif  // ENCOUNTER_H
