#ifndef DLGRESIZE_H
#define DLGRESIZE_H

#include <QtGui/QDialog>

namespace Ui
{
  class dlgResize;
}

class dlgResize: public QDialog
{
  Q_OBJECT

  public:
    explicit dlgResize(QWidget *parent = 0);
    ~dlgResize();

  signals:
    void signalPlanResize(int w, int h);

  protected:
    void showEvent(QShowEvent *e);

  private slots:
    void on_btnOK_clicked();

  private:
    Ui::dlgResize *m_ui;
};

#endif // DLGRESIZE_H
