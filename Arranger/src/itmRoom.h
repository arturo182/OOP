#ifndef ITMROOM_H
#define ITMROOM_H

#include <QtGui/QGraphicsRectItem>

class itmFurniture;

class itmRoom: public QGraphicsRectItem
{
  public:
    itmRoom(int width, int height);

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    int width() { return m_width; }
    int height() { return m_height; }

    QList<itmFurniture*> &furniture() { return m_furniture; }

  private:
    QList<itmFurniture*> m_furniture;
    int m_width;
    int m_height;
};

#endif // ITMROOM_H
