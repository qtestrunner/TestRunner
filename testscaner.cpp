#include <QDir>

#include "testscaner.h"
#include "testfabric.h"
#include "gtest_implement/gtest_testsuite.h"
#include "gtest_implement/gtest_testcase.h"
#include "utils/utils.h"
#include "utils/log.h"

//-----------------------------------------------------------------------------
//Check testsuit type
TestScaner::TestType TestScaner::getTestType(const QString &file)
{
    QStringList args;
	args << "/?";

    QList<QString> results;
	if(Utils::runProcess(file, args, results))
	{
        foreach(QString arr, results)
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
    ITestLoaderPtr googleloader;
    TestFabric::getGLoader(googleloader);

    Q_ASSERT(qtloader);

	IFilePtr test_file;
	QStringList environment;



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
                googleloader->loadFile(absfile, test_file, environment);
                if (test_file)
                    ifiles.push_back(test_file);
                else
                {
                    DEBUG(QString("bad test in ") + absfile);
                }
                break;
			case TestTypeUnKnown:
				DEBUG(QString("UnKnown type in ") + absfile);
			break;
		}
	}
}
