#ifndef WNDMAIN_H
#define WNDMAIN_H

#include <QtGui/QMainWindow>

class gfxScene;
class mgrFurniture;
class QLabel;

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

    QString fileName() { return m_fileName; }
    bool isModified() { return m_modified; }

  signals:
    void signalOpenAddRoomDlg();
    void signalOpenSettingsDlg();
    void signalOpenMoveDlg();
    void signalOpenResizeDlg();
    void signalOpenAddFurniDlg();

  public slots:
    void applySettings();
    void slotNewFile();
    void slotAddRoom(int width, int height, bool fill, int people, int things);
    void slotPlanMove(int x, int y);
    void slotPlanResize(int w, int h);
    void slotAddFurniture(QString fileName);

  public slots:
    void setFileName(QString fileName);
    void setModified(bool modified);
    void loadFile(QString fileName);

  protected:
    void closeEvent(QCloseEvent *e);

  private slots:
    void on_actFileNew_triggered();
    void on_actFileOpen_triggered();
    void on_actFileQuit_triggered();
    void on_actPlanAddRoom_triggered();
    void on_actPlanZoomIn_triggered();
    void on_actPlanZoomOut_triggered();
    void on_actFileSave_triggered();
    void on_actHelpAbout_triggered();
    void on_actFileSettings_triggered();
    void on_actPlanMove_triggered();
    void on_actPlanResize_triggered();
    void on_actPlanAddFurniture_triggered();

  private:
    Ui::wndMain *m_ui;
    gfxScene *m_gfxScene;
    QLabel* m_lbScale;
    QString m_fileName;
    mgrFurniture *m_furniMgr;
    bool m_modified;
};

#endif // WNDMAIN_H
