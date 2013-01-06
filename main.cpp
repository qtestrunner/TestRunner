#include <QCoreApplication>
#include <QtCore>

#include "testscaner.h"
#include "interfaces/itestsuite.h"
#include "utils/log.h"

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
	QList<QSharedPointer<ITestSuite> > testsuites;
	DEBUG("args start");
	DEBUG(a.arguments());
	DEBUG("args end");

    TestScaner::loadFolder(a.arguments().at(1), masks, testsuites);
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

    return 0;
}
