#include "dlgWizard.h"
#include "ui_dlgWizard.h"

#include "ArrangerApp.h"
#include "wndMain.h"

#include <QtGui/QCloseEvent>
#include <QtCore/QtDebug>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

dlgWizard::dlgWizard(QWidget *parent): QDialog(parent, Qt::Tool), m_ui(new Ui::dlgWizard)
{
  m_ui->setupUi(this);

  setWindowModality(Qt::ApplicationModal);
  show();
}

dlgWizard::~dlgWizard()
{
  delete m_ui;
}

void dlgWizard::closeEvent(QCloseEvent *e)
{
  if(qobject_cast<ArrangerApp*>(qApp)->getWndMain()->fileName().isEmpty()) {
    qApp->quit();
  }
}

void dlgWizard::showEvent(QShowEvent *e)
{
  ArrangerApp *app = qobject_cast<ArrangerApp*>(qApp);
  move(app->getWndMain()->geometry().center() - QPoint((width() / 2), (height() / 2)));

  foreach(QString file, app->getMru()) {
    if(QFile::exists(file)) {
      QTreeWidgetItem *item = new QTreeWidgetItem();
      item->setText(0, file);
      item->setIcon(0, QIcon(":/glyphs/new.png"));
      m_ui->twMRU->addTopLevelItem(item);
    }
  }
}

void dlgWizard::on_btnQuit_clicked()
{
  qApp->quit();
}

void dlgWizard::on_btnNew_clicked()
{
  emit signalNewClicked();
  close();
}

void dlgWizard::on_btnOpen_clicked()
{
  QString file = QFileDialog::getOpenFileName(this, "Otwórz projekt", QString(), "Projekty (*.xml)");
  if(!file.isEmpty()) {
    qobject_cast<ArrangerApp*>(qApp)->getWndMain()->loadFile(file);
    close();
  }
}

void dlgWizard::on_twMRU_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
  if(item) {
    if(QFile::exists(item->text(0))) {
      qobject_cast<ArrangerApp*>(qApp)->getWndMain()->loadFile(item->text(0));
      close();
    } else {
      QMessageBox::warning(this, "Otwieranie pliku", QString("Plik \"%1\" nie istnieje.").arg(QFileInfo(item->text(0)).fileName()));
    }
  }
}
