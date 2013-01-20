#include "qtestfile.h"

QTestFile::QTestFile()
{
}

void QTestFile::run()
{
}

QList<ITestSuitePtr> &QTestFile::getTestSuites()
{
	return m_suites;
}

void QTestFile::addQTestSuite(QTestSuitePtr suite)
{
	m_suites.push_back(suite.staticCast<ITestSuite>());
}
