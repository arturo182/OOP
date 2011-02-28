TARGET    = Arranger
DESTDIR   = ../bin
TEMPLATE  = app

QT       += core gui xml

SOURCES  += main.cpp \
            wndMain.cpp \
            gfxScene.cpp \
            ArrangerApp.cpp \
            dlgWizard.cpp \
            itmRoom.cpp \
            dlgAddRoom.cpp \
            itmFurniture.cpp \
            dlgSettings.cpp \
            dlgEditFurniture.cpp \
            dlgMove.cpp \
    mgrFurniture.cpp \
    dlgResize.cpp \
    dlgAddFurniture.cpp

HEADERS  += wndMain.h \
            gfxScene.h \
            ArrangerApp.h \
            dlgWizard.h \
            itmRoom.h \
            dlgAddRoom.h \
            itmFurniture.h \
            dlgSettings.h \
            dlgEditFurniture.h \
            dlgMove.h \
    mgrFurniture.h \
    dlgResize.h \
    dlgAddFurniture.h

FORMS    += wndMain.ui \
            dlgWizard.ui \
            dlgAddRoom.ui \
            dlgSettings.ui \
            dlgEditFurniture.ui \
            dlgMove.ui \
    dlgResize.ui \
    dlgAddFurniture.ui

RESOURCES +=  ../res.qrc
RC_FILE    = ../res.rc
