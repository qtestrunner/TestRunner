#include <QCoreApplication>
#include <QtCore>

#include "testscaner.h"
#include "interfaces/ifile.h"
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

    return 0;
}
