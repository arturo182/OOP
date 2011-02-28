#include "wndmain.h"
#include "ui_wndmain.h"

#include "ArrangerApp.h"
#include "gfxScene.h"
#include "itmRoom.h"
#include "itmFurniture.h"
#include "mgrFurniture.h"

#include <QtCore/QSettings>
#include <QtCore/QFileInfo>
#include <QtCore/QtDebug>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

wndMain::wndMain(QWidget *parent): QMainWindow(parent), m_ui(new Ui::wndMain)
{
  QSettings set;

  m_ui->setupUi(this);
  m_lbScale = new QLabel("100%");
  statusBar()->addPermanentWidget(m_lbScale);

  show();

  restoreGeometry(set.value("geometry", saveGeometry()).toByteArray());
  restoreState(set.value("state", saveState()).toByteArray());

  m_gfxScene = new gfxScene();
  m_ui->graphicsView->setScene(m_gfxScene);

  m_furniMgr = new mgrFurniture();
}

wndMain::~wndMain()
{
  delete m_ui;
}

void wndMain::setFileName(QString fileName)
{
  m_fileName = fileName;

  setModified(isModified());
}

void wndMain::setModified(bool modified)
{
  m_modified = modified;

  if(isModified()) {
    setWindowTitle(QString("* %1 - HomeArranger").arg(QFileInfo(m_fileName).fileName()));
  } else {
    setWindowTitle(QString("%1 - HomeArranger").arg(QFileInfo(m_fileName).fileName()));
  }
}

void wndMain::loadFile(QString fileName)
{
  if(QFile::exists(fileName)) {
    QFile file(fileName);

    m_gfxScene->clear();
    if(file.open(QIODevice::ReadOnly)) {
      QDomDocument doc;
      doc.setContent(&file);

      QDomElement root = doc.documentElement();

      QDomNodeList rooms = root.elementsByTagName("room");
      for(int i = 0; i < rooms.size(); i++) {
        QDomElement child = rooms.at(i).toElement();

        int width = child.attribute("width").toInt();
        int height = child.attribute("height").toInt();
        int x = child.attribute("x").toInt();
        int y = child.attribute("y").toInt();

        itmRoom *room = new itmRoom(width, height);
        room->setPos(x, y);
        m_gfxScene->addItem(room);

        QDomNodeList furnis = child.elementsByTagName("furniture");
        for(int j = 0; j < furnis.size(); j++) {
          QDomElement fchild = furnis.at(j).toElement();

          QString fileName = fchild.attribute("file");
          //int fwidth = fchild.attribute("width").toInt();
          //int fheight = fchild.attribute("height").toInt();
          int fx = fchild.attribute("x").toInt();
          int fy = fchild.attribute("y").toInt();

          itmFurniture *furni = new itmFurniture(fileName);
          furni->setPos(x + fx, y + fy);

          room->furniture().append(furni);
          m_gfxScene->addItem(furni);
        }
      }

      file.close();

      ArrangerApp *app = qobject_cast<ArrangerApp*>(qApp);
      app->addToMru(fileName);

      setFileName(fileName);
      setModified(false);
    } else {
      qDebug() << "Open error!";
    }

  }
}

void wndMain::closeEvent(QCloseEvent *e)
{
  if(isModified()) {
    QMessageBox msgBox;
    msgBox.setText("Projekt został zmieniony.");
    msgBox.setInformativeText(QString("Czy chcesz zapisać zmiany w \"%1\"?").arg(QFileInfo(m_fileName).fileName()));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    switch(msgBox.exec()) {
      case QMessageBox::Save:
        m_ui->actFileSave->trigger();
      break;

      case QMessageBox::Cancel:
        e->ignore();
      break;
    }
  }

  if(e->isAccepted()) {
    QSettings set;

    set.setValue("geometry", saveGeometry());
    set.setValue("state", saveState());
  }
}

void wndMain::applySettings()
{
  m_gfxScene->update();
}

void wndMain::slotNewFile()
{
  if(isModified()) {
    QMessageBox msgBox;
    msgBox.setText("Projekt został zmieniony.");
    msgBox.setInformativeText(QString("Czy chcesz zapisać zmiany w \"%1\"?").arg(QFileInfo(m_fileName).fileName()));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    switch(msgBox.exec()) {
      case QMessageBox::Save:
        m_ui->actFileSave->trigger();
      break;

      case QMessageBox::Cancel:
        return;
      break;
    }
  }

  m_gfxScene->newFile();
  setModified(false);
  setFileName("Bez Nazwy");
}

void wndMain::slotAddRoom(int width, int height, bool fill, int people, int things)
{
  QSettings set;

  itmRoom *room = new itmRoom(width, height);
  m_gfxScene->addItem(room);

  while(room->collidingItems().count() > 0) {
    room->moveBy(set.value("gridSize", 25).toReal(), 0);
  }

  if(fill) {
    while(people > 0) {
      itmFurniture* furni = m_furniMgr->findBest(1, people);
      room->furniture().append(furni);
      m_gfxScene->addItem(furni);

      while((furni->collidingItems().count() > 0)) {
        if((furni->collidingItems().count() == 1) && (furni->collidesWithItem(room))) {
          break;
        }

        furni->moveBy(set.value("gridSize", 25).toReal(), 0);
      }

      people -= furni->contentLimit();
    }

    while(things > 0) {
      itmFurniture* furni = m_furniMgr->findBest(0, things);
      room->furniture().append(furni);
      m_gfxScene->addItem(furni);

      while((furni->collidingItems().count() > 0)) {
        if((furni->collidingItems().count() == 1) && (furni->collidesWithItem(room))) {
          break;
        }

        furni->moveBy(set.value("gridSize", 25).toReal(), 0);
      }

      things -= furni->contentLimit();
    }
  }

  setModified(true);
}

void wndMain::slotPlanMove(int x, int y)
{
  m_gfxScene->moveActive(x, y);
  m_ui->graphicsView->centerOn(0, 0);
  setModified(true);
}

void wndMain::slotPlanResize(int w, int h)
{
  m_gfxScene->resizeActive(w, h);
  m_ui->graphicsView->centerOn(0, 0);
  setModified(true);
}

void wndMain::slotAddFurniture(QString fileName)
{
  if(m_gfxScene->activeItem()) {
    itmRoom *room = static_cast<itmRoom*>(m_gfxScene->activeItem());
    itmFurniture *furni = new itmFurniture(fileName);

    furni->setPos(room->pos());

    room->furniture().append(furni);
    m_gfxScene->addItem(furni);
  }
}

void wndMain::on_actFileNew_triggered()
{
  slotNewFile();
}

void wndMain::on_actFileOpen_triggered()
{
  if(isModified()) {
    QMessageBox msgBox;
    msgBox.setText("Projekt został zmieniony.");
    msgBox.setInformativeText(QString("Czy chcesz zapisać zmiany w \"%1\"?").arg(QFileInfo(m_fileName).fileName()));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    switch(msgBox.exec()) {
      case QMessageBox::Save:
        m_ui->actFileSave->trigger();
      break;

      case QMessageBox::Cancel:
        return;
      break;
    }
  }

  QString file = QFileDialog::getOpenFileName(this, "Otwórz projekt", QString(), "Projekty (*.xml)");
  loadFile(file);
}

void wndMain::on_actFileQuit_triggered()
{
  close();
}

void wndMain::on_actPlanAddRoom_triggered()
{
  emit signalOpenAddRoomDlg();
}

void wndMain::on_actPlanZoomIn_triggered()
{
  m_ui->graphicsView->scale(1.15, 1.15);
  m_lbScale->setText(QString("%1%").arg((int)(m_ui->graphicsView->transform().m11() * 100)));
}

void wndMain::on_actPlanZoomOut_triggered()
{
  m_ui->graphicsView->scale(1.0 / 1.15, 1.0 / 1.15);
  m_lbScale->setText(QString("%1%").arg((int)(m_ui->graphicsView->transform().m11() * 100)));
}

void wndMain::on_actFileSave_triggered()
{
  if(m_fileName == "Bez Nazwy") {
    QString file = QFileDialog::getSaveFileName(this, "Zapisz projekt", QString(), "Projekty (*.xml)");
    if(file.isEmpty()) {
      return;
    }

    setFileName(file);
  }

  QDomDocument doc;
  QDomElement root = doc.createElement("project");

  foreach(QGraphicsItem *item, m_gfxScene->items()) {
    if(item->type() == itmRoom::Type) {
      itmRoom *room = static_cast<itmRoom*>(item);
      QDomElement child = doc.createElement("room");

      child.setAttribute("width", room->width());
      child.setAttribute("height", room->height());
      child.setAttribute("x", room->pos().x());
      child.setAttribute("y", room->pos().y());

      foreach(itmFurniture *furni, room->furniture()) {
        QDomElement fchild = doc.createElement("furniture");

        fchild.setAttribute("file", furni->fileName());
        fchild.setAttribute("width", furni->width());
        fchild.setAttribute("height", furni->height());
        fchild.setAttribute("x", furni->pos().x() - room->pos().x());
        fchild.setAttribute("y", furni->pos().y() - room->pos().y());

        child.appendChild(fchild);
      }

      root.appendChild(child);
    }
  }

  doc.appendChild(root);

  QFile f(m_fileName);
  if(f.open(QIODevice::WriteOnly)) {
    QTextStream str(&f);
    str << doc.toString(2);

    f.close();
  } else {
    qDebug() << "error saving file!";
  }

  setModified(false);
}

void wndMain::on_actHelpAbout_triggered()
{
  QMessageBox::about(this, "O...", "HomeArranger\n\nProjekt #2 na OOP na II roku na informatyce na WMiI UŁ.\n\ncopyright (c) 2010-2011 Artur Pacholec");
}

void wndMain::on_actFileSettings_triggered()
{
  emit signalOpenSettingsDlg();
}

void wndMain::on_actPlanMove_triggered()
{
  if(m_gfxScene->activeItem()) {
    emit signalOpenMoveDlg();
  } else {
    QMessageBox::information(this, "Brak zaznaczenia", "Wybierz co chcesz przesunąć (mebel/pokój).");
  }
}

void wndMain::on_actPlanResize_triggered()
{
  if(m_gfxScene->activeItem()) {
    emit signalOpenResizeDlg();
  } else {
    QMessageBox::information(this, "Brak zaznaczenia", "Wybierz czemu chcesz zmienić rozmiar (mebel/pokój).");
  }
}

void wndMain::on_actPlanAddFurniture_triggered()
{
  if(!m_gfxScene->activeItem() || m_gfxScene->activeItem()->type() != itmRoom::Type) {
    QMessageBox::information(this, "Złe zaznaczenia", "Musisz zaznaczyć pokój.");
  } else {
    emit signalOpenAddFurniDlg();
  }
}
