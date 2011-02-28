#include "HuntersApp.h"
#include "wndMain.h"

#include <QtCore/QTextCodec>
#include <QtCore/QDateTime>
#include <QtCore/QSettings>

HuntersApp::HuntersApp(int &argc, char **argv): QApplication(argc, argv)
{
  qsrand(QDateTime::currentMSecsSinceEpoch());

  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

  QSettings::setDefaultFormat(QSettings::IniFormat);
  QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, qApp->applicationDirPath());
  QCoreApplication::setOrganizationName("data/settings");

  connect(this, SIGNAL(aboutToQuit()), this, SLOT(slotAlmostQuit()));

  m_wndMain = new wndMain();
}

void HuntersApp::slotAlmostQuit()
{
  delete m_wndMain;
}
