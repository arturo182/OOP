#include "itmRoom.h"

#include <QtGui/QPen>
#include <QtGui/QLinearGradient>
#include <QtCore/QSettings>

itmRoom::itmRoom(int width, int height): m_width(width), m_height(height)
{
  QSettings set;

  QPen newPen = pen();
  newPen.setColor(QColor(115, 157, 210));
  setPen(newPen);

  setData(0, 115);
  setData(1, 157);
  setData(2, 210);

  QLinearGradient grad(0, 0, 100, 100);
  grad.setStart(50, 100);
  grad.setFinalStop(100, 0);
  grad.setColorAt(0, Qt::white);
  grad.setColorAt(1, QColor(222, 231, 242));
  setBrush(grad);

  setToolTip("Pokój");

  setRect(0, 0, set.value("gridSize").toInt() * width, set.value("gridSize").toInt() * height);
}
