#ifndef TESTSCANER_H
#define TESTSCANER_H

#include <QString>
#include <QList>
#include <QSharedPointer>

#include "interfaces/itestsuit.h"
class TestScaner
{
	enum TestType
	{
		TestTypeQtTestLib,
		TestTypeGoogleTest,
		TestTypeUnKnown
	};
	static TestType getTestType(const QString & file);
public:
	static void loadFolder(const QString & folder, const QStringList &masks, QList<QSharedPointer<ITestSuit> > & testsuites);
};

#endif // TESTSCANER_H
