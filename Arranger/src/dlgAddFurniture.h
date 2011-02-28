#ifndef DLGADDFURNITURE_H
#define DLGADDFURNITURE_H

#include <QtGui/QDialog>

class QTreeWidgetItem;

namespace Ui
{
  class dlgAddFurniture;
}

class dlgAddFurniture: public QDialog
{
  Q_OBJECT

  public:
    explicit dlgAddFurniture(QWidget *parent = 0);
    ~dlgAddFurniture();

  signals:
    void signalAddFurniture(QString fileName);

  protected:
    void showEvent(QShowEvent *e);

  private slots:
    void on_btnOK_clicked();
    void on_twFurniture_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

  private:
    Ui::dlgAddFurniture *m_ui;
};

#endif // DLGADDFURNITURE_H
