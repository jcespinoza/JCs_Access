#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T00:55:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JCs_Access
TEMPLATE = app


SOURCES += main.cpp\
        mwindow.cpp \
    controller.cpp \
    qintermediate.cpp \
    addfieldsdialog.cpp

HEADERS  += mwindow.h \
    controller.h \
    qintermediate.h \
    addfieldsdialog.h

FORMS    += mwindow.ui \
    addfieldsdialog.ui
