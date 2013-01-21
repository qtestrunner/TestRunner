#ifndef IFLE_H
#define IFLE_H

#include <QList>

#include "interfaces/itestsuite.h"
#include "data/testresults.h"

class IFile
{
public:
	~IFile(){}

	virtual void run(QList<TestSuiteResult> & results) = 0;

	virtual QList<ITestSuitePtr> getTestSuites() = 0;

};

typedef QSharedPointer<IFile> IFilePtr;

#endif // IFLE_H
