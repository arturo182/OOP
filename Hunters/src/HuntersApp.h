#ifndef HUNTERSAPP_H
#define HUNTERSAPP_H

#include <QtGui/QApplication>

class wndMain;

class HuntersApp: public QApplication
{
  Q_OBJECT

  public:
    HuntersApp(int &argc, char **argv);

  private slots:
    void slotAlmostQuit();

  private:
    wndMain *m_wndMain;
};

#endif // HUNTERSAPP_H
