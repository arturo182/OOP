#ifndef DLGEDITFURNITURE_H
#define DLGEDITFURNITURE_H

#include <QtGui/QDialog>

namespace Ui
{
  class dlgEditFurniture;
}

class dlgEditFurniture: public QDialog
{
  Q_OBJECT

  public:
    explicit dlgEditFurniture(QWidget *parent = 0);
    ~dlgEditFurniture();

    void setFileName(QString fileName) { m_fileName = fileName; }

  protected:
    void showEvent(QShowEvent *e);

private slots:
    void on_btnColor_clicked();

    void on_btnOK_clicked();

private:
    Ui::dlgEditFurniture *m_ui;
    QString m_fileName;
    QColor m_color;
};

#endif // DLGEDITFURNITURE_H
