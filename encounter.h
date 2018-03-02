#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "citizen.h"
#include <time.h>
#include <Windows.h>
#include <iostream>


class Encounter {
public:
    Encounter();
    void talk(Citizen *, Citizen *);
};

#endif // ENCOUNTER_H
