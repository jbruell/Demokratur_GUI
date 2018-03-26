#ifndef CITIZEN_H
#define CITIZEN_H

#include <baseentity.h>

class Citizen : public BaseEntity {
  int party;

 public:
  Citizen();
  Citizen(int);
  ~Citizen();
  int getParty();
  void setParty(int);
};

#endif  // CITIZEN_H
