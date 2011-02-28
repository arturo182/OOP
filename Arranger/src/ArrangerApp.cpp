#include "ArrangerApp.h"

#include "wndMain.h"
#include "dlgMove.h"
#include "dlgResize.h"
#include "dlgWizard.h"
#include "dlgAddRoom.h"
#include "dlgSettings.h"
#include "dlgAddFurniture.h"

#include <QtCore/QSettings>
#include <QtCore/QTextCodec>
#include <QtCore/QDebug>

ArrangerApp::ArrangerApp(int &argc, char **argv): QApplication(argc, argv)
{
  QSettings::setDefaultFormat(QSettings::IniFormat);
  QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, qApp->applicationDirPath());

  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

  QCoreApplication::setOrganizationName("data/settings");

  QSettings set;
  int count = set.value("MRU/count", 0).toInt();
  if(count > 15) { count = 15; }
  for(int i = 0; i < count; i++) {
    m_mru.append(set.value(QString("MRU/file%1").arg(i)).toString());
  }

  m_mru.removeDuplicates();

  m_wndMain = new wndMain();
  m_dlgMove = new dlgMove();
  m_dlgResize = new dlgResize();
  m_dlgWizard = new dlgWizard();
  m_dlgAddRoom = new dlgAddRoom();
  m_dlgSettings = new dlgSettings();
  m_dlgAddFurniture = new dlgAddFurniture();

  connect(this, SIGNAL(aboutToQuit()), this, SLOT(slotAlmostQuit()));

  connect(m_wndMain, SIGNAL(signalOpenAddRoomDlg()), m_dlgAddRoom, SLOT(show()));
  connect(m_wndMain, SIGNAL(signalOpenSettingsDlg()), m_dlgSettings, SLOT(show()));
  connect(m_wndMain, SIGNAL(signalOpenMoveDlg()), m_dlgMove, SLOT(show()));
  connect(m_wndMain, SIGNAL(signalOpenResizeDlg()), m_dlgResize, SLOT(show()));
  connect(m_wndMain, SIGNAL(signalOpenAddFurniDlg()), m_dlgAddFurniture, SLOT(show()));

  connect(m_dlgWizard, SIGNAL(signalNewClicked()), m_wndMain, SLOT(slotNewFile()));
  connect(m_dlgMove, SIGNAL(signalPlanMove(int,int)), m_wndMain, SLOT(slotPlanMove(int,int)));
  connect(m_dlgResize, SIGNAL(signalPlanResize(int,int)), m_wndMain, SLOT(slotPlanResize(int,int)));
  connect(m_dlgAddRoom, SIGNAL(signalAddRoom(int,int,bool,int,int)), m_wndMain, SLOT(slotAddRoom(int,int,bool,int,int)));
  connect(m_dlgAddFurniture, SIGNAL(signalAddFurniture(QString)), m_wndMain, SLOT(slotAddFurniture(QString)));
}

void ArrangerApp::addToMru(QString fileName)
{
  m_mru.removeAll(fileName);
  m_mru.prepend(fileName);
}

void ArrangerApp::slotAlmostQuit()
{
  QSettings set;

  set.setValue("MRU/count", m_mru.count());
  for(int i = 0; i < m_mru.count(); i++) {
    set.setValue(QString("MRU/file%1").arg(i), m_mru.at(i));
  }

  delete m_dlgSettings;
  delete m_dlgAddRoom;
  delete m_dlgWizard;
  delete m_wndMain;
}
