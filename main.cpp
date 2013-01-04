#include <QCoreApplication>
#include <QtCore>
#include <QDebug>

#include "testscaner.h"
#include "interfaces/itestsuit.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QStringList masks;
	masks << "ut_*.exe";
	QList<QSharedPointer<ITestSuite> > testsuites;
	TestScaner::loadFolder("C:\\Projects\\testfolder", masks, testsuites);
	foreach(QSharedPointer<ITestSuite> suit, testsuites)
	{
		qDebug() << "test suit" << suit->getName();
		QVector<QSharedPointer<ITestCase> > & cases = suit->getCases();
		foreach(QSharedPointer<ITestCase> obj, cases)
		{
			obj->print();
		}
	}
	qDebug() << "all done";

	return a.exec();
}
