#include "gfxScene.h"

#include "itmRoom.h"
#include "itmFurniture.h"

#include <QtCore/QSettings>
#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsSceneMouseEvent>

gfxScene::gfxScene(QObject *parent): QGraphicsScene(parent)
{
  m_active = 0;
}

void gfxScene::newFile()
{
  m_active = 0;
  clear();
}

void gfxScene::moveActive(int x, int y)
{
  QSettings set;

  if(m_active) {
    int gridSize = set.value("gridSize", 25).toInt();

    m_active->moveBy(x * gridSize, y * gridSize);
    if(m_active->type() == itmRoom::Type) {
      itmRoom *room = static_cast<itmRoom*>(m_active);
      foreach(itmFurniture *furni, room->furniture()) {
        furni->moveBy(x * gridSize, y * gridSize);
      }
    }
  }
}

void gfxScene::resizeActive(int w, int h)
{
  QSettings set;

  if(m_active) {
    int gridSize = set.value("gridSize", 25).toInt();

    if((m_active->rect().width() + 2 * w * gridSize > 0) && (m_active->rect().height() + 2 * h * gridSize > 0)) {
      m_active->setRect(m_active->rect().x() - w * gridSize, m_active->rect().y() - h * gridSize, m_active->rect().width() + 2 * w * gridSize, m_active->rect().height() + 2 * h * gridSize);
    }
  }
}

void gfxScene::drawBackground(QPainter *painter, const QRectF &rect)
{
  QSettings set;

  int gridSize = set.value("gridSize", 25).toInt();
  int gridDivs = set.value("gridDivs", 4).toInt();
  painter->setWorldMatrixEnabled(true);

  qreal left = (int)rect.left() - ((int)rect.left() % gridSize);
  qreal top = (int)rect.top() - ((int)rect.top() % gridSize);

  QVector<QLineF> lines;
  QVector<QLineF> linesBold;

  for(qreal x = left; x < rect.right(); x += gridSize) {
    lines.append(QLineF(x, rect.top(), x, rect.bottom()));

    if((int)x % (gridSize * gridDivs) == 0) {
      linesBold.append(QLineF(x, rect.top(), x, rect.bottom()));
    }
  }

  for(qreal y = top; y < rect.bottom(); y += gridSize) {
    lines.append(QLineF(rect.left(), y, rect.right(), y));

    if((int)y % (gridSize * gridDivs) == 0) {
      linesBold.append(QLineF(rect.left(), y, rect.right(), y));
    }
  }

  QPen pen = painter->pen();
  pen.setColor(QColor(195, 195, 195));
  pen.setStyle(Qt::DotLine);
  painter->setPen(pen);
  painter->drawLines(lines);

  QPen penBold = painter->pen();
  penBold.setColor(QColor(130, 130, 130));
  penBold.setStyle(Qt::SolidLine);
  painter->setPen(penBold);
  painter->drawLines(linesBold);
}

void gfxScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  QGraphicsScene::mousePressEvent(mouseEvent);

  QGraphicsRectItem *item = static_cast<QGraphicsRectItem*>(itemAt(mouseEvent->scenePos()));
  if(item) {
    if(m_active) {
      m_active->setPen(QPen(QColor(m_active->data(0).toInt(), m_active->data(1).toInt(), m_active->data(2).toInt()), 1));
    }

    item->setPen(QPen(Qt::red, 2));
    m_active = item;
  }
}
