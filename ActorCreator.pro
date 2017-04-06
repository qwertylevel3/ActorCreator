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

PRECOMPILED_HEADER = src/stable.h



SOURCES +=\
    src/main.cpp \
    src/animation/animation.cpp \
    src/animation/animationbox.cpp \
    src/animation/animationframe.cpp \
    src/animation/animationframerect.cpp \
    src/mainwindow.cpp

HEADERS  +=\
    src/stable.h \
    src/animation/animation.h \
    src/animation/animationbox.h \
    src/animation/animationframe.h \
    src/animation/animationframerect.h \
    src/mainwindow.h

FORMS    += \
    src/mainwindow.ui


INCLUDEPATH += $$PWD\src\
INCLUDEPATH += $$PWD\src\animation\
INCLUDEPATH += $$PWD\resource\

