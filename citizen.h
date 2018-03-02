#ifndef CITIZEN_H
#define CITIZEN_H


class Citizen {
    int party;
public:
    Citizen();
    Citizen(int);
    int GetParty();
    void SetParty(int);
};

#endif // CITIZEN_H
