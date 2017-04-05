#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T17:28:51
#
#-------------------------------------------------

QT       += core gui
QT		 += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActorCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    animation.cpp \
    animationframe.cpp \
    animationbox.cpp

HEADERS  += mainwindow.h \
    animation.h \
    animationframe.h \
    animationbox.h

FORMS    += mainwindow.ui
