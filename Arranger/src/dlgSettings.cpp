#include "dlgSettings.h"
#include "ui_dlgSettings.h"

#include "ArrangerApp.h"
#include "dlgEditFurniture.h"
#include "wndMain.h"

#include <QtGui/QShowEvent>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>
#include <QtCore/QtDebug>

dlgSettings::dlgSettings(QWidget *parent): QDialog(parent, Qt::Tool), m_ui(new Ui::dlgSettings)
{
  m_ui->setupUi(this);

  setWindowModality(Qt::ApplicationModal);

  m_dlgFurniture = new dlgEditFurniture(this);
}

dlgSettings::~dlgSettings()
{
  delete m_ui;
}

void dlgSettings::showEvent(QShowEvent *e)
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
        } else if(child.nodeName() == "margins") {
          item->setText(2, child.attribute("horizontal") + "x" + child.attribute("vertical"));
        } else if(child.nodeName() == "size") {
          item->setText(3, child.attribute("width") + "x" + child.attribute("height"));
        } else if(child.nodeName() == "color") {
          item->setForeground(4, QColor(child.attribute("red").toInt(), child.attribute("green").toInt(), child.attribute("blue").toInt()));
          item->setText(4, "R: " + child.attribute("red") + " G: " + child.attribute("green") + " B: " + child.attribute("blue"));
        }
      }

      item->setText(5, file.fileName());

      f.close();
    }

    m_ui->twFurniture->addTopLevelItem(item);
  }
}

void dlgSettings::on_twFurniture_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
  if(current) {
    m_ui->btnFurnitureEdit->setEnabled(true);
    m_ui->btnFurnitureDelete->setEnabled(true);
  } else {
    m_ui->btnFurnitureEdit->setEnabled(false);
    m_ui->btnFurnitureDelete->setEnabled(false);
  }
}

void dlgSettings::on_btnFurnitureAdd_clicked()
{
  m_dlgFurniture->setFileName("");
  m_dlgFurniture->show();
}

void dlgSettings::on_btnFurnitureEdit_clicked()
{
  m_dlgFurniture->setFileName(m_ui->twFurniture->currentItem()->text(5));
  m_dlgFurniture->show();
}
