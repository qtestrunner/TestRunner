#include <QDir>

#include "testscaner.h"
#include "testfabric.h"
#include "gtest_testsuite.h"
#include "gtest_testcase.h"
#include "utils/utils.h"
#include "utils/log.h"

//-----------------------------------------------------------------------------
//Check testsuit type
TestScaner::TestType TestScaner::getTestType(const QString &file)
{
    QStringList args;
	args << "/?";

	QVector<QByteArray> results;
	if(Utils::runProcess(file, args, results))
	{
		foreach(QByteArray arr, results)
		{
			if (arr.contains("QVERIFY/QCOMPARE/QTEST"))
				return TestTypeQtTestLib;
            if (arr.contains("Google Test."))
                return TestTypeGoogleTest;
		}
		return TestTypeUnKnown;
	}
	else
	return TestTypeUnKnown;
}

//-----------------------------------------------------------------------------
// Loads all testsuites in folder to vector of ITestSuite
void TestScaner::loadFolder(const QString &folder, const QStringList &masks, QList<QSharedPointer<ITestSuite> > &testsuites)
{
	QDir dir(folder);
	QStringList files = dir.entryList(masks, QDir::Executable | QDir::Files, QDir::Name);

	QSharedPointer<ITestLoader> qtloader;
	TestFabric::getQtLoader(qtloader);

	Q_ASSERT(qtloader);

    ITestSuitePtr suite;
    ITestCasePtr testcase;
    QVector<QByteArray> listResult;
    QStringList args;

    DEBUG(QString("detecting tests:"));
	foreach(QString file, files)
    {
		QString absfile = dir.absolutePath() + QDir::separator() + file;
        TestScaner::TestType type = getTestType(absfile);
		switch(type)
		{
			case TestTypeQtTestLib:
                qtloader->loadTestSuite(absfile, suite);
                if (suite)
                    testsuites.push_back(suite);
                else {
					DEBUG(QString("bad test in ") + absfile);
                }
                break;
            case TestTypeGoogleTest:
                /** @warning For a while load For GTestSuite Will be there. Do not Remove! */

                args << "--gtest_list_tests";

                Utils::runProcess(absfile, args, listResult);
                DEBUG(QString("Gtest detected"));
                foreach(QByteArray line, listResult){
                    // if there is no spaces - than it is testsuitename
                    if (line[0] != ' '){
                        suite = ITestSuitePtr(new GTest_TestSuite);
                        suite->setName(line.remove(line.length()-1, 1)); // remove dot at the end of line
                        testsuites.push_back(suite);
                    }
                    else{
                        // this removes first two spaces
                        testcase = ITestCasePtr(new GTest_TestCase(line.remove(0, 2)));
                        suite->addTestCase(testcase);
                    }
                }
                break;
			case TestTypeUnKnown:
				DEBUG(QString("UnKnown type in ") + absfile);
			break;
		}
	}
}
