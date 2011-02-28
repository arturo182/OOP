#include "wndMain.h"
#include "ui_wndMain.h"

#include "wndNewGame.h"
#include "gfxScene.h"

#include <QtCore/QSettings>
#include <QtGui/QMessageBox>

wndMain::wndMain(QWidget *parent): QMainWindow(parent), m_ui(new Ui::wndMain)
{
  QSettings set;

  m_ui->setupUi(this);
  m_wndNewGame = new wndNewGame(this);

  m_gfxScene = new gfxScene();
  m_ui->graphicsView->setScene(m_gfxScene);

  connect(m_wndNewGame, SIGNAL(signalStartGame(int,int,int,int,int)), m_gfxScene, SLOT(slotNewGame(int,int,int,int,int)));
  connect(m_gfxScene, SIGNAL(signalLog(QString)), this, SLOT(slotAddLog(QString)));
  connect(m_gfxScene, SIGNAL(signalGameStarted()), this, SLOT(slotActiveCtrls()));
  connect(m_gfxScene, SIGNAL(signalGameEnded()), this, SLOT(slotDeactiveCtrls()));
  connect(m_ui->actTurnNext, SIGNAL(triggered()), m_gfxScene, SLOT(slotNextTurn()));

  restoreGeometry(QByteArray::fromBase64(set.value("geometry", saveGeometry().toBase64()).toByteArray()));
  restoreState(QByteArray::fromBase64(set.value("state", saveState().toBase64()).toByteArray()));

  show();
  showNewGameWnd();

  slotAddLog("<b>Witam jestem Nag Aniacz i dzisiaj będę dla państwa komentował.</b>");
  slotAddLog("Przypominam, że nasze zwierzęta wydają dźwięki dlatego zalecamy włączenie głośników.<br>");
}

wndMain::~wndMain()
{
  QSettings set;

  set.setValue("geometry", saveGeometry().toBase64());
  set.setValue("state", saveState().toBase64());

  delete m_ui;
  delete m_wndNewGame;
}

void wndMain::slotAddLog(QString msg)
{
  m_ui->tbLog->append(msg);
}

void wndMain::slotActiveCtrls()
{
  m_ui->actTurnToggle->setText("Zatrzymaj");
  m_ui->actTurnToggle->setEnabled(true);
  m_ui->actTurnNext->setEnabled(false);
}

void wndMain::slotDeactiveCtrls()
{
  m_ui->actTurnToggle->setEnabled(false);
  m_ui->actTurnNext->setEnabled(false);
}

void wndMain::showNewGameWnd()
{
  m_wndNewGame->move(geometry().center() - m_wndNewGame->rect().center());
  m_wndNewGame->show();
}

void wndMain::on_actHelpAbout_triggered()
{
  QMessageBox::about(this, "O...", "Hunters\n\nProjekt #1 na OOP na II roku na informatyce na WMiI UŁ.\n\ncopyright (c) 2010-2011 Artur Pacholec");
}

void wndMain::on_actGameQuit_triggered()
{
  close();
}

void wndMain::on_actTurnToggle_triggered()
{
  if(m_gfxScene->isPaused()) {
    m_ui->actTurnToggle->setText("Zatrzymaj");
    m_ui->actTurnToggle->setIcon(QIcon(":/glyphs/pause.png"));
    m_ui->actTurnNext->setEnabled(false);
    m_gfxScene->play();
    slotAddLog("<span style='color: green;'>Witamy ponownie po krótkiej przerwie.</span>");
  } else {
    m_ui->actTurnToggle->setText("Wznów");
    m_ui->actTurnToggle->setIcon(QIcon(":/glyphs/play.png"));
    m_ui->actTurnNext->setEnabled(true);
    m_gfxScene->pause();
    slotAddLog("<span style='color: green;'>Sędzia zarządza krótką przerwę.</span>");
  }
}

void wndMain::on_actGameNew_triggered()
{
  m_wndNewGame->show();
}
