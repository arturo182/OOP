#ifndef ITMPREDATOR_H
#define ITMPREDATOR_H

#include "itmAnimal.h"

class itmPredator: public itmAnimal
{
  Q_OBJECT

  public:
    itmPredator();

    bool isCaged() { return m_caged; }

    void makeMove();
    void createCage();

    enum { Type = UserType + 2 };
    int type() const { return Type; }

  signals:
    void signalCaged();

  private:
    bool m_caged;
};

#endif // ITMPREDATOR_H
