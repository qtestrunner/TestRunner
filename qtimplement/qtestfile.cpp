#include <QDebug>

#include "qtestfile.h"
#include "utils/utils.h"

QTestFile::QTestFile()
{
}

void QTestFile::run(QList<TestSuiteResult> & results)
{
	QStringList args;
	if (m_suite->isRunnable())
	{

		QList<ITestCasePtr> & cases = m_suite->getCases();
		foreach(const ITestCasePtr & caseitem, cases)
		{
			if (caseitem->isRunnable())
			{
				if(caseitem->hasDataTags())
				{
					const QList<QByteArray> & tags = caseitem->runnableDataTags();
					if (tags != caseitem->getAllDataTags())
					{
						foreach(const QByteArray & tag,tags)
						{
							QString arg(caseitem->getName());
							arg.append(':');
							arg.append(tag);
							args.push_back(arg);
						}
					}
					else
						args.push_back(caseitem->getName());
				}
				else
				{
					args.push_back(caseitem->getName());
				}
			}
		}
	}

	QByteArray output;
	Utils::runProcess(m_absname, args, output);
	qDebug() << output;
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

void QTestFile::setAbsFileName(const QString &absname)
{
	m_absname = absname;
}
