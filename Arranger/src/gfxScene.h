#ifndef GFXSCENE_H
#define GFXSCENE_H

#include <QtGui/QGraphicsScene>

class gfxScene: public QGraphicsScene
{
  Q_OBJECT

  public:
    explicit gfxScene(QObject *parent = 0);
    void newFile();

    void moveActive(int x, int y);
    void resizeActive(int w, int h);

    QGraphicsRectItem *activeItem() { return m_active; }

  protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

  private:
    QGraphicsRectItem *m_active;
};

#endif // GFXSCENE_H
