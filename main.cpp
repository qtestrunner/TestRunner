#include <QCoreApplication>
#include <QtCore>
#include <QDebug>

#include "testfabric.h"
#include "testscaner.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString path("C:\\Perforce\\troynich_wks700_5304\\elektron\\5L_GRV\\v1.0\\platform\\4.8.2-win32-msvc2010-32-debug\\bin\\ut_copaddress.exe");

	QSharedPointer<ITestLoader> loader;
	TestFabric::getQtLoader(loader);

	QSharedPointer<ITestSuit> suit;
	loader->loadTestSuit(path, suit);

	QVector<QSharedPointer<ITestCase> > & cases = suit->getCases();
	foreach(QSharedPointer<ITestCase> obj, cases)
	{
		//obj->print();
	}

	QStringList masks;
	masks << "ut_*.exe";
	TestScaner::scanFolder("C:\\Perforce\\troynich_wks700_5304\\elektron\\5L_GRV\\v1.0\\platform\\4.8.2-win32-msvc2010-32-debug\\bin\\", masks);

	return a.exec();
}
