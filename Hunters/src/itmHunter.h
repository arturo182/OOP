#ifndef ITMHUNTER_H
#define ITMHUNTER_H

#include "itmPawn.h"

class itmHunter: public itmPawn
{
  public:
    itmHunter();

    void makeMove();

    enum { Type = UserType + 1 };
    int type() const { return Type; }
};

#endif // ITMHUNTER_H
