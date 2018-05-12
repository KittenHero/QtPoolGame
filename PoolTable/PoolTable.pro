#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T23:26:07
#
#-------------------------------------------------

QT       += core gui
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PoolTable
TEMPLATE = app

DISTFILES += \
    config.json

HEADERS += \
    abstractfactory.h \
    ball.h \
    basegame.h \
    cueballcontrolfeature.h \
    dialog.h \
    gamebuilder.h \
    gamefeature.h \
    initializer.h \
    poolgame.h \
    stageoneball.h \
    stageonefactory.h \
    stageonetable.h \
    table.h

SOURCES += \
    basegame.cpp \
    dialog.cpp \
    gamebuilder.cpp \
    initializer.cpp \
    main.cpp \
    stageonefactory.cpp \
    cueballcontrolfeature.cpp
