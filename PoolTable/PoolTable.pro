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

equals(QMAKE_CXX, "clang++") {
	QMAKE_CXXFLAGS_WARN_ON += -Wno-logical-op-parentheses
}
equals(QMAKE_CXX, "g++") {
	QMAKE_CXXFLAGS_WARN_ON += -Wno-parentheses
}

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
    table.h \
    pocketedtable.h \
    stagetwofactory.h \
    matryoshkaball.h \
    explodingballfeature.h \
    pocketinteractionfeature.h

SOURCES += \
    basegame.cpp \
    dialog.cpp \
    gamebuilder.cpp \
    initializer.cpp \
    main.cpp \
    stageonefactory.cpp \
    cueballcontrolfeature.cpp \
    poolgame.cpp \
    pocketedtable.cpp \
    stagetwofactory.cpp \
    matryoshkaball.cpp \
    explodingballfeature.cpp \
    pocketinteractionfeature.cpp
