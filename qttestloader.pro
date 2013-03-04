#-------------------------------------------------
#
# Project created by QtCreator 2012-12-28T09:57:51
#
#-------------------------------------------------

QT       += core sql gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qttestloader
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
    gtest_implement/gtest_file.cpp \
    gui/ctesttreeview.cpp \
    gui/ctestsuiteviewmodel.cpp \
    gui/treenode.cpp \
    data/testkeeper.cpp \
    data/databasemanager.cpp \
    gui/forms/mainfrm.cpp

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
    gtest_implement/gtest_loader.h \
    gui/ctesttreeview.h \
    gui/ctestsuiteviewmodel.h \
    gui/treenode.h \
    data/testkeeper.h \
    data/databasemanager.h \
    gui/forms/mainfrm.h

FORMS += \
    gui/forms/mainfrm.ui
