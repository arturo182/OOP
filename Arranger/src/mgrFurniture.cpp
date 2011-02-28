#include "mgrFurniture.h"

#include "ArrangerApp.h"

#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

mgrFurniture::mgrFurniture()
{
  QDir dir(qApp->applicationDirPath() + "/data/furniture/");
  QFileInfoList list = dir.entryInfoList(QStringList() << "*.xml", QDir::Files);

  foreach(QFileInfo info, list) {
    QFile file(info.absoluteFilePath());
    if(file.open(QIODevice::ReadOnly)) {
      QDomDocument doc;
      doc.setContent(&file);

      QDomElement root = doc.documentElement();
      QDomElement content = root.elementsByTagName("content").at(0).toElement();

      furniInfo *nfo = new furniInfo;
      nfo->fileName = info.fileName();
      nfo->contentType = content.attribute("type").toInt();
      nfo->contentLimit = content.attribute("limit").toInt();
      m_list.append(nfo);
    }

    file.close();
  }
}

itmFurniture *mgrFurniture::findBest(int type, int quantity)
{
  QString fileName;
  int limit = 0;
  foreach(furniInfo *info, m_list) {
    if(info->contentType == type) {
      if((info->contentLimit <= quantity) && (info->contentLimit > limit)) {
        fileName = info->fileName;
        limit = info->contentLimit;
      }
    }
  }

  if(fileName.isEmpty()) {
    foreach(furniInfo *info, m_list) {
      if(info->contentType == type) {
        fileName = info->fileName;
        limit = info->contentLimit;
        break;
      }
    }
  }

  itmFurniture *furni = new itmFurniture(fileName);
  return furni;
}
