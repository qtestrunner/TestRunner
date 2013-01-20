#ifndef IFLE_H
#define IFLE_H

#include <QList>

#include "interfaces/itestsuite.h"

class IFile
{
public:
	~IFile(){}

	virtual void run() = 0;

	virtual QList<ITestSuitePtr> & getTestSuites() = 0;

};

typedef QSharedPointer<IFile> IFilePtr;

#endif // IFLE_H
