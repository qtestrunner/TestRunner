#include "testfabric.h"

#include "qtimplement/qtestloader.h"
#include <gtest_implement/gtest_loader.h>

//------------------------------------------------------------------------------
// Creates QtTest Loader
void TestFabric::getQtLoader(QSharedPointer<ITestLoader> &loader)
{
	loader = QSharedPointer<ITestLoader>(new QTestLoader());
}

//------------------------------------------------------------------------------
// Creates Google test Loader
void TestFabric::getGLoader(QSharedPointer<ITestLoader> &loader)
{
    loader = QSharedPointer<ITestLoader>(new GTest_Loader());
}
