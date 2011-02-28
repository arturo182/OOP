#ifndef WDNNEWGAME_H
#define WDNNEWGAME_H

#include <QtGui/QWidget>

namespace Ui
{
  class wndNewGame;
}

class wndNewGame: public QWidget
{
  Q_OBJECT

  public:
    explicit wndNewGame(QWidget *parent = 0);
    ~wndNewGame();

  signals:
    void signalStartGame(int turn, int width, int height, int hunters, int animals);

  protected:
    void showEvent(QShowEvent *event);

  private slots:
    void on_btnOK_clicked();

  private:
    Ui::wndNewGame *m_ui;
};

#endif // WDNNEWGAME_H
