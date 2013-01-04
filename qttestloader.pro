#-------------------------------------------------
#
# Project created by QtCreator 2012-12-28T09:57:51
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = qttestloader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qtestcase.cpp \
    qtestsuit.cpp \
    testfabric.cpp \
    qtestloader.cpp \
    testscaner.cpp \
    utils/utils.cpp

HEADERS += \
    qtestcase.h \
    qtestsuit.h \
    interfaces/itestcase.h \
    interfaces/itestsuit.h \
    interfaces/itestloader.h \
    testfabric.h \
    qtestloader.h \
    testscaner.h \
    utils/utils.h \
    utils/log.h
