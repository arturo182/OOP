#include "itmFurniture.h"

#include "ArrangerApp.h"

#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QtGui/QPen>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

itmFurniture::itmFurniture(QString fileName)
{
  QSettings set;

  m_fileName = fileName;
  QFile file(qApp->applicationDirPath() + "/data/furniture/" + fileName);
  if(file.open(QIODevice::ReadOnly)) {
    QDomDocument doc;
    doc.setContent(&file);

    QDomElement root = doc.documentElement();
    QDomElement name = root.elementsByTagName("name").at(0).toElement();
    QDomElement content = root.elementsByTagName("content").at(0).toElement();
    QDomElement margins = root.elementsByTagName("margins").at(0).toElement();
    QDomElement color = root.elementsByTagName("color").at(0).toElement();
    QDomElement size = root.elementsByTagName("size").at(0).toElement();

    m_name = name.attribute("value");
    m_contentType = content.attribute("type").toInt();
    m_contentLimit = content.attribute("limit").toInt();
    m_marginVertical = margins.attribute("vertical").toInt();
    m_marginHorizontal = margins.attribute("horizontal").toInt();
    m_color = QColor(color.attribute("red").toInt(), color.attribute("green").toInt(), color.attribute("blue").toInt());
    m_width = size.attribute("width").toInt();
    m_height = size.attribute("height").toInt();

    QPen newPen = pen();
    newPen.setColor(m_color.darker());
    setPen(newPen);

    setData(0, m_color.darker().red());
    setData(1, m_color.darker().green());
    setData(2, m_color.darker().blue());

    setBrush(m_color);
    setToolTip(m_name);
    setRect(0, 0, set.value("gridSize").toInt() * m_width, set.value("gridSize").toInt() * m_height);
  }

  file.close();
}

