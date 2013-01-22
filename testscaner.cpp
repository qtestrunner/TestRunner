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

	QList<QByteArray> results;
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
void TestScaner::loadFolder(const QString &folder, const QStringList &masks, QList<IFilePtr> &ifiles)
{
	QDir dir(folder);
	QStringList files_list = dir.entryList(masks, QDir::Executable | QDir::Files, QDir::Name);

	ITestLoaderPtr qtloader;
	TestFabric::getQtLoader(qtloader);
	//!ITestLoaderPtr googleloader; FIXME: I think to do this way
	//!TestFabric::getGLoader(googleloader);

	Q_ASSERT(qtloader);
	QList<ITestSuitePtr> google_suites; //FIXME:deprecated
	ITestSuitePtr google_suite;//FIXME:deprecated

	IFilePtr test_file;
	QStringList environment;

	ITestCasePtr testcase;//FIXME:deprecated
	QList<QByteArray> listResult;//FIXME:deprecated
	QStringList args;//FIXME:deprecated

    DEBUG(QString("detecting tests:"));
	foreach(QString file_name, files_list)
    {
		QString absfile = dir.absolutePath() + QDir::separator() + file_name;
        TestScaner::TestType type = getTestType(absfile);
		switch(type)
		{
			case TestTypeQtTestLib:

				qtloader->loadFile(absfile, test_file, environment);
				if (test_file)
					ifiles.push_back(test_file);
				else
				{
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
						google_suite = ITestSuitePtr(new GTest_TestSuite);
						google_suite->setName(line.remove(line.length()-1, 1)); // remove dot at the end of line
						google_suites.push_back(google_suite);
                    }
                    else{
                        // this removes first two spaces
                        testcase = ITestCasePtr(new GTest_TestCase(line.remove(0, 2)));
						google_suite->addTestCase(testcase);
                    }
                }
                break;
			case TestTypeUnKnown:
				DEBUG(QString("UnKnown type in ") + absfile);
			break;
		}
	}
}
