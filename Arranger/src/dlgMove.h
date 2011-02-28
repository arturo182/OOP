#ifndef DLGMOVE_H
#define DLGMOVE_H

#include <QtGui/QDialog>

class QShowEvent;

namespace Ui
{
  class dlgMove;
}

class dlgMove: public QDialog
{
    Q_OBJECT

  public:
    explicit dlgMove(QWidget *parent = 0);
    ~dlgMove();

  signals:
    void signalPlanMove(int x, int y);

  protected:
    void showEvent(QShowEvent *e);

  private slots:
    void on_btnOK_clicked();

private:
    Ui::dlgMove *m_ui;
};

#endif // DLGMOVE_H
