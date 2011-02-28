#include "itmAnimal.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfoList>
#include <QtXml/QDomDocument>

itmAnimal::itmAnimal(): itmPawn()
{
}

void itmAnimal::loadFromDir(QString d)
{
  QDir dir(d);
  QFileInfoList list = dir.entryInfoList(QStringList() << "*", QDir::NoDotAndDotDot | QDir::Dirs);

  QFileInfo info = list.at(rand() % list.count());

  QFile file(info.absoluteFilePath() + "/info.xml");
  if(file.open(QIODevice::ReadOnly)) {
    QDomDocument doc;
    doc.setContent(&file);

    QDomElement root = doc.documentElement();
    QDomElement name = root.elementsByTagName("name").at(0).toElement();
    m_name = name.attribute("value");
    m_nameSex = name.attribute("sex").toInt();
    m_genetivus = name.attribute("genetivus");

    QDomElement pixmap = root.elementsByTagName("pixmap").at(0).toElement();
    setPixmap(QPixmap(d + info.fileName() + "/" + pixmap.attribute("file")));
  }

  file.close();
}
