#include "testfabric.h"

#include "qtimplement/qtestloader.h"

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
}
