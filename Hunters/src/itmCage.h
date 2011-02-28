#ifndef ITMCAGE_H
#define ITMCAGE_H

#include "itmPawn.h"

class itmCage: public itmPawn
{
  public:
    itmCage();

    enum { Type = UserType + 4 };
    int type() const { return Type; }

};

#endif // ITMCAGE_H
