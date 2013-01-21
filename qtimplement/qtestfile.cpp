#include <QDebug>

#include "qtestfile.h"

QTestFile::QTestFile()
{
}

void QTestFile::run(QList<TestSuiteResult> & results)
{
	if (m_suite->isRunnable())
	{
		//QList<ITestCasePtr> & cases = m_suite->getCases();
		//foreach(ITestCasePtr)
	}
}

QList<ITestSuitePtr> QTestFile::getTestSuites()
{
	QList<ITestSuitePtr> suites;
	suites.push_back(m_suite);
	return suites;
}

void QTestFile::setQTestSuite(QTestSuitePtr suite)
{
	m_suite = suite;
}
