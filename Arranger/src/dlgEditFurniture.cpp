#include "dlgEditFurniture.h"
#include "ui_dlgEditFurniture.h"

#include "ArrangerApp.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QColorDialog>
#include <QtXml/QDomDocument>

dlgEditFurniture::dlgEditFurniture(QWidget *parent): QDialog(parent, Qt::Tool), m_ui(new Ui::dlgEditFurniture)
{
  m_ui->setupUi(this);
  setModal(true);
}

dlgEditFurniture::~dlgEditFurniture()
{
  delete m_ui;
}

void dlgEditFurniture::showEvent(QShowEvent *e)
{
  move(parentWidget()->geometry().center() - QPoint((width() / 2), (height() / 2)));

  if(m_fileName.isEmpty()) {
    setWindowTitle("Dodaj mebel");

    m_ui->edName->clear();
    m_ui->frmColor->setStyleSheet("");
    m_ui->sbSizeWidth->setValue(0);
    m_ui->sbSizeHeight->setValue(0);
    m_ui->cbContentType->setCurrentIndex(0);
    m_ui->sbContentLimit->setValue(0);
    m_ui->sbMarginsHorizontal->setValue(0);
    m_ui->sbMarginsVertical->setValue(0);
  } else {
    setWindowTitle("Edytuj mebel");

    QFile f(qApp->applicationDirPath() + "/data/furniture/" + m_fileName);
    if(f.open(QIODevice::ReadOnly)) {
      QDomDocument doc;
      doc.setContent(&f);

      QDomElement root = doc.documentElement();
      for(int i = 0; i < root.childNodes().size(); i++) {
        QDomElement child = root.childNodes().at(i).toElement();

        if(child.nodeName() == "name") {
          m_ui->edName->setText(child.attribute("value"));
        } else if(child.nodeName() == "content") {
          m_ui->cbContentType->setCurrentIndex(child.attribute("type").toInt());
          m_ui->sbContentLimit->setValue(child.attribute("limit").toInt());
        } else if(child.nodeName() == "margins") {
          m_ui->sbMarginsHorizontal->setValue(child.attribute("horizontal").toInt());
          m_ui->sbMarginsVertical->setValue(child.attribute("vertical").toInt());
        } else if(child.nodeName() == "size") {
          m_ui->sbSizeWidth->setValue(child.attribute("width").toInt());
          m_ui->sbSizeHeight->setValue(child.attribute("height").toInt());
        } else if(child.nodeName() == "color") {
          m_color = QColor(child.attribute("red").toInt(), child.attribute("green").toInt(), child.attribute("blue").toInt());
          m_ui->frmColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(child.attribute("red")).arg(child.attribute("green")).arg(child.attribute("blue")));
        }
      }

      f.close();
    }
  }

  m_ui->edName->setFocus();
}

void dlgEditFurniture::on_btnColor_clicked()
{
  m_color = QColorDialog::getColor(m_color, this);
  m_ui->frmColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(m_color.red()).arg(m_color.green()).arg(m_color.blue()));
}

void dlgEditFurniture::on_btnOK_clicked()
{
  if(!m_fileName.isEmpty()) {
    QFile::remove(qApp->applicationDirPath() + "/data/furniture/" + m_fileName);
  }

  QDomDocument doc;
  QDomElement root = doc.createElement("furniture");

  QDomElement name = doc.createElement("name");
  name.setAttribute("value", m_ui->edName->text());
  root.appendChild(name);

  QDomElement content = doc.createElement("content");
  content.setAttribute("type", m_ui->cbContentType->currentIndex());
  content.setAttribute("limit", m_ui->sbContentLimit->value());
  root.appendChild(content);

  QDomElement margins = doc.createElement("margins");
  margins.setAttribute("vertical", m_ui->sbMarginsVertical->value());
  margins.setAttribute("horizontal", m_ui->sbMarginsHorizontal->value());
  root.appendChild(margins);

  QDomElement color = doc.createElement("color");
  color.setAttribute("red", m_color.red());
  color.setAttribute("green", m_color.green());
  color.setAttribute("blue", m_color.blue());
  root.appendChild(color);

  QDomElement size = doc.createElement("size");
  size.setAttribute("width", m_ui->sbSizeWidth->value());
  size.setAttribute("height", m_ui->sbSizeHeight->value());
  root.appendChild(size);

  doc.appendChild(root);

  m_fileName = m_ui->edName->text().toLower() + ".xml";
  QFile f(qApp->applicationDirPath() + "/data/furniture/" + m_fileName);
  if(f.open(QIODevice::WriteOnly)) {
    QTextStream str(&f);
    str << doc.toString(2);

    f.close();
  }
}
