QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    utils/actionpushbutton.cpp \
    utils/datasetloader.cpp \
    utils/datasetsetup.cpp \
    utils/descriptioncheckbox.cpp \
    utils/integerrangetune.cpp

HEADERS += \
    mainwindow.h \
    utils/actionpushbutton.h \
    utils/datasetloader.h \
    utils/datasetsetup.h \
    utils/descriptioncheckbox.h \
    utils/integerrangetune.h \
    utils/loaditems.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    QtHowToResources.qrc

RC_ICONS = QtHowTo.ico
