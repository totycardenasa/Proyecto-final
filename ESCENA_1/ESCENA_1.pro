QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    firstscn.cpp \
    humo.cpp \
    main.cpp \
    mainwindow.cpp \
    buque.cpp \
    aviones.cpp \
    Bullet.cpp \
    Enemy.cpp \
    Game.cpp \
    Health.cpp \
    Player.cpp \
    Score.cpp \
    misil.cpp

HEADERS += \
    firstscn.h \
    humo.h \
    mainwindow.h \
    buque.h \
    aviones.h \
    misil.h \
    Bullet.h \
    Enemy.h \
    Game.h \
    Health.h \
    Player.h \
    Score.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
