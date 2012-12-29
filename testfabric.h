#ifndef TESTFABRIC_H
#define TESTFABRIC_H

#include "interfaces/itestloader.h"


class TestFabric
{
public:
	static void getQtLoader(QSharedPointer<ITestLoader> & loader);
	static void getGLoader(QSharedPointer<ITestLoader> & loader);


};

#endif // TESTFABRIC_H
