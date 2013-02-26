#ifndef TESTFABRIC_H
#define TESTFABRIC_H

#include "interfaces/itestloader.h"

/** Creates specific loader of tests */
class TestFabric
{
public:
	/** Creates QtTest Loader
	 * @param[out] loader in qsharedpointer
	 */
	static void getQtLoader(QSharedPointer<ITestLoader> & loader);

	/** Creates Google test Loader
	 * @param[out] loader in qsharedpointer
	 */
	static void getGLoader(QSharedPointer<ITestLoader> & loader);
};

#endif // TESTFABRIC_H
