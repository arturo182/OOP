#ifndef MGRFURNITURE_H
#define MGRFURNITURE_H

#include "itmFurniture.h"

#include <QtCore/QList>

struct furniInfo
{
  QString fileName;
  int contentType;
  int contentLimit;
};

class mgrFurniture
{
  public:
    mgrFurniture();

    itmFurniture *findBest(int type, int quantity);

  private:
    QList<furniInfo*> m_list;
};

#endif // MGRFURNITURE_H
