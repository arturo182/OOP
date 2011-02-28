#include "itmHunter.h"

#include "gfxScene.h"

#include <QtGui/QApplication>
#include <QtCore/QDebug>

itmHunter::itmHunter()
{
  m_wallHack = true;

  setPixmap(QPixmap(qApp->applicationDirPath() + "/data/hunters/hunter.png"));
}

void itmHunter::makeMove()
{
  makeMoveBy(qrand() % 2 + 1);
}
