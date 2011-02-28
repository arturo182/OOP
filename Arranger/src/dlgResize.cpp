#include "dlgResize.h"
#include "ui_dlgResize.h"

#include "ArrangerApp.h"
#include "wndMain.h"

dlgResize::dlgResize(QWidget *parent): QDialog(parent, Qt::Tool), m_ui(new Ui::dlgResize)
{
  m_ui->setupUi(this);
}

dlgResize::~dlgResize()
{
  delete m_ui;
}

void dlgResize::showEvent(QShowEvent *e)
{
  move(qobject_cast<ArrangerApp*>(qApp)->getWndMain()->geometry().center() - QPoint((width() / 2), (height() / 2)));

  m_ui->sbResizeWidth->setValue(0);
  m_ui->sbResizeHeight->setValue(0);
}

void dlgResize::on_btnOK_clicked()
{
  emit signalPlanResize(m_ui->sbResizeWidth->value(), m_ui->sbResizeHeight->value());
  accept();
}
