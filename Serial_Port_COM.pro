QT       += core gui
QT  += serialport
QT += widgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dashboard.cpp \
    main.cpp \
    mainwindow.cpp \
    starting_screen.cpp \
    uart.cpp \
    uartips.cpp

HEADERS += \
    dashboard.h \
    mainwindow.h \
    starting_screen.h \
    uart.h \
    uartips.h

FORMS += \
    dashboard.ui \
    mainwindow.ui \
    starting_screen.ui \
    uart.ui \
    uartips.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    connexion.png \
    file.txt \
    images/logo-actia.png \
    images/logo-actia.png


