#ifndef QTESTFILE_H
#define QTESTFILE_H

#include <QSharedPointer>

#include "interfaces/ifile.h"
#include "interfaces/itestsuite.h"

#include "qtestsuite.h"

class QTestFile : public IFile
{
	ITestSuitePtr m_suite;
	QString m_absname;
public:
	QTestFile();

	void setQTestSuite(QTestSuitePtr suite);

	virtual void setAbsFileName(const QString & absname);

	virtual void run(QList<TestSuiteResult> & results);

	virtual QList<ITestSuitePtr> getTestSuites();
};

typedef QSharedPointer<QTestFile> QTestFilePtr;

#endif // QTESTFILE_H
