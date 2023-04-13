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
    main.cpp \
    mainwindow.cpp \
    signupwindow.cpp \
    userdatahandler.cpp

HEADERS += \
    country.h \
    gamemodel.h \
    gamewindow.h \
    mainwindow.h \
    signupwindow.h \
    userdatahandler.h

FORMS += \
    gamewindow.ui \
    mainwindow.ui \
    signupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    EducationAppResources.qrc

DISTFILES +=
