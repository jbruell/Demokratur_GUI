#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <Windows.h>
#include <time.h>
#include <iostream>
#include "citizen.h"

class Encounter {
 public:
  Encounter();
  void talk(Citizen*, Citizen*);
};

#endif  // ENCOUNTER_H
