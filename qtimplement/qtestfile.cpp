#include <QXmlStreamReader>

#include "qtestfile.h"
#include "utils/utils.h"
#include "utils/log.h"
#include "data/testresults.h"

void QTestFile::parseResults(const QByteArray &output, TestSuiteResult & suite_result)
{
	QXmlStreamReader xmlr(output);
	;

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
						TestCaseResult caseitem;
						caseitem.m_casename = xmlr.attributes().value("name").toString();
						suite_result.m_caseresults.push_back(caseitem);
					}
					else if(tagname == "Incident")
					{
						QString rez = xmlr.attributes().value("type").toString();
						if (rez == "pass")
						{
							suite_result.m_caseresults.last().m_result = TestCaseResult::ResultTrue;
						}
						else
						{
							suite_result.m_caseresults.last().m_result = TestCaseResult::ResultFalse;
							Incident inc;
							inc.m_line = xmlr.attributes().value("line").toString().toInt();
							inc.m_file_path = xmlr.attributes().value("file").toString();
							suite_result.m_caseresults.last().m_incedents.push_back(inc);
						}
					}
					else if(tagname == "DataTag")
					{

						suite_result.m_caseresults.last().m_incedents.last().m_tagname = xmlr.readElementText();
					}
					else if(tagname == "Description")
					{
						suite_result.m_caseresults.last().m_incedents.last().m_description = xmlr.readElementText();
					}
			}
	}

	if(xmlr.hasError())
	{
		LOG(xmlr.errorString());
		return;
	}
}

QTestFile::QTestFile()
{
}

void QTestFile::run(QList<TestSuiteResult> & results)
{
	TestSuiteResult suite_result;
	suite_result.m_suitename = m_suite->getName();
	suite_result.m_uid = QUuid::createUuid();

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
	if(Utils::runProcess(m_absname, args, output))
		parseResults(output, suite_result);

	results.push_back(suite_result);
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
