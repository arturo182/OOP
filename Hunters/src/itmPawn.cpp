#include "itmPawn.h"

#include "gfxScene.h"
#include "itmCage.h"

#include <QtCore/QDebug>

void itmPawn::makeMoveBy(int spots)
{
  int dir = qrand() % 4;

  for(int i = 0; i < spots; i++) {
    if(!moveInDir(dir)) {
      break;
    }
  }
}

bool itmPawn::moveInDir(int dir)
{
  gfxScene *scn = qobject_cast<gfxScene*>(scene());

  switch(dir) {
    case 0: // up
    {
      if(y() == 0) {
        if(m_wallHack) {
          if(checkForCage(x(), (scn->boardHeight()-1) * 24)) {
            return false;
          } else {
            setY((scn->boardHeight()-1) * 24);
          }
        } else {
          moveInDir(qrand() % 4);
        }
      } else {
        if(checkForCage(x(), y() - 24)) {
          moveInDir(qrand() % 4);
          return false;
        } else {
          setY(y() - 24);
        }
      }
    }
    break;

    case 1: // right
    {
      if(x() == (scn->boardWidth()-1) * 24) {
        if(m_wallHack) {
          if(checkForCage(0, y())) {
            return false;
          } else {
            setX(0);
          }
        } else {
          moveInDir(qrand() % 4);
        }
      } else {
        if(checkForCage(x() + 24, y())) {
          moveInDir(qrand() % 4);
          return false;
        } else {
          setX(x() + 24);
        }
      }
    }
    break;

    case 2: // down
    {
      if(y() == (scn->boardHeight()-1) * 24) {
        if(m_wallHack) {
          if(checkForCage(x(), 0)) {
            return false;
          } else {
            setY(0);
          }
        } else {
          moveInDir(qrand() % 4);
        }
      } else {
        if(checkForCage(x(), y() + 24)) {
         // moveInDir(qrand() % 4);
          return false;
        } else {
          setY(y() + 24);
        }
      }
    }
    break;

    case 3: // left
    {
      if(x() == 0) {
        if(m_wallHack) {
          if(checkForCage((scn->boardWidth()-1) * 24, y())) {
            return false;
          } else {
            setX((scn->boardWidth()-1) * 24);
          }
        } else {
          moveInDir(qrand() % 4);
        }
      } else {
        if(checkForCage(x() - 24, y())) {
          //moveInDir(qrand() % 4);
          return false;
        } else {
          setX(x() - 24);
        }
      }
    }
    break;
  }

  return true;
}

bool itmPawn::checkForCage(qreal x, qreal y)
{
  gfxScene *scn = qobject_cast<gfxScene*>(scene());

  QList<QGraphicsItem*> items = scn->items(x, y, 24, 24, Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
  if(items.count() > 0) {
    foreach(QGraphicsItem *item, items) {
      if(item->type() == itmCage::Type) {
        return true;
      }
    }
  }

  return false;
}
