#ifndef QTESTFILE_H
#define QTESTFILE_H

#include <QSharedPointer>

#include "interfaces/ifile.h"
#include "interfaces/itestsuite.h"

#include "qtestsuite.h"

class QTestFile : public IFile
{
	QList<ITestSuitePtr> m_suites;
public:
	QTestFile();

	void addQTestSuite(QTestSuitePtr suite);

	virtual void run();

	virtual QList<ITestSuitePtr> & getTestSuites();

};

typedef QSharedPointer<QTestFile> QTestFilePtr;

#endif // QTESTFILE_H
