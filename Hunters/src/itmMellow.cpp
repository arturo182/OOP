#include "itmMellow.h"

#include "itmPredator.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtGui/QApplication>
#include <QtGui/QSound>

itmMellow::itmMellow(): itmAnimal()
{
  m_eaten = false;
  loadFromDir(qApp->applicationDirPath() + "/data/animals/mellows/");
}

void itmMellow::makeMove()
{
  if(!m_eaten) {
    foreach(QGraphicsItem *item, collidingItems()) {
      if(item->type() == QGraphicsItem::UserType + 2) {
        itmPredator *pred = static_cast<itmPredator*>(item);

        m_eaten = true;
        QSound::play(qApp->applicationDirPath() + "/data/sounds/eaten.wav");

        hide();
        emit signalLog(QString("<span style='color: red;'>%1 zostaje %2 przez %3.</span>").arg(m_name).arg((m_nameSex == 1)?"zjedzony":"zjedzona").arg(pred->genetivus()));
        return;
      }
    }

    makeMoveBy(1);
  }
}
