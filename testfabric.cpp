#include "testfabric.h"

#include "qtestloader.h"

void TestFabric::getQtLoader(QSharedPointer<ITestLoader> &loader)
{
	loader = QSharedPointer<ITestLoader>(new QTestLoader());
}

void TestFabric::getGLoader(QSharedPointer<ITestLoader> &loader)
{
}
