#ifndef ARRANGERAPP_H
#define ARRANGERAPP_H

#include <QtGui/QApplication>
#include <QtCore/QStringList>

class wndMain;
class dlgMove;
class dlgResize;
class dlgWizard;
class dlgAddRoom;
class dlgSettings;
class dlgAddFurniture;

class ArrangerApp: public QApplication
{
  Q_OBJECT

  public:
    explicit ArrangerApp(int &argc, char **argv);

    void addToMru(QString fileName);

    wndMain *getWndMain() { return m_wndMain; }
    QStringList getMru() { return m_mru; }

  private slots:
    void slotAlmostQuit();

  private:
    QStringList m_mru;
    wndMain *m_wndMain;
    dlgWizard *m_dlgWizard;
    dlgAddRoom *m_dlgAddRoom;
    dlgSettings *m_dlgSettings;
    dlgMove *m_dlgMove;
    dlgResize *m_dlgResize;
    dlgAddFurniture *m_dlgAddFurniture;

};

#endif // ARRANGERAPP_H
