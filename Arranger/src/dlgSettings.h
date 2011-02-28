#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QtGui/QDialog>
#include <QtGui/QTreeWidgetItem>

class dlgEditFurniture;

namespace Ui
{
  class dlgSettings;
}

class dlgSettings: public QDialog
{
  Q_OBJECT

  public:
    explicit dlgSettings(QWidget *parent = 0);
    ~dlgSettings();

  protected:
    void showEvent(QShowEvent *e);

  private slots:
    void on_twFurniture_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_btnFurnitureAdd_clicked();

    void on_btnFurnitureEdit_clicked();

private:
    Ui::dlgSettings *m_ui;
    dlgEditFurniture *m_dlgFurniture;
};

#endif // DLGSETTINGS_H
