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
    qtimplement/qtestcase.cpp \
    testfabric.cpp \
    qtimplement/qtestloader.cpp \
    testscaner.cpp \
    utils/utils.cpp \
    qtimplement/qtestsuite.cpp \
    gtest_implement/gtest_testsuite.cpp \
    gtest_implement/gtest_testcase.cpp \
    qtimplement/qtestfile.cpp \
    gtest_implement/gtest_loader.cpp \
    gtest_implement/gtest_file.cpp

HEADERS += \
    qtimplement/qtestcase.h \
    interfaces/itestcase.h \
    interfaces/itestloader.h \
    testfabric.h \
    qtimplement/qtestloader.h \
    testscaner.h \
    utils/utils.h \
    utils/log.h \
    qtimplement/qtestsuite.h \
    interfaces/itestsuite.h \
    gtest_implement/gtest_testsuite.h \
    gtest_implement/gtest_testcase.h \
    data/testresults.h \
    interfaces/ifile.h \
    qtimplement/qtestfile.h \
    gtest_implement/gtest_file.h \
    gtest_implement/gtest_loader.h
