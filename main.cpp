#include <QCoreApplication>
#include <QtCore>

#include "testscaner.h"
#include "interfaces/itestsuite.h"
#include "utils/log.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QStringList masks;
	masks << "ut_*.exe";
	QList<QSharedPointer<ITestSuite> > testsuites;
	TestScaner::loadFolder("C:\\Projects\\testfolder", masks, testsuites);
	foreach(QSharedPointer<ITestSuite> suit, testsuites)
	{
		DEBUG(QString("suit name=")+suit->getName());
		QVector<QSharedPointer<ITestCase> > & cases = suit->getCases();
		foreach(QSharedPointer<ITestCase> obj, cases)
		{
			obj->print();
		}
	}
	DEBUG("all done");

	return a.exec();
}
