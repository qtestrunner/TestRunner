#include <QCoreApplication>
#include <QtCore>

#include "testscaner.h"
#include "interfaces/ifile.h"
#include "utils/log.h"
#include "data/testresults.h"
#include "data/testkeeper.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    if (a.arguments().count() < 3)
    {
        LOG("first argument path, second - mask\n");
        return 0;
    }
	QStringList masks;
    masks << a.arguments().at(2);
	QList<IFilePtr> testfiles;

	TestScaner::loadFolder(a.arguments().at(1), masks, testfiles);
	foreach(IFilePtr file, testfiles)
	{
		foreach(ITestSuitePtr suit, file->getTestSuites())
		{
			DEBUG(QString("suit name=") + suit->getName());
			const QList<ITestCasePtr> & cases = suit->getCases();
			foreach(const ITestCasePtr & obj, cases)
			{
				obj->print();
			}
		}
	}

	DEBUG("all done");
	QList<TestSuiteResult> results_for_save;
	foreach(IFilePtr file, testfiles)
		file->run(results_for_save);

	if (results_for_save.isEmpty())
	{
		DEBUG("result are empty!");
	}
	TRACE("Try to save");
	TestKeeper::saveSuites(results_for_save);


	QList<TestSuiteResult> results_loaded;
	SearchParams sp;
	sp.runuid = results_for_save.first().m_uid;
	TestKeeper::loadSuites(results_loaded, sp);

	foreach(const TestSuiteResult & result, results_loaded)
	{
		qDebug() << "suite name = " << result.m_suitename;

		foreach(const TestCaseResult & caseitem, result.m_caseresults)
		{
			qDebug() << "case name = " << caseitem.m_casename;
			if (caseitem.m_result == TestCaseResult::ResultTrue)
			{
				qDebug() << "passed";
			}
			else
			{
				foreach(const Incident & incd, caseitem.m_incedents)
				{
					qDebug() << "failed in" << incd.m_file_path << ":" << incd.m_line << "desc:"<< incd.m_description;
				}
			}
		}
	}

	return 0;
}
