#ifndef ITMANIMAL_H
#define ITMANIMAL_H

#include "itmPawn.h"

class itmAnimal: public itmPawn
{
  public:
    itmAnimal();

    void loadFromDir(QString dir);

    QString name() { return m_name; }
    int nameSex() { return m_nameSex; }
    QString genetivus() { return m_genetivus; }

  protected:
    QString m_name;
    int m_nameSex;
    QString m_genetivus;
};

#endif // ITMANIMAL_H
