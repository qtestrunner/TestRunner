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
    testfabric.cpp \
    qtestloader.cpp \
    testscaner.cpp \
    utils/utils.cpp \
    qtestsuite.cpp \
    gtest_testsuite.cpp \
    gtest_testcase.cpp

HEADERS += \
    qtestcase.h \
    interfaces/itestcase.h \
    interfaces/itestloader.h \
    testfabric.h \
    qtestloader.h \
    testscaner.h \
    utils/utils.h \
    utils/log.h \
    qtestsuite.h \
    interfaces/itestsuite.h \
    gtest_testsuite.h \
    gtest_testcase.h
