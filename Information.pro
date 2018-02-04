#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T20:03:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Information
TEMPLATE = app


SOURCES += code/main.cpp\
        code/mainwindow.cpp \
    code/gotolinedialog.cpp \
    code/finddialog.cpp \
    code/maintablewidget.cpp

HEADERS  += code/mainwindow.h \
    code/gotolinedialog.h \
    code/finddialog.h \
    code/common/commondefine.h \
    code/maintablewidget.h

FORMS    += code/ui/mainwindow.ui \
    code/ui/finddialog.ui \
    code/ui/gotolinedialog.ui \
    code/ui/maintablewidget.ui

RESOURCES += \
    mainresources.qrc
