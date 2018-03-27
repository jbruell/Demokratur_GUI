#ifndef CITIZEN_H
#define CITIZEN_H

#include <baseentity.h>

class Citizen : public BaseEntity {
  int party;
  bool currentlyTalking;

 public:
  Citizen();
  Citizen(int);
  ~Citizen();
  int getParty();
  void setParty(int);
  bool isCurrentlyTalking();
  void setCurrentlyTalking(bool talking);
};

#endif  // CITIZEN_H
