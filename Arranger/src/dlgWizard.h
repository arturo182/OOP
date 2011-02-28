#ifndef DLGWIZARD_H
#define DLGWIZARD_H

#include <QtGui/QDialog>

class QCloseEvent;
class QTreeWidgetItem;

namespace Ui
{
  class dlgWizard;
}

class dlgWizard: public QDialog
{
  Q_OBJECT

  public:
    explicit dlgWizard(QWidget *parent = 0);
    ~dlgWizard();

  signals:
    void signalNewClicked();

  protected:
    void closeEvent(QCloseEvent *e);
    void showEvent(QShowEvent *e);

  private slots:
    void on_btnQuit_clicked();
    void on_btnNew_clicked();

    void on_btnOpen_clicked();

    void on_twMRU_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::dlgWizard *m_ui;
};

#endif // DLGWIZARD_H
