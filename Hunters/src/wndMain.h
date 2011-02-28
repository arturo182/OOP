#ifndef WNDMAIN_H
#define WNDMAIN_H

#include <QtGui/QMainWindow>

class wndNewGame;
class gfxScene;

namespace Ui
{
  class wndMain;
}

class wndMain: public QMainWindow
{
  Q_OBJECT

  public:
    explicit wndMain(QWidget *parent = 0);
    ~wndMain();

  public slots:
    void slotAddLog(QString msg);
    void slotActiveCtrls();
    void slotDeactiveCtrls();

  private slots:
    void showNewGameWnd();
    void on_actHelpAbout_triggered();
    void on_actGameQuit_triggered();
    void on_actTurnToggle_triggered();

    void on_actGameNew_triggered();

private:
    Ui::wndMain *m_ui;
    wndNewGame *m_wndNewGame;
    gfxScene *m_gfxScene;
};

#endif // WNDMAIN_H
