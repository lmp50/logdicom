#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T13:01:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logdicom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialhelp.cpp \
    classlogdicom.cpp \
    classfiledicom.cpp

HEADERS  += mainwindow.h \
    dialhelp.h \
    classlogdicom.h \
    classfiledicom.h \
    constdefine.h

FORMS    += mainwindow.ui \
    dialhelp.ui

TRANSLATIONS += \
    Translations/logdicom_ru.ts

tr.commands = lupdate $$_PRO_FILE_ && lrelease $$_PRO_FILE_
    PRE_TARGETDEPS += tr
    QMAKE_EXTRA_TARGETS += tr

RESOURCES += \
    logd.qrc

