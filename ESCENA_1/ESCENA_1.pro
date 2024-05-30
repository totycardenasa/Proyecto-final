QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    firstscn.cpp \
    main.cpp \
    mainwindow.cpp \
    buque.cpp \
    aviones.cpp

HEADERS += \
    firstscn.h \
    mainwindow.h \
    buque.h \
    aviones.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
