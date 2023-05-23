QT       += core gui
QT  += serialport
QT += widgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configmode.cpp \
    dashboard.cpp \
    main.cpp \
    mainwindow.cpp \
    runmode.cpp \
    starting_screen.cpp \
    uart.cpp \
    uartips.cpp

HEADERS += \
    configmode.h \
    dashboard.h \
    mainwindow.h \
    runmode.h \
    starting_screen.h \
    uart.h \
    uartips.h

FORMS += \
    configmode.ui \
    dashboard.ui \
    mainwindow.ui \
    runmode.ui \
    starting_screen.ui \
    uart.ui \
    uartips.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    1.png \
    3.jpg \
    3.png \
    XCUBE.png \
    actia-logo.png \
    antivirus.png \
    back-arrow.png \
    back.png \
    back1.png \
    config1.png \
    config2.png \
    config3.png \
    config4.png \
    config5.png \
    config6.png \
    config7.png \
    connexion.png \
    debug.png \
    debug1.png \
    debugging.png \
    download.png \
    file.txt \
    images/logo-actia.png \
    images/logo-actia.png \
    input.png \
    loading.png \
    output.png \
    platform.png \
    reglage.png \
    return-button.png \
    return.png \
    running-time.png \
    send (1).png \
    send (2).png \
    send (3).png \
    send (4).png \
    send (5).png \
    send (6).png \
    send-message.png \
    send.png


