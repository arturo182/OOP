#include "dlgMove.h"
#include "ui_dlgMove.h"

#include "ArrangerApp.h"
#include "wndMain.h"

dlgMove::dlgMove(QWidget *parent): QDialog(parent, Qt::Tool), m_ui(new Ui::dlgMove)
{
  m_ui->setupUi(this);
}

dlgMove::~dlgMove()
{
  delete m_ui;
}

void dlgMove::showEvent(QShowEvent *e)
{
  move(qobject_cast<ArrangerApp*>(qApp)->getWndMain()->geometry().center() - QPoint((width() / 2), (height() / 2)));

  m_ui->sbMoveHorizontal->setValue(0);
  m_ui->sbMoveVertical->setValue(0);
}

void dlgMove::on_btnOK_clicked()
{
  emit signalPlanMove(m_ui->sbMoveHorizontal->value(), m_ui->sbMoveVertical->value());
  accept();
}
