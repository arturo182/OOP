#ifndef ITMMELLOW_H
#define ITMMELLOW_H

#include "itmAnimal.h"

class itmMellow: public itmAnimal
{
  public:
    itmMellow();

    void makeMove();

    enum { Type = UserType + 3 };
    int type() const { return Type; }

  private:
    bool m_eaten;
};

#endif // ITMMELLOW_H
