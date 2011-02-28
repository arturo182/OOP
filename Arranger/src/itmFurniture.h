#ifndef ITMFURNITURE_H
#define ITMFURNITURE_H

#include <QtGui/QGraphicsRectItem>

class itmRoom;

class itmFurniture: public QGraphicsRectItem
{
  public:
    itmFurniture(QString fileName);

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    QString fileName() { return m_fileName; }
    int contentType() { return m_contentType; }
    int contentLimit() { return m_contentLimit; }
    int marginVertical() { return m_marginVertical; }
    int marginHorizontal() { return m_marginHorizontal; }
    QColor color() { return m_color; }

    int width() { return m_width; }
    int height() { return m_height; }

  private:
    itmRoom *m_room;
    int m_contentType;
    int m_contentLimit;
    int m_marginVertical;
    int m_marginHorizontal;
    QString m_fileName;
    QString m_name;
    QColor m_color;
    int m_width;
    int m_height;
};

#endif // ITMFURNITURE_H
