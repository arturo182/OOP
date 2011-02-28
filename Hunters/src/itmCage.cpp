#include "itmCage.h"

#include <QtGui/QApplication>

itmCage::itmCage()
{
  setPixmap(QPixmap(qApp->applicationDirPath() + "/data/cage.png"));
}
