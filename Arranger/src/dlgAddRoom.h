#ifndef DLGADDROOM_H
#define DLGADDROOM_H

#include <QtGui/QDialog>

class QShowEvent;

namespace Ui
{
  class dlgAddRoom;
}

class dlgAddRoom: public QDialog
{
  Q_OBJECT

  public:
    explicit dlgAddRoom(QWidget *parent = 0);
    ~dlgAddRoom();

  protected:
    void showEvent(QShowEvent *e);

  signals:
    void signalAddRoom(int width, int height, bool fill, int people, int things);

  private slots:
    void on_btnOK_clicked();

  private:
    Ui::dlgAddRoom *m_ui;
};

#endif // DLGADDROOM_H
