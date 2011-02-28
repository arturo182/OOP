#include "itmPredator.h"

#include "gfxScene.h"
#include "itmHunter.h"
#include "itmCage.h"

#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtGui/QSound>

itmPredator::itmPredator(): itmAnimal()
{
  m_caged = false;
  loadFromDir(qApp->applicationDirPath() + "/data/animals/predators/");
}

void itmPredator::makeMove()
{
  if(!m_caged) {
    gfxScene *scn = qobject_cast<gfxScene*>(scene());
    QList<QGraphicsItem*> neighbours;

    if(y() > 0) {  // up
      neighbours.append(scene()->items(x(), y() - 24, 24, 24, Qt::IntersectsItemShape, Qt::AscendingOrder));
    }

    if(x() < (scn->boardWidth()-1) * 24) { // right
      neighbours.append(scene()->items(x() + 24, y(), 24, 24, Qt::IntersectsItemShape, Qt::AscendingOrder));
    }

    if(y() < (scn->boardHeight()-1) * 24) { // down
      neighbours.append(scene()->items(x(), y() + 24, 24, 24, Qt::IntersectsItemShape, Qt::AscendingOrder));
    }

    if(x() > 0) { // left
      neighbours.append(scene()->items(x() - 24, y(), 24, 24, Qt::IntersectsItemShape, Qt::AscendingOrder));
    }

    if(neighbours.count() > 0) {
      int hunterCount = 0;
      int predCount = 0;

      foreach(QGraphicsItem *item, neighbours) {
        if(item->type() == itmPredator::Type) {
          predCount++;
        } else if(item->type() == itmHunter::Type) {
          hunterCount++;
        }
      }

      if(hunterCount == 2) {
        emit signalLog(QString("<span style='color: orange;'>%1 zostaje %2 w klatce!</span>").arg(m_name).arg((m_nameSex == 0)?"zamknięta":"zamknięty"));
        QSound::play(qApp->applicationDirPath() + "/data/sounds/caged.wav");
        createCage();
      }
    }
  }

  if(!m_caged) {
    makeMoveBy(qrand() % 3 + 1);
  }
}

void itmPredator::createCage()
{
  gfxScene *scn = qobject_cast<gfxScene*>(scene());
  bool area[3][3] = {
    { true, true,  true },
    { true, false, true },
    { true, true,  true }
  };

  m_caged = true;

  if(y() == 0) {  // up
    area[0][0] = false;
    area[0][1] = false;
    area[0][2] = false;
  }

  if(x() == (scn->boardWidth()-1) * 24) { // right
    area[0][2] = false;
    area[1][2] = false;
    area[2][2] = false;
  }

  if(y() == (scn->boardHeight()-1) * 24) { // down
    area[2][0] = false;
    area[2][1] = false;
    area[2][2] = false;
  }

  if(x() == 0) { // left
    area[0][0] = false;
    area[1][0] = false;
    area[2][0] = false;
  }

  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if((i == 1) && (j == 1)) {
        continue;
      }

      if(area[j][i]) {
        int addX = 0;
        int addY = 0;

        if(i == 0) {
          addX = -24;
        } else if(i == 2) {
          addX = 24;
        }

        if(j == 0) {
          addY = -24;
        } else if(j == 2) {
          addY = 24;
        }

        QList<QGraphicsItem*> items = scn->items(x() + addX, y() + addY, 24, 24, Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
        foreach(QGraphicsItem *item, items) {
          if(item->type() == itmPredator::Type) {
            itmPredator *pred = static_cast<itmPredator*>(item);
            if(pred->isCaged()) {
              continue;
            }
          }
        }

        itmCage *cage = new itmCage();
        cage->setPos(x() + addX, y() + addY);
        scn->addItem(cage);
      }
    }
  }

  emit signalCaged();
}
