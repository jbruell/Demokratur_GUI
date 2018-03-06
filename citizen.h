#ifndef CITIZEN_H
#define CITIZEN_H

class Citizen {
  int party;

 public:
  Citizen();
  Citizen(int);
  ~Citizen();
  int getParty();
  void setParty(int);
};

#endif  // CITIZEN_H
