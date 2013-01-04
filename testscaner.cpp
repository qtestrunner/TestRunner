#include <QDir>

#include "testscaner.h"
#include "testfabric.h"
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

	foreach(QString file, files)
	{
		QString absfile = dir.absolutePath() + QDir::separator() + file;
		TestScaner::TestType type = getTestType(absfile);
		QSharedPointer<ITestSuite> suit;
		switch(type)
		{
			case TestTypeQtTestLib:
				qtloader->loadTestSuit(absfile, suit);
				if (suit)
					testsuites.push_back(suit);
				else
					DEBUG(QString("bad test in ") + absfile);
			break;
			case TestTypeGoogleTest:
			break;
			case TestTypeUnKnown:
				DEBUG(QString("UnKnown type in ") + absfile);
			break;
		}
	}
}
