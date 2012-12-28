#include <QCoreApplication>
#include <QDebug>
#include "qtrunner.h"

class QTestRun
{
public:

};

class QTestCase
{
public:

};

class QTestData
{
public:

};




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QString path("C:\\Perforce\\troynich_wks700_5304\\elektron\\5L_GRV\\v1.0\\platform\\4.8.2-win32-msvc2010-32-debug\\bin\\ut_ciobuffer.exe");
	QStringList cases;
	QtRunner::getTestCases(path, cases);
	qDebug() << cases;
	
	return a.exec();
}
