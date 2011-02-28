#include "dlgAddFurniture.h"
#include "ui_dlgAddFurniture.h"

#include "ArrangerApp.h"
#include "wndMain.h"

#include <QtCore/QDir>
#include <QtGui/QTreeWidgetItem>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

dlgAddFurniture::dlgAddFurniture(QWidget *parent): QDialog(parent, Qt::Tool), m_ui(new Ui::dlgAddFurniture)
{
  m_ui->setupUi(this);
}

dlgAddFurniture::~dlgAddFurniture()
{
  delete m_ui;
}

void dlgAddFurniture::showEvent(QShowEvent *e)
{
  move(qobject_cast<ArrangerApp*>(qApp)->getWndMain()->geometry().center() - QPoint((width() / 2), (height() / 2)));

  m_ui->twFurniture->clear();

  QDir dir(qApp->applicationDirPath() + "/data/furniture");
  dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
  dir.setNameFilters(QStringList() << "*.xml");
  dir.setSorting(QDir::Name);

  foreach(QFileInfo file, dir.entryInfoList()) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    QFile f(file.absoluteFilePath());
    if(f.open(QIODevice::ReadOnly)) {
      QDomDocument doc;
      doc.setContent(&f);

      QDomElement root = doc.documentElement();
      for(int i = 0; i < root.childNodes().size(); i++) {
        QDomElement child = root.childNodes().at(i).toElement();

        if(child.nodeName() == "name") {
          item->setText(0, child.attribute("value"));
        } else if(child.nodeName() == "content") {
          QString name;
          if(child.attribute("type").toInt() == 1) {
            name = " osób";
          } else {
            name = " rzeczy";
          }

          item->setText(1, child.attribute("limit") + name);
        } else if(child.nodeName() == "size") {
          item->setText(2, child.attribute("width") + "x" + child.attribute("height"));
        }
      }

      item->setText(3, file.fileName());

      f.close();
    }

    m_ui->twFurniture->addTopLevelItem(item);
  }
}

void dlgAddFurniture::on_btnOK_clicked()
{
  emit signalAddFurniture(m_ui->twFurniture->currentItem()->text(3));
  accept();
}

void dlgAddFurniture::on_twFurniture_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
  m_ui->btnOK->setEnabled(current != 0);
}
