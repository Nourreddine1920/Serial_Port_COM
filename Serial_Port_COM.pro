QT       += core gui
QT  += serialport
QT += widgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configchoice.cpp \
    configmode.cpp \
    dashboard.cpp \
    directrun.cpp \
    main.cpp \
    mainwindow.cpp \
    runmode.cpp \
    sequenceapplication.cpp \
    starting_screen.cpp \
    testapplication.cpp \
    uart.cpp \
    uartips.cpp

HEADERS += \
    configchoice.h \
    configmode.h \
    dashboard.h \
    directrun.h \
    mainwindow.h \
    runmode.h \
    sequenceapplication.h \
    starting_screen.h \
    testapplication.h \
    uart.h \
    uartips.h

FORMS += \
    configchoice.ui \
    configmode.ui \
    dashboard.ui \
    directrun.ui \
    mainwindow.ui \
    runmode.ui \
    sequenceapplication.ui \
    starting_screen.ui \
    testapplication.ui \
    uart.ui \
    uartips.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    1.png \
    2.png \
    3.jpg \
    3.png \
    XCUBE.png \
    actia-logo.png \
    antivirus.png \
    application.png \
    back-arrow.png \
    back.png \
    back1.png \
    browser.png \
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
    facebook-removebg-preview.png \
    facebook.png \
    file.txt \
    gmail.png \
    images/logo-actia.png \
    images/logo-actia.png \
    input.png \
    insta.png \
    instagram-removebg-preview (1).png \
    instagram-removebg-preview (1).png \
    instagram.jpg \
    linkedin-removebg-preview.png \
    linkedin.png \
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
    send.png \
    starting-app.png \
    starting.png \
    startingapplication.png \
    testapplication.png \
    welcome.png \
    welcomeapp.png \
    xcube (2).png \
    xcubellll.png


