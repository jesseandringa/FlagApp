QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    country.cpp \
    gamemodel.cpp \
    gamewindow.cpp \
    gamewindowhelp.cpp \
    helpwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    signupwindow.cpp \
    statswindow.cpp \
    studywindow.cpp \
    userdatahandler.cpp

HEADERS += \
    country.h \
    gamemodel.h \
    gamewindow.h \
    gamewindowhelp.h \
    helpwindow.h \
    loginwindow.h \
    mainwindow.h \
    signupwindow.h \
    statswindow.h \
    studywindow.h \
    userdatahandler.h

FORMS += \
    gamewindow.ui \
    gamewindowhelp.ui \
    helpwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    signupwindow.ui \
    statswindow.ui \
    studywindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    EducationAppResources.qrc

DISTFILES +=
