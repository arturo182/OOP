#ifndef ITMPAWN_H
#define ITMPAWN_H

#include <QtGui/QGraphicsPixmapItem>

class itmPawn: public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT

  public:
    itmPawn(): m_wallHack(false) { }

    virtual void makeMove() { }
    void makeMoveBy(int spots);

    enum { Type = UserType };
    int type() const { return Type; }

  signals:
    void signalLog(QString msg);

  protected:
    bool m_wallHack;

  private:
    bool moveInDir(int dir);
    bool checkForCage(qreal x, qreal y);

};

#endif // ITMPAWN_H
