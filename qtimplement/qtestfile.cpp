#include <QDebug>
#include <QXmlStreamReader>

#include "qtestfile.h"
#include "utils/utils.h"
#include "data/testresults.h"

void QTestFile::parseResults(const QByteArray &output)
{
	QXmlStreamReader xmlr(output);
	TestSuiteResult suite;

	while(!xmlr.atEnd() && !xmlr.hasError())
	{
			QXmlStreamReader::TokenType token = xmlr.readNext();

			if(token == QXmlStreamReader::StartDocument)
					continue;

			if(token == QXmlStreamReader::StartElement)
			{
					QStringRef tagname = xmlr.name();
					if (tagname == "TestFunction")
					{
//						TestCaseResult caseitem;
//						caseitem.m_casename = xmlr.attributes().value("name");
//						suite.m_caseresults.push_back(caseitem);
					}
					else if(tagname == "Incident")
					{
//						QByteArray rez = xmlr.attributes().value("type");
//						if (rez == "pass")
//							suite.m_caseresults.last()->m_result = TestCaseResult::ResultTrue;
//						else
//							suite.m_caseresults.last()->m_result = TestCaseResult::ResultFalse;
					}

			}
	}

	if(xmlr.hasError())
	{
		qDebug() << "Error reading xml" << xmlr.errorString();
		return;
	}
}

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

	if (args.isEmpty())
		return;

	QByteArray output;
	args.insert(0, "-xml");
	Utils::runProcess(m_absname, args, output);
	parseResults(output);
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
