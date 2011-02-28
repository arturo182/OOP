#include "wndNewGame.h"
#include "ui_wndNewGame.h"

wndNewGame::wndNewGame(QWidget *parent): QWidget(parent, Qt::Tool), m_ui(new Ui::wndNewGame)
{
  m_ui->setupUi(this);

  setWindowModality(Qt::ApplicationModal);
}

wndNewGame::~wndNewGame()
{
  delete m_ui;
}

void wndNewGame::showEvent(QShowEvent *event)
{
  m_ui->sbGameTurn->setValue(1000);
  m_ui->sbBoardWidth->setValue(20);
  m_ui->sbBoardHeight->setValue(15);
  m_ui->sbPawnsHunters->setValue(6);
  m_ui->sbPawnsAnimals->setValue(7);
}

void wndNewGame::on_btnOK_clicked()
{
  emit signalStartGame(m_ui->sbGameTurn->value(), m_ui->sbBoardWidth->value(), m_ui->sbBoardHeight->value(), m_ui->sbPawnsHunters->value(), m_ui->sbPawnsAnimals->value());
  close();
}
