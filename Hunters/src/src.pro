QT       += core gui xml

TARGET    = Hunters
DESTDIR   = ../bin
TEMPLATE  = app

SOURCES  += main.cpp\
            wndMain.cpp \
            wndNewGame.cpp \
            HuntersApp.cpp \
            gfxScene.cpp \
            itmHunter.cpp \
            itmPawn.cpp \
            itmPredator.cpp \
    itmMellow.cpp \
    itmAnimal.cpp \
    itmCage.cpp

HEADERS  += wndMain.h \
            wndNewGame.h \
            HuntersApp.h \
            gfxScene.h \
            itmHunter.h \
            itmPawn.h \
            itmPredator.h \
    itmMellow.h \
    itmAnimal.h \
    itmCage.h

FORMS    += wndMain.ui \
            wndNewGame.ui

RESOURCES += ../res.qrc
RC_FILE    = ../res.rc
