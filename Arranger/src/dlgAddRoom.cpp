#include "dlgAddRoom.h"
#include "ui_dlgAddRoom.h"

#include "ArrangerApp.h"
#include "wndMain.h"

dlgAddRoom::dlgAddRoom(QWidget *parent): QDialog(parent, Qt::Tool), m_ui(new Ui::dlgAddRoom)
{
  m_ui->setupUi(this);
}

dlgAddRoom::~dlgAddRoom()
{
  delete m_ui;
}

void dlgAddRoom::showEvent(QShowEvent *e)
{
  move(qobject_cast<ArrangerApp*>(qApp)->getWndMain()->geometry().center() - QPoint((width() / 2), (height() / 2)));

  m_ui->cbFill->setChecked(false);
  m_ui->sbFillPeople->setValue(0);
  m_ui->sbFillThings->setValue(0);
  m_ui->sbSizeHeight->setValue(1);
  m_ui->sbSizeWidth->setValue(1);
}

void dlgAddRoom::on_btnOK_clicked()
{
  emit signalAddRoom(m_ui->sbSizeWidth->value(), m_ui->sbSizeHeight->value(), m_ui->cbFill->isChecked(), m_ui->sbFillPeople->value(), m_ui->sbFillThings->value());
  accept();
}
